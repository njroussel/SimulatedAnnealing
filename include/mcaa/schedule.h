#pragma once

#include <mcaa/common.h>

/**
 * \brief Abstract schedule used for MCMC simulated annealing.
 */
class Schedule {
    public:

        /**
         * \brief Pybind bindings for Schedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<Schedule>(m, "schedule");
        }

        /**
         * \brief Computes and returns the next value of the temperature.
         */
        virtual Float computeNextTemp() = 0;
};

