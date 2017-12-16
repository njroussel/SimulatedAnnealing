#pragma once

#include <mcaa/common.h>

/**
 * \brief Abstract schedule used for MCMC simulated annealing
 */
class Schedule {
    public:

        /**
         * \brief Abstract constructor, simply initializes a couple class members
         */
        Schedule() : m_beta(0), currentIter(0) {
        }

        /**
         * \brief Pybind bindings for Schedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<Schedule>(m, "schedule");
        }

        /**
         * \brief Computes and returns the next value of the temperature for the 
         * current schedule
         */
        virtual Float computeNextTemp() = 0;

    protected:
        Float m_beta;
        int currentIter;
};

