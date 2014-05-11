import numpy as np

count = 9

for i in range(0, count):
    id1, s1, t1 = np.loadtxt("./run1/" + str(i) + ".txt", unpack=True, dtype=int)
    id2, s2, t2 = np.loadtxt("./run2/" + str(i) + ".txt", unpack=True)

    for j in range(0, id2.shape[0]):
        id2[j] = id2[j]+1000

    _id = np.concatenate((id1, id2))
    _s = np.concatenate((s1, s2))
    _t = np.concatenate((t1, t2))

    np.savetxt("data/"+str(i)+".txt", np.c_[_id, _s, _t], fmt="%i")
