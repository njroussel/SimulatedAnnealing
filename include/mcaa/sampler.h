#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/common.h>

class Sampler {
    public:

        Sampler(int N, uint32_t seed = 0xDEADBEEF); 

        static void defPybind(pybind11::module &m) {
            pybind11::class_<Sampler>(m, "sampler")
                .def(pybind11::init<int, uint32_t>(),
                        pybind11::arg("N"),
                        pybind11::arg("seed") = 0xDEADBEEF)
                .def("accept", &Sampler::accept)
                .def("reject", &Sampler::reject)
                .def("swap", &Sampler::swap)
                .def("getSamples", &Sampler::getSamples);
        }

        inline int size() {
            return m_X.values.size();
        }

        void accept(int index);

        void reject(int index);

        void swap(int index);

        inline VectorXf& getSamples() {
            return m_X.values;
        }

    protected:
        struct Sample {
            Sample(int N); 

            inline void swap(int index) {

            }

            VectorXf values; 
        };

        pcg32 m_rng;
        Sample m_X;

        uint32_t m_currentIndex = 0;
};

