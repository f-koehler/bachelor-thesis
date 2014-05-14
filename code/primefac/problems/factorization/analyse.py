import os
import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

count = 9

# read files
S    = []
Serr = []
T    = []
Terr = []
for i in range(0, count):
    idx, s, t = np.loadtxt("./data/"+str(i)+".txt", unpack=True)
    S.append(np.mean(s))
    Serr.append(sem(s))
    T.append(np.mean(t))
    Terr.append(sem(s))

S = np.array(S)
T = np.array(T)

N = np.loadtxt("./problems.txt", unpack=True, dtype=np.int64)
n = np.array([len(bin(i))-2 for i in N])

plt.plot(n, T)
plt.show()
