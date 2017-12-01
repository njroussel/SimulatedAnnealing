#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <mcaa/sampler.h>

#define Float double

void defPybindHelpers(pybind11::module &m);

Float computeEnergy(std::vector<Float> const &patterns,
        std::vector<Sampler::Sample> const &weights,
        std::vector<Float> const &classes);

inline Float computeGibbsBoltzmann(Float beta, Float currentE, Float nextE) {
    return  exp(-beta * (nextE - currentE));
}
