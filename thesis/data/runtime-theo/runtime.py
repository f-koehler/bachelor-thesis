import numpy as np

def runtime(n):
    r = 0
    for a in range(2, n+1):
        for a1 in range(1, a+1):
            for b in range(2, a+1):
                for b1 in range(1, b+1):
                    r += 1
    return r

def runtime_optimized(n):
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

n = np.arange(4, 256)
r1 = np.array([runtime(i) for i in n])
r2 = np.array([runtime_optimized(i) for i in n])

np.savetxt("data/runtime-theo/data.txt", np.c_[n, r1, r2])
