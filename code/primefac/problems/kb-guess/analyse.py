import numpy as np
from scipy.stats import sem
from matplotlib import pyplot as plt

plt.rc("text", usetex=True)

count = 15

# read files
S = []
Serr = []
for i in range(0, count):
    idx, s_raw, t_raw = np.loadtxt("path/"+str(i)+".txt", unpack=True)
    S.append(np.mean(s_raw))
    Serr.append(sem(s_raw))

K13 = np.array([i for i in range(1, 16)])
S = np.array(S)
Serr = np.array(Serr)

plt.title("Rough approach to finding the optimal $k$")
plt.errorbar(K13, S, Serr, fmt=None)
plt.plot(K13, S, "x")
plt.grid()
plt.xlabel("$k^{1/3}$")
plt.ylabel("success rate")
plt.savefig("plot.pdf")
