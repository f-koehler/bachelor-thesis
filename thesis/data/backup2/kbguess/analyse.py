import os
import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

k = np.linspace(1, 16, 16)

s = []
sErr = []
t = []
tErr = []
n = []
nErr = []
for i in range(0, k.shape[0]):
    _id, _s, _t, _n = np.loadtxt("data/"+str(i)+".txt", unpack=True)
    s.append(np.mean(_s))
    sErr.append(sem(_s))
    t.append(np.mean(_t))
    tErr.append(sem(_t))
    n.append(np.mean(_n))
    nErr.append(sem(_n))

plt.errorbar(k, s, sErr)
plt.show()
