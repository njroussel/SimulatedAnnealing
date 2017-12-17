#pragma once

#include <cmath>
#include <mcaa/schedule.h>
#include <mcaa/schedule.h>
#include <mcaa/common.h>

/**
 * \brief Continous polynomial Schedule used for MCMC simulated annealing.
 */
class ContinuousPolynomialSchedule : public Schedule {
    public:
        /**
         * \brief Constructs a continuous polynomial schedule.
         *
         * \param iterationCount 
         *  The number of iterations durich which the schedule will be ran.
         *
         * \param offset 
         *  The offset value of the polynomial function (initial temperature).
         *
         * \param exponent 
         *  The exponent of the polynomial function (step size).
         */
        ContinuousPolynomialSchedule(int iterationCount, Float offset, Float exponent) :
            Schedule(), m_currentTime(0), m_stepSize(1.0 / iterationCount),
            m_offset(offset), m_exponent(exponent) { } 

        /**
         * \brief Pybind bindings for ContinuousPolynomialSchedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<ContinuousPolynomialSchedule, Schedule>(m, "continuousPolynomialSchedule")
                .def(pybind11::init<int, Float, Float>(),
                        pybind11::arg("iterationCount"),
                        pybind11::arg("offset"),
                        pybind11::arg("exponent"));
        }

        /**
         * \brief Computes and returns the next value of the temperature.
         */
        inline Float computeNextTemp() {
            float result = m_offset * std::pow(m_currentTime, m_exponent);
            m_currentTime += m_stepSize;
            return result;
        }

    private:
        Float m_stepSize;
        Float m_currentTime;
        Float m_offset;
        Float m_exponent;
};

