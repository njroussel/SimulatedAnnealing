#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <mcaa/competition.h>

/**
 * \brief Multithreaded pipeline CompetitionRunner
 */
class MultiCompetitionRunner {
    public:
        /**
         * \brief Constructs the multithreaded pipeline runner from the given
         *  runners. 
         *
         * \param workerCount
         *  The number of workers (threads) to be used. 
         *
         * \param runners
         *  A vector of CompetitionRunner pointers. 
         */
        MultiCompetitionRunner (int workerCount, std::vector<CompetitionRunner*> runners) :
            m_workerCount(workerCount), m_jobsCount(runners.size()), m_runners(runners) { }

        /**
         * \brief Pybind bindings for MultiCompetitionRunner
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<MultiCompetitionRunner>(m, "multiCompetitionRunner")
                .def(pybind11::init<int, std::vector<CompetitionRunner*>>())
                .def("getEMeasures", &MultiCompetitionRunner::getEMeasures)
                .def("runAll", &MultiCompetitionRunner::runAll);
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

    private:
        void runJobs(int index);

        int m_workerCount;
        int m_jobsCount;

        std::vector<CompetitionRunner*> m_runners;
};
