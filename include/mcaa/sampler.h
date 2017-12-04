#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pcg32.h>

class Sampler {
    public:
        struct Sample {
            Sample(int _value, int _valueBackup) :
                value(_value), valueBackup(_valueBackup) { }

            static void defPybind(pybind11::module &m) {
                pybind11::class_<Sample>(m, "sample")
                    .def(pybind11::init<int, int>(),
                            pybind11::arg("value"),
                            pybind11::arg("valueBackup"))
                    .def("backup", &Sample::backup)
                    .def("restore", &Sample::restore);
            }

            void backup() {
                valueBackup = value;
            }

            void restore() {
                value = valueBackup;
            }

            int value = 0;
            int valueBackup = 0;
        };

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
            return m_X.size();
        }

        void accept(int index);

        void reject(int index);

        void swap(int index);

        inline std::vector<Sample>& getSamples() {
            return m_X;
        }

    protected:
        pcg32 m_rng;
        std::vector<Sample> m_X;
};

