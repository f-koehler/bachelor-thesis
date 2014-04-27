import numpy as np
from matplotlib import pyplot as plt
import theory

N=128
BAL=8192

################################################
# inner energy as function of T at different J #
################################################

# heating ######################################
plt.title("Heating, $h=0$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# j=1
T, h, U, M = np.loadtxt("few/heating_J1.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$J=1$ (MC)")
plt.plot(Tval, theory.energy(Tval, 1.0), label="$J=1$ (theory)")

# j=2
T, h, U, M = np.loadtxt("few/heating_J2.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$J=2$ (MC)")
plt.plot(Tval, theory.energy(Tval, 2.0), label="$J=2$ (theory)")

# finalize
plt.xlabel("$T$")
plt.ylabel("$U/N$")
plt.legend(loc=4)
plt.grid()
plt.savefig("few_heating_J.pdf")
plt.close()

# cooling ######################################
plt.title("Cooling, $h=0$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# j=1
T, h, U, M = np.loadtxt("few/cooling_J1.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$J=1$ (MC)")
plt.plot(Tval, theory.energy(Tval, 1.0), label="$J=1$ (theory)")

# j=2
T, h, U, M = np.loadtxt("few/cooling_J2.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$J=2$ (MC)")
plt.plot(Tval, theory.energy(Tval, 2.0), label="$J=2$ (theory)")

# finalize
plt.xlabel("$T$")
plt.ylabel("$U/N$")
plt.legend(loc=4)
plt.grid()
plt.savefig("few_cooling_J.pdf")
plt.close()


################################################
# inner energy as function of T at different h #
################################################

# heating ######################################
plt.title("Heating, $J=0$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# j=1
T, h, U, M = np.loadtxt("few/heating_h1.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$h=1$ (MC)")
plt.plot(Tval, theory.energy(Tval, 1.0), label="$h=1$ (theory)")

# j=2
T, h, U, M = np.loadtxt("few/heating_h2.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$h=2$ (MC)")
plt.plot(Tval, theory.energy(Tval, 2.0), label="$h=2$ (theory)")

# finalize
plt.xlabel("$T$")
plt.ylabel("$U/N$")
plt.legend(loc=4)
plt.grid()
plt.savefig("few_heating_h.pdf")
plt.close()

# cooling ######################################
plt.title("Cooling, $J=0$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# j=1
T, h, U, M = np.loadtxt("few/cooling_h1.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$h=1$ (MC)")
plt.plot(Tval, theory.energy(Tval, 1.0), label="$h=1$ (theory)")

# j=2
T, h, U, M = np.loadtxt("few/cooling_h2.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="$h=2$ (MC)")
plt.plot(Tval, theory.energy(Tval, 2.0), label="$h=2$ (theory)")

# finalize
plt.xlabel("$T$")
plt.ylabel("$U/N$")
plt.legend(loc=4)
plt.grid()
plt.savefig("few_cooling_h.pdf")
plt.close()


##############################################
# inner energy as function of T with J and h #
##############################################
plt.title("Cooling, $J=1$, $h=1$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")
T, h, U, M = np.loadtxt("few/cooling.txt", unpack=True)
U = U/N
Tval = np.linspace(T.min(), T.max(), 10000)
plt.plot(T, U, label="MC")
plt.plot(Tval, theory.energy(Tval, 1.0, 1.0), label="theory")
plt.xlabel("$T$")
plt.ylabel("$U/N$")
plt.legend(loc=4)
plt.grid()
plt.savefig("few_cooling.pdf")
plt.close()


################################################
# magnetization as funtion of h at different T #
################################################
plt.title("Magnetization, $J=0$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# T=0
T, h, U, M = np.loadtxt("few/mag_T0.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="T=0 (MC)")

# T=1
T, h, U, M = np.loadtxt("few/mag_T1.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="T=1 (MC)")
plt.plot(hval, theory.magnetization(hval, 1.0), label="T=1 (theory)")

# T=2
T, h, U, M = np.loadtxt("few/mag_T2.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="T=2 (MC)")
plt.plot(hval, theory.magnetization(hval, 2.0), label="T=2 (theory)")

# finalize
plt.xlabel("$h$")
plt.ylabel("$M$")
plt.ylim([-1.1, 1.1])
plt.legend(loc=4)
plt.grid()
plt.savefig("few_mag_T.pdf")
plt.close()

################################################
# magnetization as funtion of h at different J #
################################################
plt.title("Magnetization, $T=1$, $N=" + str(N) + "$, $" + str(BAL) + "$ balance steps")

# J=0
T, h, U, M = np.loadtxt("few/mag_J0.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="J=0 (MC)")
plt.plot(hval, theory.magnetization(hval, T=1.0), label="J=0 (theory)")

# J=1
T, h, U, M = np.loadtxt("few/mag_J1.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="J=1 (MC)")
plt.plot(hval, theory.magnetization(hval, T=1.0, J=1.0), label="J=1 (theory)")

# J=2
T, h, U, M = np.loadtxt("few/mag_J2.txt", unpack=True)
M = M/N
hval = np.linspace(h.min(), h.max(), 10000)
plt.plot(h, M, label="J=2 (MC)")
plt.plot(hval, theory.magnetization(hval, T=1.0, J=2.0), label="J=2 (theory)")

# finalize
plt.xlabel("$h$")
plt.ylabel("$M$")
plt.ylim([-1.1, 1.1])
plt.legend(loc=4)
plt.grid()
plt.savefig("few_mag_J.pdf")
plt.close()
