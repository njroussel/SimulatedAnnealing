#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/common.h>
#include <mcaa/sampler.h>

void defPybindHelpers(pybind11::module &m);

inline int signFloat(Float x) {
    return x < 0 ? -1 : 1;
}

Float computeEnergy(MatrixXf const &patterns,
        VectorXf const &weights,
        VectorXf const &classes);

inline Float computeGibbsBoltzmann(Float beta, Float currentE, Float nextE) {
    return  exp(-beta * (nextE - currentE));
}

VectorXf buildRandomWeights(int N, uint32_t seed = 0xDEADBEEF);

MatrixXf buildRandomPatterns(int N, int M,
        uint32_t seed = 0xDEADBEEF);

VectorXf buildClasses(VectorXf &weights, MatrixXf &patterns);
