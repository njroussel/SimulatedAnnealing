#include <pybind11/pybind11.h>

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


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
