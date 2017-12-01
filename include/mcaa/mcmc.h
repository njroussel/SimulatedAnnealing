#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/sampler.h>
#include <mcaa/helpers.h>


using namespace std; 
class MCMCRunner {
    public:
        MCMCRunner(int mutationCount, int measureStep, Float beta, Sampler &sampler, 
                std::vector<Float> &patterns, std::vector<Float> &classes,
                uint32_t seed = 0xDEADBEEF) :
            m_mutationCount(mutationCount),
            m_measureStep(measureStep), m_beta(beta) m_sampler(sampler),
            m_patterns(patterns), m_classes(classes) {
                int EmeasuresLength = measureStep == 0 ?
                    1 : (int) (((Float) m_mutationCount) / m_measureStep);
                m_EMeasures = std::vector<Float>(EmeasuresLength);
                m_rng.seed(seed);
            }


        static void defPybind(pybind11::module &m) {
            pybind11::class_<MCMCRunner>(m, "MCMCRunner")
                .def(pybind11::init<int, int, Float, Sampler&, std::vector<Float>&,
                        std::vector<Float>&, uint32_t>(),
                        pybind11::arg("mutationCount"),
                        pybind11::arg("measureStep"),
                        pybind11::arg("beta"),
                        pybind11::arg("sampler"),
                        pybind11::arg("patterns"),
                        pybind11::arg("classes"),
                        pybind11::arg("seed") = 0xDEADBEEF)
                .def("run", &MCMCRunner::run)
                .def("getPointer", &MCMCRunner::getPointer)
                .def("getEMeasures", &MCMCRunner::getEMeasures);
        }

        void run();

        inline MCMCRunner* getPointer() {
            return this;
        }

        inline std::vector<Float> getEMeasures() const {
            return m_EMeasures;
        }

    protected:
        int m_mutationCount;
        int m_measureStep;
        Float m_beta;

        pcg32 m_rng;
        std::vector<Float> m_EMeasures;
        std::vector<Float> m_patterns;
        std::vector<Float> m_classes;
        Sampler &m_sampler;
};
