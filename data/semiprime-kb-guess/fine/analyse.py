import numpy as np
from scipy.stats import sem
import matplotlib
from matplotlib import pyplot as plt

count = 9

# read files
S = []
Serr = []
for i in range(0, count):
    idx, s_raw, t_raw = np.loadtxt("run1/"+str(i)+".txt", unpack=True)
    S.append(np.mean(s_raw))
    Serr.append(sem(s_raw))

K13 = np.array([7+i*0.25 for i in range(0, 9)])
S = np.array(S)
Serr = np.array(Serr)

plt.title("Finer approach to finding the optimal $k$")
plt.errorbar(K13, S, Serr, fmt=None, label="Errors")
plt.plot(K13, S, "x")
plt.grid()
plt.xlabel("$k^{1/3}$")
plt.ylabel("success rate")
plt.legend()
plt.savefig("plot.pdf")
