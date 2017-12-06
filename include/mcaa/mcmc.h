#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <mcaa/common.h>
#include <mcaa/sampler.h>

class MCMCRunner {
    public:
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
