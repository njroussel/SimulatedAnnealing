#pragma once

#include <mcaa/schedule.h>
#include <mcaa/common.h>

/**
 * \brief Constat Schedule used for MCMC simulated annealing
 */
class ConstantSchedule : public Schedule {
    public:
        /**
         * \brief Constructs a constant schedule
         *
         * \param beta
         *  The constant value of the temperature
         */
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

        /**
         * \brief Computes and returns the next value of the temperature for the 
         * current schedule
         */
        inline Float computeNextTemp() {
            return m_beta;
        }
};

