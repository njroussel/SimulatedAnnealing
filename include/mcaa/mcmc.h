#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <mcaa/common.h>
#include <mcaa/sampler.h>

/**
 * \brief Simple MCMC runner for simulated annealing 
 */
class MCMCRunner {
    public:
        /**
         * \brief Constructs a MCMCRunner runners. 
         *
         * \param mutationCount 
         *  The number of mutations which we be ran.
         *
         * \param measureStep 
         *  The number of mutations between each measure (energy and overlap).
         *
         * \param beta 
         *  The inital temperature parameter.
         *
         * \param sampler 
         *  The sampler to be used by this runner.
         *
         * \param weights 
         *  The goal weights.
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
        MCMCRunner(int mutationCount, int measureStep, Float beta, Sampler &sampler, 
                VectorXf &weights, MatrixXf &patterns, VectorXf &classes,
                uint32_t seed = 0xDEADBEEF) :
            m_mutationCount(mutationCount),
            m_measureStep(measureStep), m_beta(beta), m_sampler(sampler),
            m_weights(weights), m_patterns(patterns), m_classes(classes) {
                int EmeasuresLength = (int) (((Float) m_mutationCount) / m_measureStep) + 1;
                m_EMeasures = VectorXf(EmeasuresLength);
                m_overlapMeasures = VectorXf(EmeasuresLength);
                m_rng.seed(seed);
            }

        /**
         * \brief Pybind bindings for MCMCRunner
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<MCMCRunner>(m, "MCMCRunner")
                .def(pybind11::init<int, int, Float, Sampler&, VectorXf&,
                        MatrixXf&, VectorXf&, uint32_t>(),
                        pybind11::arg("mutationCount"),
                        pybind11::arg("measureStep"),
                        pybind11::arg("beta"),
                        pybind11::arg("sampler"),
                        pybind11::arg("weights"),
                        pybind11::arg("patterns"),
                        pybind11::arg("classes"),
                        pybind11::arg("seed") = 0xDEADBEEF)
                .def("run", &MCMCRunner::run)
                .def("getPointer", &MCMCRunner::getPointer)
                .def("getClasses", &MCMCRunner::getClasses)
                .def("getEMeasures", &MCMCRunner::getEMeasures)
                .def("getOverlapMeasures", &MCMCRunner::getOverlapMeasures);
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
        inline MCMCRunner* getPointer() {
            return this;
        }

        /**
         * \brief Returns the energy measures from this run.
         */
        inline VectorXf getEMeasures() const {
            return m_EMeasures;
        }

        /**
         * \brief Returns the overlap measures from this run.
         */
        inline VectorXf getOverlapMeasures() const {
            return m_overlapMeasures;
        }

    protected:
        int m_mutationCount;
        int m_measureStep;
        Float m_beta;

        pcg32 m_rng;
        VectorXf m_weights;
        MatrixXf m_patterns;
        VectorXf m_classes;
        VectorXf m_EMeasures;
        VectorXf m_overlapMeasures;
        Sampler &m_sampler;
};
