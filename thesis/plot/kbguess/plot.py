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
    _id, _s, _t, _n = np.loadtxt("data/kbguess/data/"+str(i)+".txt", unpack=True)
    s.append(np.mean(_s))
    sErr.append(sem(_s))
    t.append(np.mean(_t))
    tErr.append(sem(_t))
    n.append(np.mean(_n))
    nErr.append(sem(_n))

t = np.array(t)*1e-6
tErr = np.array(tErr)*1e-6

kTicks = np.array((k+[1])[::2])
kLabel = ["$"+str(int(_k))+"^3$" for _k in kTicks]
kTicks = np.concatenate([np.array([0]), kTicks])
kLabel = ["$0$"]+kLabel

plt.errorbar(k, s, sErr)
plt.grid()
plt.xticks(kTicks, kLabel)
plt.xlim([np.min(k)-1, np.max(k)+1])
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("Erfolgsrate")
plt.savefig("plot/kbguess/success.pdf")
plt.close()

plt.errorbar(k, t, tErr)
plt.grid()
plt.xlim([np.min(k)-1, np.max(k)+1])
plt.xticks(kTicks, kLabel)
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("$T/\si{\second}$")
plt.savefig("plot/kbguess/time.pdf")
plt.close()

plt.errorbar(k, n, nErr)
plt.grid()
plt.xlim([np.min(k)-1, np.max(k)+1])
plt.xticks(kTicks, kLabel)
plt.xlabel("$k_\\mathrm{B}$")
plt.ylabel("Schritte")
plt.savefig("plot/kbguess/steps.pdf")
plt.close()
