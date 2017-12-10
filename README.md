# MCAA mini-project 

## Table of Contents :
  * [About](#about)
  * [Documentation](#documentation)
  * [Setup](#setup)
    * [Building](#building)
    * [Running](#running)

## About ##

This repository contains the code for the [Markov Chains and Aglorithimic Applications](http://ipgold.epfl.ch/~leveque/Markov_Chains/) class given at EPFL.
In short, it is an implementation of simulated annealing for the Ising perceptron. 

## Documentation ##

Code is directly commented, there is no additional documentation.

## Setup

The code base is written in C++ using [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) for all linear algebra related operations.
This is then built into a shared library which is accessible in Python thanks to [Pybind11](https://github.com/pybind/pybind11).
Finally a [Jupyter Notebook](http://jupyter.org/) is used to run the previous code in Python.

### Building

On a Linux or equivalent system using gcc, you can simply: 

```
git clone --recursive git@github.com:njroussel/MCAA.git
pip install ./MCMCKernels
```

The whole build system uses CMake, it is therfore a requirement for building an running this project.

Note that the Jupyter notebooks will need specific packages which can be installed through `pip`.


### Running

The notebook `Running.ipynb` should already have the cells rendered, you can also simply just run the again.

