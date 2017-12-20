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
The report and its figures are in the `report` folder.

## Setup

The code base is written in C++ using [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) for all linear algebra related operations.
This is then built into a shared library which is accessible as Python module thanks to [Pybind11](https://github.com/pybind/pybind11).
Finally a [Jupyter Notebook](http://jupyter.org/) is used to run the previous Python code.

### Building

On a Linux or equivalent system using gcc, you can simply: 

```
git clone git@github.com:njroussel/MCAA.git --recursive
pip install ./MCAA
```

The whole build system uses CMake, it is therfore a requirement for building and running this project.

Note that the Jupyter notebooks will need specific packages which can be installed through `pip`.


### Running

In the `python` folder, there are several notebooks which contain examples of how to run code. They should already have the cells rendered, you can also simply just run them again if you change their configuration.
