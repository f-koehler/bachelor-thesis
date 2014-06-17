import os
import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

k1 = np.linspace(1, 16, 16)
k2 = np.linspace(4, 28, 24)

s1 = []
sErr1 = []
t1 = []
tErr1 = []
n1 = []
nErr1 = []
for i in range(0, k1.shape[0]):
    _id, _s, _t, _n = np.loadtxt("data/kbguess/data/"+str(i)+".txt", unpack=True)
    s1.append(np.mean(_s))
    sErr1.append(sem(_s))
    t1.append(np.mean(_t))
    tErr1.append(sem(_t))
    n1.append(np.mean(_n))
    nErr1.append(sem(_n))

s2 = []
sErr2 = []
t2 = []
tErr2 = []
n2 = []
nErr2 = []
for i in range(0, k2.shape[0]):
    _id, _s, _t, _n = np.loadtxt("data/kbguess2/data/"+str(i)+".txt", unpack=True)
    s2.append(np.mean(_s))
    sErr2.append(sem(_s))
    t2.append(np.mean(_t))
    tErr2.append(sem(_t))
    n2.append(np.mean(_n))
    nErr2.append(sem(_n))

t1 = np.array(t1)*1e-6
tErr1 = np.array(tErr1)*1e-6
t2 = np.array(t2)*1e-6
tErr2 = np.array(tErr2)*1e-6

kTicks = np.arange(2, 28, 2)
kLabel = ["$"+str(int(_k))+"^3$" for _k in kTicks]
kTicks = np.concatenate([np.array([0]), kTicks])
kLabel = ["$0$"]+kLabel

plt.errorbar(k1, s1, sErr1, label="Durchlauf 1")
plt.errorbar(k2, s2, sErr2, label="Durchlauf 2")
plt.grid()
plt.xticks(kTicks, kLabel)
plt.xlim([kTicks.min(), kTicks.max()+1])
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("Erfolgsrate")
plt.legend(loc=4)
plt.savefig("plot/kbguess/success.pdf")
plt.close()

plt.errorbar(k1, t1, tErr1, label="Durchlauf 1")
plt.errorbar(k2, t2, tErr2, label="Durchlauf 2")
plt.grid()
plt.xlim([kTicks.min(), kTicks.max()+1])
plt.xticks(kTicks, kLabel)
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("$T/\si{\second}$")
plt.legend(loc=1)
plt.savefig("plot/kbguess/time.pdf")
plt.close()

plt.errorbar(k1, n1, nErr1)
plt.errorbar(k2, n2, nErr2)
plt.grid()
plt.xlim([kTicks.min(), kTicks.max()+1])
plt.xticks(kTicks, kLabel)
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("Schritte")
plt.savefig("plot/kbguess/steps.pdf")
plt.close()
