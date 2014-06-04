import numpy as np
from matplotlib import pyplot as plt

n, r1, r2 = np.loadtxt("data/runtime-theo/data.txt", unpack=True)

plt.plot(n, r1/n**3, label="$R_1\\left(n\\right)$")
plt.plot(n, r2/n**3, label="$R_2\\left(n\\right)$")
plt.grid()
plt.xlabel("$n$")
plt.ylabel("$\\frac{R\\left(n\\right)}{n^3 N_a N_c}$")
plt.legend(loc=4)
plt.savefig("plot/runtime-theo/runtime.pdf")
