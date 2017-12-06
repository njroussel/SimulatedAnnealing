#include <pcg32.h>
#include <mcaa/helpers.h>

using namespace std;

void defPybindHelpers(pybind11::module &m) {
    m.def("computeEnergy", &computeEnergy)
        .def("computeGibbsBoltzmann", &computeGibbsBoltzmann)
        .def("buildRandomWeights", &buildRandomWeights)
        .def("buildRandomPatterns", &buildRandomPatterns)
        .def("buildClasses", &buildClasses);
}

Float computeEnergy(MatrixXf const &patterns,
        VectorXf const &weights,
        VectorXf const &classes) {
    VectorXf computedClasses = patterns * weights; 
    signVector(computedClasses);
    VectorXf classesDiff = classes - computedClasses;
    Float sum = classesDiff.dot(classesDiff);

    return 0.5 * sum; 
}

VectorXf buildRandomWeights(int N, uint32_t seed) {
    pcg32 rng;
    rng.seed(seed);
    VectorXf out(N);

    for(int i = 0; i < N; i++) {
        out(i) = signFloat(rng.nextFloat() - 0.5); 
    }

    return out;
}

MatrixXf buildRandomPatterns(int N, int M, uint32_t seed) {
    pcg32 rng;
    rng.seed(seed);
    MatrixXf out(M, N);

    for(int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            out(i, j) = rng.nextFloat();
        }
    }

    return out;
}

VectorXf buildClasses(VectorXf &weights, MatrixXf &patterns) {
    VectorXf out = patterns * weights;
    signVector(out);

    return out;
}
