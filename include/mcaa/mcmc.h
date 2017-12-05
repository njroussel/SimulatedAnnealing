#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/common.h>
#include <mcaa/helpers.h>
#include <mcaa/sampler.h>

class MCMCRunner {
    public:
        MCMCRunner(int mutationCount, int measureStep, Float beta, Sampler &sampler, 
                MatrixXf &patterns, VectorXf &classes,
                uint32_t seed = 0xDEADBEEF) :
            m_mutationCount(mutationCount),
            m_measureStep(measureStep), m_beta(beta), m_sampler(sampler),
            m_patterns(patterns), m_classes(classes) {
                int EmeasuresLength = (int) (((Float) m_mutationCount) / m_measureStep) + 1;
                m_EMeasures = VectorXf(EmeasuresLength);
                m_rng.seed(seed);
            }


        static void defPybind(pybind11::module &m) {
            pybind11::class_<MCMCRunner>(m, "MCMCRunner")
                .def(pybind11::init<int, int, Float, Sampler&, MatrixXf&,
                        VectorXf&, uint32_t>(),
                        pybind11::arg("mutationCount"),
                        pybind11::arg("measureStep"),
                        pybind11::arg("beta"),
                        pybind11::arg("sampler"),
                        pybind11::arg("patterns"),
                        pybind11::arg("classes"),
                        pybind11::arg("seed") = 0xDEADBEEF)
                .def("run", &MCMCRunner::run)
                .def("getPointer", &MCMCRunner::getPointer)
                .def("getClasses", &MCMCRunner::getClasses)
                .def("getEMeasures", &MCMCRunner::getEMeasures);
        }

        void run();

        inline VectorXf getClasses() {
            return m_classes;
        }

        inline MCMCRunner* getPointer() {
            return this;
        }

        inline VectorXf getEMeasures() const {
            return m_EMeasures;
        }

    protected:
        int m_mutationCount;
        int m_measureStep;
        Float m_beta;

        pcg32 m_rng;
        MatrixXf m_patterns;
        VectorXf m_classes;
        VectorXf m_EMeasures;
        Sampler &m_sampler;
};
