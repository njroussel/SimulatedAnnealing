#pragma once

#include <cmath>
#include <mcaa/schedule.h>
#include <mcaa/schedule.h>
#include <mcaa/common.h>

/**
 * \brief Continous logarithmic Schedule used for MCMC simulated annealing.
 */
class ContinuousLogarithmicSchedule : public Schedule {
    public:
        /**
         * \brief Constructs a continuous logarithmic schedule.
         *
         * \param iterationCount 
         *  The number of iterations durich which the schedule will be ran.
         *
         * \param offset 
         *  The offset value of the logarithmic function (initial temperature).
         *
         * \param logarithmOffset 
         *  The offset in the logarithm term.
         */
        ContinuousLogarithmicSchedule(int iterationCount, Float offset, Float logOffset) :
            Schedule(), m_currentTime(0), m_stepSize(1.0 / iterationCount),
            m_offset(offset), m_logOffset(logOffset) { } 

        /**
         * \brief Pybind bindings for ContinuousLogarithmicSchedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<ContinuousLogarithmicSchedule, Schedule>(m, "continuousLogarithmicSchedule")
                .def(pybind11::init<int, Float, Float>(),
                        pybind11::arg("iterationCount"),
                        pybind11::arg("offset"),
                        pybind11::arg("logOffset"));
        }

        /**
         * \brief Computes and returns the next value of the temperature.
         */
        inline Float computeNextTemp() {
            float result = m_offset * std::log(m_currentTime + m_logOffset);
            m_currentTime += m_stepSize;
            return result;
        }

    private:
        Float m_stepSize;
        Float m_currentTime;
        Float m_offset;
        Float m_logOffset;
};

