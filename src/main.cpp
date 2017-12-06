#include <iostream>
#include <pybind11/pybind11.h>
#include <Eigen/Dense>
#include <mcaa/common.h>
#include <mcaa/helpers.h>
#include <mcaa/sampler.h>
#include <mcaa/mcmc.h>
#include <mcaa/multimcmc.h>

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
    MultiMCMCRunner::defPybind(m);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

/*
int main() {
    Float BETA = 1.0;
    Float ALPHA = 1.0;
    int N = 10;
    int M = (int) ALPHA * N;;
    int T = 1 * N;
    int MEASURE_STEP = 1;

    VectorXf weights = buildRandomWeights(N, 420);
    MatrixXf patterns = buildRandomPatterns(N, M, 421);
    VectorXf classes = buildClasses(weights, patterns);

    Sampler sampler1(N, 422);
    MCMCRunner runner1(T, 1,  BETA, sampler1, weights, patterns, classes, 423);   
    Sampler sampler2(N, 424);
    MCMCRunner runner2(T, 1,  BETA, sampler2, weights, patterns, classes, 425); 

    std::vector<MCMCRunner*> runners;
    runners.push_back(&runner1);
    runners.push_back(&runner2);
    MultiMCMCRunner multi(2, runners);
    multi.runAll();

    multi.getEMeasures();
    multi.getOverlapMeasures();
}
*/
