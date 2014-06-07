import os
from scipy.stats import sem
import numpy as np

numbers = np.loadtxt("data/runtime/numbers.txt", dtype=np.int64)

# determine an array where each n appears only once
n = []
y = 0
for _n in np.array([len(bin(N))-2 for N in numbers]):
    if len(n) == 0:
        n.append(_n)
    elif np.in1d(np.array([_n]), np.array(n)) == False:
        n.append(_n)
    y += 1
n = np.array(n)

# find the index of a n value in the n list
def nFind(val):
    for i in range(0, n.shape[0]):
        if n[i] == val:
            return i
    return None

# create empty arrays for success, time, steps and their errors
success      = []
successError = []
time         = []
timeError    = []
steps        = []
stepsError   = []
for i in range(0, n.shape[0]):
    success.append([])
    successError.append([])
    time.append([])
    timeError.append([])
    steps.append([])
    stepsError.append([])

# load all datasets
for i in range(0, numbers.shape[0]):
    _run, _success, _time, _steps = np.loadtxt("data/runtime/data/"+str(i)+".txt", unpack=True)

    pos = nFind(len(bin(numbers[i]))-2)

    success[pos].append(np.mean(_success))
    successError[pos].append(sem(_success))
    time[pos].append(np.mean(_time))
    timeError[pos].append(sem(_time))
    steps[pos].append(np.mean(_steps))
    stepsError[pos].append(sem(_steps))

# calculate average values and their errors
for i in range(0, n.shape[0]):
    success[i] = np.mean(success[i])
    time[i]    = np.mean(time[i])
    steps[i]   = np.mean(steps[i])
    
    a = 0
    b = 0
    c = 0
    for j in range(0, len(successError[i])):
        a += successError[i][j]**2
        b += timeError[i][j]**2
        c += stepsError[i][j]**2
    a = np.sqrt(a)/len(successError[i])
    b = np.sqrt(b)/len(successError[i])
    c = np.sqrt(c)/len(successError[i])

    successError[i] = a
    timeError[i] = b
    stepsError[i] = c

np.savetxt("data/runtime/results.txt", np.c_[n, success, successError, time, timeError, steps, stepsError], fmt="%4f")
