#include <iostream>
#include <pybind11/pybind11.h>
#include <mcaa/common.h>
#include <mcaa/helpers.h>
#include <mcaa/sampler.h>
#include <mcaa/mcmc.h>
#include <Eigen/Dense>

namespace py = pybind11;

using namespace std;

PYBIND11_MODULE(mcaa, m) {
    m.doc() = R"pbdoc(
        MCAA mini-project implementation
        -----------------------

        .. currentmodule:: mcaa

        .. autosummary::
           :toctree: _generate

    )pbdoc";

    defPybindHelpers(m);
    Sampler::defPybind(m);
    MCMCRunner::defPybind(m);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}


int main() {
    Float BETA = 1.0;
    Float ALPHA = 2.0;
    int N = 10;
    int M = (int) ALPHA * N;;
    int T = 10 * N;
    int MEASURE_STEP = 1;

    VectorXf weights = buildRandomWeights(N, 420);
    MatrixXf patterns = buildRandomPatterns(N, M, 421);
    VectorXf classes = buildClasses(weights, patterns);

    Sampler sampler(N, 422);
    MCMCRunner runner(T, 1,  BETA, sampler, patterns, classes, 423);   

    VectorXf &samples = sampler.getSamples();
    for (int i = 0; i < N; i++) {
        cout << weights[i] << "    " << samples(i) << endl;
    }
    runner.run();
    cout << "-----------" << endl;
    samples = sampler.getSamples();
    for (int i = 0; i < N; i++) {
        cout << weights[i] << "    " << samples[i] << endl;
    }

    computeEnergy(patterns, sampler.getSamples(), classes); 
}
