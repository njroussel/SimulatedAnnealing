#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <mcaa/mcmc.h>

class MultiMCMCRunner {
    public:
        MultiMCMCRunner (int workerCount, std::vector<MCMCRunner*> runners) :
            m_workerCount(workerCount), m_jobsCount(runners.size()), m_runners(runners) { }

        static void defPybind(pybind11::module &m) {
            pybind11::class_<MultiMCMCRunner>(m, "multiMCMCRunner")
                .def(pybind11::init<int, std::vector<MCMCRunner*>>())
                .def("getEMeasures", &MultiMCMCRunner::getEMeasures)
                .def("getOverlapMeasures", &MultiMCMCRunner::getOverlapMeasures)
                .def("runAll", &MultiMCMCRunner::runAll);
        }

        void runAll();

        inline MatrixXf getEMeasures() const {
            int rows = (m_runners[0])->getEMeasures().rows();
            MatrixXf out(rows, m_jobsCount);

            for (int i = 0; i < m_jobsCount; i++) {
                out.col(i) = (m_runners[i])->getEMeasures();
            }

            return out;
        }

        inline MatrixXf getOverlapMeasures() const {
            int rows = (m_runners[0])->getOverlapMeasures().rows();
            MatrixXf out(rows, m_jobsCount);

            for (int i = 0; i < m_jobsCount; i++) {
                out.col(i) = (m_runners[i])->getOverlapMeasures();
            }

            return out;
        }

    private:
        void runJobs(int index);

        int m_workerCount;
        int m_jobsCount;

        std::vector<MCMCRunner*> m_runners;
};
