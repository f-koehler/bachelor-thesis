import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt
from math import sqrt

r1, s1, t1, S1 = np.loadtxt("data/parallelization/1.txt", unpack=True)
r2, s2, t2, S2 = np.loadtxt("data/parallelization/2.txt", unpack=True)
r4, s4, t4, S4 = np.loadtxt("data/parallelization/4.txt", unpack=True)
r8, s8, t8, S8 = np.loadtxt("data/parallelization/8.txt", unpack=True)

t1mean = np.mean(t1)
t2mean = np.mean(t2)
t4mean = np.mean(t4)
t8mean = np.mean(t8)
t1err  = sem(t1)
t2err  = sem(t2)
t4err  = sem(t4)
t8err  = sem(t8)

speedup1 = t1mean/t1mean
speedup2 = t1mean/t2mean
speedup4 = t1mean/t4mean
speedup8 = t1mean/t8mean
speedup1Err = sqrt((t1err/t1mean)**2+(t1mean*t1err/(t1mean**2))**2)
speedup2Err = sqrt((t1err/t2mean)**2+(t1mean*t2err/(t2mean**2))**2)
speedup4Err = sqrt((t1err/t4mean)**2+(t1mean*t4err/(t4mean**2))**2)
speedup8Err = sqrt((t1err/t8mean)**2+(t1mean*t8err/(t8mean**2))**2)

#plt.errorbar([1, 2, 4, 8], [t1mean, t2mean, t4mean, t8mean], [t1err, t2err, t4err, t8err])
plt.errorbar([1, 2, 4, 8], [speedup1, speedup2, speedup4, speedup8], [speedup1Err, speedup2Err, speedup4Err, speedup8Err])
plt.xticks([1, 2, 4, 8])
plt.xlim([0,9])
plt.ylim([0, int(speedup8)+1])
plt.xlabel("Threads")
plt.ylabel("Speedup")
plt.grid()
plt.savefig("plot/parallelization/plot.pdf")
