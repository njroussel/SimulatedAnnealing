import mcaa
import random as rng
import matplotlib.pyplot as plt
import numpy as np

def linearRunner(offset, slope, alpha, n, tFactor, measureStep, runCount, threadCount): 
    # CONSTANTS
    OFFSET = offset
    SLOPE = slope
    ALPHA = alpha
    N = n
    M = int(ALPHA * N) 
    T = tFactor * N
    MEASURE_STEP = measureStep
    RUN_COUNT = runCount 
    THREAD_COUNT = threadCount

    # SEEDS
    weightsSeed = rng.randint(0,2**32-1)
    patternsSeed = rng.randint(0,2**32-1)
    samplerSeeds = [rng.randint(0,2**32-1) for i in range(RUN_COUNT)]
    runnerSeeds = [rng.randint(0,2**32-1) for i in range(RUN_COUNT)]

    # INPUT VARIABLES 
    weights = mcaa.buildRandomWeights(N, weightsSeed)
    patterns = mcaa.buildRandomPatterns(N, M, patternsSeed)
    classes = mcaa.buildClasses(weights, patterns)

    # SAMPLERS & RUNNERS
    samplers = [mcaa.sampler(N, samplerSeeds[i]) for i in range(RUN_COUNT)]
    schedules = [mcaa.continuousLinearSchedule(T, OFFSET, SLOPE) for i in range(RUN_COUNT)]
    runners = [mcaa.MCMCRunner(T, MEASURE_STEP, schedules[i], samplers[i], weights, patterns, classes, runnerSeeds[i])            for i in range(RUN_COUNT)]
    multiRunner = mcaa.multiMCMCRunner(THREAD_COUNT, [runner.getPointer() for runner in runners]) 

    # RUN
    multiRunner.runAll()

    # OUTPUTS 
    allEMeasures = multiRunner.getEMeasures() / M
    allOverlapMeasures = multiRunner.getOverlapMeasures()

    return allEMeasures, allOverlapMeasures
