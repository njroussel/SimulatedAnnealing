#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
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
                .def("mutate", &Sampler::mutate)
                .def("getSamples", &Sampler::getSamples);
        }

        inline int size() {
            return m_sample.values.size();
        }

        void accept();

        void reject();

        void mutate(int index);

        inline VectorXf& getSamples() {
            return m_sample.values;
        }

    protected:

        struct Sample {
            Sample(int N, uint32_t seed = 0xDEADBEEF); 

            inline void swap(int index) {
                values(index) *= -1.0;
            }

            VectorXf values; 
        };

        Sample m_sample;
        uint32_t m_currentIndex;
};

