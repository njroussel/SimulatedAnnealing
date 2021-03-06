#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <mcaa/common.h>
#include <mcaa/sampler.h>
#include <mcaa/schedule.h>

/**
 * \brief Simple MCMC runner for simulated annealing 
 */
class CompetitionRunner {
    public:
        /**
         * \brief Constructs a CompetitionRunner runners. 
         *
         * \param mutationCount 
         *  The number of mutations which we be ran.
         *
         * \param measureStep 
         *  The number of mutations between each measure energy. 
         *
         * \param beta 
         *  The inital temperature parameter.
         *
         * \param sampler 
         *  The sampler to be used by this runner.
         *
         * \param patterns 
         *  The patterns (input data).
         *
         * \param classes 
         *  The classes (output data).
         *
         * \param seed 
         *  A random seed to be used for this runner.
         */
        CompetitionRunner(int mutationCount, int measureStep, Schedule &schedule, Sampler &sampler, 
                MatrixXf &patterns, VectorXf &classes,
                uint32_t seed = 0xDEADBEEF) :
            m_mutationCount(mutationCount),
            m_measureStep(measureStep), m_schedule(schedule), m_sampler(sampler),
            m_patterns(patterns), m_classes(classes) {
                int EmeasuresLength = m_measureStep == 0 ?
                    1 : (int) (((Float) m_mutationCount) / m_measureStep) + 1;
                m_EMeasures = VectorXf(EmeasuresLength);
                m_EMeasures.setZero();
                m_rng.seed(seed);
            }

        /**
         * \brief Pybind bindings for CompetitionRunner
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<CompetitionRunner>(m, "CompetitionRunner")
                .def(pybind11::init<int, int, Schedule&, Sampler&, 
                        MatrixXf&, VectorXf&, uint32_t>(),
                        pybind11::arg("mutationCount"),
                        pybind11::arg("measureStep"),
                        pybind11::arg("schedule"),
                        pybind11::arg("sampler"),
                        pybind11::arg("patterns"),
                        pybind11::arg("classes"),
                        pybind11::arg("seed") = 0xDEADBEEF)
                .def("run", &CompetitionRunner::run)
                .def("getPointer", &CompetitionRunner::getPointer)
                .def("getClasses", &CompetitionRunner::getClasses)
                .def("getEMeasures", &CompetitionRunner::getEMeasures);
        }


        /**
         * \brief Runs the MCMC method for the defined number of mutations. 
         */
        void run();

        /**
         * \brief Returns the goal classes.
         */
        inline VectorXf getClasses() {
            return m_classes;
        }

        /**
         * \brief Returns this object's pointer.
         */
        inline CompetitionRunner* getPointer() {
            return this;
        }

        /**
         * \brief Returns the energy measures from this run.
         */
        inline VectorXf getEMeasures() const {
            return m_EMeasures;
        }

    protected:
        int m_mutationCount;
        int m_measureStep;

        pcg32 m_rng;
        MatrixXf m_patterns;
        VectorXf m_classes;
        VectorXf m_EMeasures;
        Sampler &m_sampler;
        Schedule &m_schedule;
};
