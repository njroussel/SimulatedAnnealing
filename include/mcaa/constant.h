#pragma once

#include <mcaa/schedule.h>
#include <mcaa/common.h>

/**
 * \brief Constat Schedule used for MCMC simulated annealing
 */

class ConstantSchedule : public Schedule {
    public:
        ConstantSchedule(Float beta) : Schedule() {
            m_beta = beta;
        } 

        /**
         * \brief Pybind bindings for Schedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<ConstantSchedule, Schedule>(m, "constantSchedule")
                .def(pybind11::init<Float>(),
                        pybind11::arg("beta"));
        }

        inline Float computeNextTemp() {
            return m_beta;
        }
};

