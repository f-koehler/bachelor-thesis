import numpy as np
from matplotlib import pyplot as plt

n, success, successErr, time, timeErr, steps, stepsErr = np.loadtxt("data/runtime/results.txt", unpack=True)
time = time*10e-7
timeErr = timeErr*10e-7

plt.errorbar(n, success, successErr, fmt="x")
plt.xlabel("$n$")
plt.ylabel("Erfolgsrate")
plt.xlim([n.min()-1, n.max()+1])
plt.ylim([success.min()-0.1, success.max()+0.1])
plt.xticks(n)
plt.grid()
plt.savefig("plot/runtime/success.pdf")
plt.close()

plt.errorbar(n**4, time, timeErr, fmt="x")
plt.xlabel("$n^4$")
plt.ylabel("$T/\\si{\\second}$")
plt.xticks((n**4)[5:], ["$"+str(int(_n))+"^4$" for _n in n[5:]])
plt.grid()
plt.savefig("plot/runtime/time.pdf")
plt.close()

plt.errorbar(n**4, steps, stepsErr)
plt.xlabel("$n^4$")
plt.ylabel("Schritte")
plt.xticks((n**4)[5:], ["$"+str(int(_n))+"^4$" for _n in n[5:]])
plt.grid()
plt.savefig("plot/runtime/steps.pdf")
