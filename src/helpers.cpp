#include <cmath>
#include <mcaa/helpers.h>

using namespace std;

void defPybindHelpers(pybind11::module &m) {
    m.def("computeEnergy", &computeEnergy)
        .def("computeGibbsBoltzmann", &computeGibbsBoltzmann);
}

Float computeEnergy(std::vector<Float> const &patterns,
        std::vector<Sampler::Sample> const &weights,
        std::vector<Float> const &classes) {
    Float result = 0;

    return 0.5 * result;
}
