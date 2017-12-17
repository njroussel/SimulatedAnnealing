#pragma once

#include <pcg32.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <mcaa/common.h>

/**
 * \brief Sampler used for MCMC Ising perceptron
 */
class Sampler {
    public:

        /**
         * \brief Constructs a sampler of a given size.
         *
         * \param N
         *  The length of the weights in the Ising perceptron model.
         *
         * \param seed
         *  A random seed used for this sampler.
         */
        Sampler(int N, uint32_t seed = 0xDEADBEEF); 

        /**
         * \brief Pybind bindings for Sampler. 
         */
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

        /**
         * \brief Returns the length of the weights in the Ising model.
         */
        inline int size() {
            return m_sample.values.size();
        }

        /**
         * \brief Accepts the currently proposed mutation.
         */
        void accept();

        /**
         * \brief Rejects the currently proposed mutation.
         */
        void reject();


        /**
         * \brief Mutates the weights for the given index
         *
         * \param index
         *  The index of the weight which should be changed.
         */
        void mutate(int index);

        /**
         * \brief Returns the current samples (weights) of the Ising model.
         */
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

