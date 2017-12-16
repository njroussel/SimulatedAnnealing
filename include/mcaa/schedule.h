#pragma once

#include <mcaa/common.h>

/**
 * \brief Schedule used for MCMC simulated annealing
 */

class Schedule {
    public:

        Schedule() : m_beta(0), currentIter(0) {
        }

        /**
         * \brief Pybind bindings for Schedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<Schedule>(m, "schedule");
        }

        virtual Float computeNextTemp() = 0;

    protected:
        Float m_beta;
        int currentIter;
};

