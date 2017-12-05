#include <cmath>
#include <pcg32.h>
#include <iostream>
#include <ctime>
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
    clock_t begin = clock();
    Float result = 0;
    int M = patterns.size();
    int N = weights.size();

    for (int i = 0; i < M; i++) {
        Float dotProduct = 0;
        for (int j = 0; j < N; j++) {
            dotProduct += patterns(i, j) * weights[j];
        }

        int tmp = classes[i] - signFloat(dotProduct);
        result += tmp * tmp;
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;

    return 0.5 * result;
}

VectorXf buildRandomWeights(int N, uint32_t seed) {
    pcg32 rng;
    rng.seed(seed);
    VectorXf out(N);

    for(int i = 0; i < N; i++) {
        out[i] = signFloat(rng.nextFloat() - 0.5); 
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
    int M = patterns.size();
    int N = weights.size();
    VectorXf out(M);

    for (int i = 0; i < M; i++) {
        Float dotProduct = 0;
        for (int j = 0; j < N; j++) {
            dotProduct += patterns(i, j) * weights[j];
        }

        out[i] = signFloat(dotProduct);
    }

    return out;
}
