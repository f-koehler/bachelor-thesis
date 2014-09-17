import os
import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

numbers = np.loadtxt("./numbers.txt", dtype=np.int64)

# determine an array where each n appears only once
n = []
y = 0
for _n in np.array([len(bin(N))-2 for N in numbers]):
    if _n == 7:
        print(numbers[y])
        exit()
    if len(n) == 0:
        n.append(_n)
    elif np.in1d(np.array([_n]), np.array(n)) == False:
        n.append(_n)
    y += 1
n = np.array(n)

# create arrays for T and TErr
T = []
TErr = []
steps = []
stepsErr = []
for i in range(0, n.shape[0]):
    T.append([])
    TErr.append([])
    steps.append([])
    stepsErr.append([])

# go through all datasets
for i in range(0, numbers.shape[0]):
    # load set
    _id, _s, _t, _steps = np.loadtxt("./data/"+str(i)+".txt", unpack=True)

    # determine corresponding n
    nCurr = len(bin(numbers[i]))-2

    # find the index of nCurr in n
    pos = 0
    for j in range(0, n.shape[0]):
        if n[j] == nCurr:
            pos = j

    # calculate t and tErr
    t = np.mean(_t)
    tErr = sem(_t)

    # calculate steps and stepsErr
    st = np.mean(_steps)
    stErr = sem(_steps)

    # add current value
    T[pos].append(t)
    TErr[pos].append(tErr)
    steps[pos].append(steps)
    stepsErr[pos].append(stepsErr)

#
tmp = np.array(T)
T = []
for t in tmp:
    T.append(np.mean(t))
T = np.array(T)

#
tmp = np.array(TErr)
TErr = []
for line in tmp:
    tot = 0
    for err in line:
        tot += err*err
    TErr.append(np.sqrt(tot))
TErr = np.arrayi(TErr)

#
tmp = np.array(steps)
steps = []
for line in tmp:
    steps.append(np.mean(line))
steps = np.array(steps)


# plot
#plt.errorbar(n**4, T, TErr, fmt="x")
plt.plot(n, steps)
plt.show()
