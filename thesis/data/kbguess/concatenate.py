import numpy as np
import os

# create a directory
if not os.path.exists("data/kbguess/data"):
    os.mkdir("data/kbguess/data")

for f in os.listdir("data/kbguess/data1"):
    idx, s, t, n = np.loadtxt("data/kbguess/data1/"+f, unpack=True, dtype=np.int64)

    _idx, _s, _t, _n = np.loadtxt("data/kbguess/data2/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    _idx, _s, _t, _n = np.loadtxt("data/kbguess/data3/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    _idx, _s, _t, _n = np.loadtxt("data/kbguess/data4/"+f, unpack=True, dtype=np.int64)
    idx = np.append(idx, _idx)
    s = np.append(s, _s)
    t = np.append(t, _t)
    n = np.append(n, _n)

    np.savetxt("data/kbguess/data/"+f, np.c_[idx, s, t, n], fmt="%i")
