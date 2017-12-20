import mcaa
import random as rng
import matplotlib.pyplot as plt
import numpy as np

def competitionRunner(X, Y, schedules, m, n, tFactor, measureStep): 
    # CONSTANTS
    SCHEDULES = schedules
    N = n
    M = m
    T = tFactor * N
    MEASURE_STEP = measureStep
    RUN_COUNT = 4
    THREAD_COUNT = 4

    # SEEDS
    samplerSeeds = [rng.randint(0,2**32-1) for i in range(RUN_COUNT)]
    runnerSeeds = [rng.randint(0,2**32-1) for i in range(RUN_COUNT)]

    # INPUT VARIABLES 
    patterns = X
    classes = Y

    # SAMPLERS & RUNNERS
    samplers = [mcaa.sampler(N, samplerSeeds[i]) for i in range(RUN_COUNT)]
    runners = [mcaa.CompetitionRunner(T, MEASURE_STEP, SCHEDULES[i], samplers[i], patterns, classes, runnerSeeds[i]) \
               for i in range(RUN_COUNT)]
    multiRunner = mcaa.multiCompetitionRunner(THREAD_COUNT, [runner.getPointer() for runner in runners]) 

    # RUN
    multiRunner.runAll()

    # OUTPUTS 
    allEMeasures = multiRunner.getEMeasures() / M
    allWeights = [sampler.getSamples() for sampler in samplers]

    return allEMeasures, allWeights
