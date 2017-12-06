#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <mcaa/common.h>

void defPybindHelpers(pybind11::module &m);

inline int signFloat(Float x) {
    return x < 0 ? -1 : 1;
}

inline int signVector(VectorXf &x) {
    for (int i = 0; i < x.rows(); i++) {
        x(i) = signFloat(x(i));
    }
}

Float computeEnergy(MatrixXf const &patterns, VectorXf const &weights,
        VectorXf const &classes);

inline Float computeOverlap(VectorXf const &weights, VectorXf const &computedWeights) {
    return weights.dot(computedWeights) / weights.size();
}

inline Float computeGibbsBoltzmann(Float beta, Float currentE, Float nextE) {
    return  exp(-beta * (nextE - currentE));
}

VectorXf buildRandomWeights(int N, uint32_t seed = 0xDEADBEEF);

MatrixXf buildRandomPatterns(int N, int M,
        uint32_t seed = 0xDEADBEEF);

VectorXf buildClasses(VectorXf &weights, MatrixXf &patterns);
