import numpy as np
import os

# create a directory
if not os.path.exists("data"):
    os.mkdir("data")

for f in os.listdir("data1"):
    idx, s, t, n = np.loadtxt("data1/"+f, unpack=True, dtype=np.int64)

    _idx, _s, _t, _n = np.loadtxt("data2/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    _idx, _s, _t, _n = np.loadtxt("data3/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    _idx, _s, _t, _n = np.loadtxt("data4/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    np.savetxt("data/"+f, np.c_[idx, s, t, n], fmt="%i")
