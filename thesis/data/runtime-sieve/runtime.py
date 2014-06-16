import numpy as np

def runtime(n):
    r = 0
    amin = int(n/2)
    if amin == 1:
        amin = 2

    for a in range(amin, n+1):
        for a1 in range(1, a+1):
            bmin = n-a
            if bmin == 1:
                bmin = 2
            for b in range(bmin, a+1):
                for b1 in range(1, b+1):
                    r += 1
    return r

c = 64/9
Na = 1000
Nc = 2000000

n = np.arange(2, 65)
N = np.array([2**(_n)-1 for _n in n])
r1 = np.array([runtime(i) for i in n])*Na*Nc
r2 = np.exp(c*(np.log(N)**(2/3))*(np.log(np.log(N))**(1/3)))

np.savetxt("data/runtime-sieve/data.txt", np.c_[n, r1, r2])
