import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt
from math import sqrt

r1, s1, t1, S1 = np.loadtxt("data/parallelization/1.txt", unpack=True)
r2, s2, t2, S2 = np.loadtxt("data/parallelization/2.txt", unpack=True)
r3, s3, t3, S3 = np.loadtxt("data/parallelization/3.txt", unpack=True)
r4, s4, t4, S4 = np.loadtxt("data/parallelization/4.txt", unpack=True)
r5, s5, t5, S5 = np.loadtxt("data/parallelization/5.txt", unpack=True)
r6, s6, t6, S6 = np.loadtxt("data/parallelization/6.txt", unpack=True)
r7, s7, t7, S7 = np.loadtxt("data/parallelization/7.txt", unpack=True)
r8, s8, t8, S8 = np.loadtxt("data/parallelization/8.txt", unpack=True)

t1mean = np.mean(t1)
t2mean = np.mean(t2)
t3mean = np.mean(t3)
t4mean = np.mean(t4)
t5mean = np.mean(t5)
t6mean = np.mean(t6)
t7mean = np.mean(t7)
t8mean = np.mean(t8)
t1err  = sem(t1)
t2err  = sem(t2)
t3err  = sem(t3)
t4err  = sem(t4)
t5err  = sem(t5)
t6err  = sem(t6)
t7err  = sem(t7)
t8err  = sem(t8)

speedup1 = t1mean/t1mean
speedup2 = t1mean/t2mean
speedup3 = t1mean/t3mean
speedup4 = t1mean/t4mean
speedup5 = t1mean/t5mean
speedup6 = t1mean/t6mean
speedup7 = t1mean/t7mean
speedup8 = t1mean/t8mean
speedup1Err = sqrt((t1err/t1mean)**2+(t1mean*t1err/(t1mean**2))**2)
speedup2Err = sqrt((t1err/t2mean)**2+(t1mean*t2err/(t2mean**2))**2)
speedup3Err = sqrt((t1err/t3mean)**2+(t1mean*t3err/(t3mean**2))**2)
speedup4Err = sqrt((t1err/t4mean)**2+(t1mean*t4err/(t4mean**2))**2)
speedup5Err = sqrt((t1err/t5mean)**2+(t1mean*t5err/(t5mean**2))**2)
speedup6Err = sqrt((t1err/t6mean)**2+(t1mean*t6err/(t6mean**2))**2)
speedup7Err = sqrt((t1err/t7mean)**2+(t1mean*t7err/(t7mean**2))**2)
speedup8Err = sqrt((t1err/t8mean)**2+(t1mean*t8err/(t8mean**2))**2)

plt.errorbar([1, 2, 3, 4, 5, 6, 7, 8], [speedup1, speedup2, speedup3, speedup4, speedup5, speedup6, speedup7, speedup8], [speedup1Err, speedup2Err, speedup3Err, speedup4Err, speedup5Err, speedup6Err, speedup7Err, speedup8Err], fmt="x")
plt.xticks([1, 2, 3, 4, 5, 6, 7, 8])
plt.xlim([0,9])
plt.ylim([0, int(speedup8)+1])
plt.xlabel("Threads")
plt.ylabel("Speedup $\\frac{\\tau_1}{\\tau_i}$")
plt.grid()
plt.savefig("plot/parallelization/plot.pdf")
