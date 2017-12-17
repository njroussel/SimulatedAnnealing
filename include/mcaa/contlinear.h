#pragma once

#include <mcaa/schedule.h>
#include <mcaa/common.h>

/**
 * \brief Continous linear Schedule used for MCMC simulated annealing.
 */
class ContinuousLinearSchedule : public Schedule {
    public:
        /**
         * \brief Constructs a continuous linear schedule.
         *
         * \param iterationCount 
         *  The number of iterations durich which the schedule will be ran.
         *
         * \param offset 
         *  The offset value of the affine function (initial temperature).
         *
         * \param slope
         *  The slope of the affine function (step size).
         */
        ContinuousLinearSchedule(int iterationCount, Float offset, Float slope) :
            Schedule(), m_currentTime(0), m_stepSize(1.0 / iterationCount),
            m_offset(offset), m_slope(slope) { } 

        /**
         * \brief Pybind bindings for ContinuousLinearSchedule. 
         */
        static void defPybind(pybind11::module &m) {
            pybind11::class_<ContinuousLinearSchedule, Schedule>(m, "continuousLinearSchedule")
                .def(pybind11::init<int, Float, Float>(),
                        pybind11::arg("iterationCount"),
                        pybind11::arg("offset"),
                        pybind11::arg("slope"));
        }

        /**
         * \brief Computes and returns the next value of the temperature.
         */
        inline Float computeNextTemp() {
            float result = m_offset + (m_slope * m_currentTime);
            m_currentTime += m_stepSize;
            return result;
        }

    private:
        Float m_stepSize;
        Float m_currentTime;
        Float m_offset;
        Float m_slope;
};

