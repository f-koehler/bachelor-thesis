import numpy as np
from matplotlib import pyplot as plt


n, r1, r2 = np.loadtxt("data/runtime-sieve/data.txt", unpack=True)

plt.plot(n, r1, label="Simulated Annealing")
plt.plot(n, r2, label="Zahlkörpersieb")
plt.title("$c=64/9$, $N_a=1000$ und $N_c=2\cdot 10^6$")
plt.yscale("log")
plt.grid()
plt.xlabel("$n$")
plt.ylabel("$R\\left(n\\right)$")
plt.legend(loc=2)
plt.savefig("plot/runtime-sieve/plot.pdf")
