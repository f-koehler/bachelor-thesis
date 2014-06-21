import numpy as np
from matplotlib import pyplot as plt

n, success, successErr, time, timeErr, steps, stepsErr, timeClean, timeErrClean, stepsClean, stepsErrClean = np.loadtxt("data/factorization/results.txt", unpack=True)
time = time*1e-6
timeErr = timeErr*1e-6
timeClean = timeClean*1e-6
timeErrClean = timeErrClean*1e-6

plt.errorbar(n, success, successErr)
plt.xlabel("$n$")
plt.ylabel("Erfolgsrate")
plt.xlim([n.min()-1, n.max()+1])
plt.ylim([success.min()-0.1, success.max()+0.1])
plt.xticks(n[::2])
plt.grid()
plt.savefig("plot/factorization/success.pdf")
plt.close()

plt.errorbar(n**4, time, timeErr)
plt.xlabel("$n^4$")
plt.ylabel("$T/\\si{\\second}$")
plt.xticks((n**4), ["$"+str(int(_n))+"^4$" for _n in n])
plt.grid()
plt.savefig("plot/factorization/time.pdf")
plt.close()

plt.errorbar(n**4, steps, stepsErr)
plt.xlabel("$n^4$")
plt.ylabel("Schritte")
plt.xticks((n**4)[10::2], ["$"+str(int(_n))+"^4$" for _n in n[10::2]])
plt.grid()
plt.savefig("plot/factorization/steps.pdf")
