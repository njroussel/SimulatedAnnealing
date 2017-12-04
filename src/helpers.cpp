#include <cmath>
#include <mcaa/helpers.h>
#include <pcg32.h>

using namespace std;

void defPybindHelpers(pybind11::module &m) {
    m.def("computeEnergy", &computeEnergy)
        .def("computeGibbsBoltzmann", &computeGibbsBoltzmann)
        .def("buildRandomWeights", &buildRandomWeights)
        .def("buildRandomPatterns", &buildRandomPatterns)
        .def("buildClasses", &buildClasses);
}

Float computeEnergy(vector<vector<Float>> const &patterns,
        vector<Sampler::Sample> const &weights,
        vector<int> const &classes) {
    Float result = 0;
    int M = patterns.size();
    int N = weights.size();

    for (int i = 0; i < M; i++) {
        Float dotProduct = 0;
        for (int j = 0; j < N; j++) {
            dotProduct += patterns[i][j] * weights[j].value;
        }

        int tmp = classes[i] - signFloat(dotProduct);
        result += tmp * tmp;
    }

    return 0.5 * result;
}

vector<int> buildRandomWeights(int N, uint32_t seed) {
    pcg32 rng;
    rng.seed(seed);
    vector<int> out(N);

    for(int i = 0; i < N; i++) {
        out[i] = signFloat(rng.nextFloat() - 0.5); 
    }

    return out;
}

vector<vector<Float>> buildRandomPatterns(int N, int M, uint32_t seed) {
    pcg32 rng;
    rng.seed(seed);
    vector<vector<Float>> out(M);

    for(int i = 0; i < M; i++) {
        vector<Float> pattern(N);
        for (int i = 0; i < N; i++) {
            pattern[i] = rng.nextFloat();
        }

        out[i] = pattern;
    }

    return out;
}

vector<int> buildClasses(vector<int> &weights, vector<vector<Float>> &patterns) {
    int M = patterns.size();
    int N = weights.size();
    vector<int> out(M);

    for (int i = 0; i < M; i++) {
        Float dotProduct = 0;
        for (int j = 0; j < N; j++) {
            dotProduct += patterns[i][j] * weights[j];
        }

        out[i] = signFloat(dotProduct);
    }

    return out;
}
