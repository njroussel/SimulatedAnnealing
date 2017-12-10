#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <mcaa/mcmc.h>

/**
 * \brief Multithreaded pipeline MCMCrunner
 */
class MultiMCMCRunner {
    public:
        /**
         * \brief Constructs the multithreaded pipeline runner from the given
         *  runners. 
         *
         * \param workerCount
         *  The number of workers (threads) to be used. 
         *
         * \param runners
         *  A vector of MCMCRunner pointers. 
         */
        MultiMCMCRunner (int workerCount, std::vector<MCMCRunner*> runners) :
            m_workerCount(workerCount), m_jobsCount(runners.size()), m_runners(runners) { }

        /**
         * \brief Pybind bindings for MultiMCMCRunner
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<MultiMCMCRunner>(m, "multiMCMCRunner")
                .def(pybind11::init<int, std::vector<MCMCRunner*>>())
                .def("getEMeasures", &MultiMCMCRunner::getEMeasures)
                .def("getOverlapMeasures", &MultiMCMCRunner::getOverlapMeasures)
                .def("runAll", &MultiMCMCRunner::runAll);
        }

        /**
         * Runs all the runners according the number of worker defined.
         */
        void runAll();

        /**
         * \brief Returns all energy measures for each runner.
         *
         * \return
         *  The Matrix containing all energy measures for each runner (columns).
         */
        inline MatrixXf getEMeasures() const {
            int rows = (m_runners[0])->getEMeasures().rows();
            MatrixXf out(rows, m_jobsCount);

            for (int i = 0; i < m_jobsCount; i++) {
                out.col(i) = (m_runners[i])->getEMeasures();
            }

            return out;
        }

        /**
         * \brief Returns all overlap measures for each runner.
         *
         * \return
         *  The Matrix containing all overlap measures for each runner (columns).
         */
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
