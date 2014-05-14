import os
import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

# read files
Id   = []
S    = []
Serr = []
T    = []
Terr = []
for f in os.listdir("./data"):
    idx, s, t = np.loadtxt("./data/"+f, unpack=True)
    S.append(np.mean(s))
    Serr.append(sem(s))
    T.append(np.mean(t))
    Terr.append(sem(s))

N = np.loadtxt("./problems.txt")
n = np.array([len(bin(N[i]))-2 for i in N])

plt.errorbar(n, T, Terr)
plt.show()
