#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/sampler.h>

#define Float double

void defPybindHelpers(pybind11::module &m);

inline int signFloat(Float x) {
    return x < 0 ? -1 : 1;
}

Float computeEnergy(std::vector<std::vector<Float>> const &patterns,
        std::vector<Sampler::Sample> const &weights,
        std::vector<int> const &classes);

inline Float computeGibbsBoltzmann(Float beta, Float currentE, Float nextE) {
    return  exp(-beta * (nextE - currentE));
}

std::vector<int> buildRandomWeights(int N, uint32_t seed = 0xDEADBEEF);

std::vector<std::vector<Float>> buildRandomPatterns(int N, int M, uint32_t seed = 0xDEADBEEF);

std::vector<int> buildClasses(std::vector<int> &weights, std::vector<std::vector<Float>> &patterns);
