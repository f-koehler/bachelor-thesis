import numpy as np
from matplotlib import pyplot as plt

n, r1, r2 = np.loadtxt("data/runtime-theo/data.txt", unpack=True)

plt.plot(n, 1-r2/r1)
plt.grid()
plt.xlabel("$n$")
plt.ylabel("$1-\\frac{R_2\\left(n\\right)}{R_1\\left(n\\right)}$")
plt.savefig("plot/runtime-theo/comparison.pdf")
