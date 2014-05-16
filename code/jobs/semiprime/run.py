import os
import subprocess
import numpy as np

prog = "../../bin/semiprime"
N1, N2, Na, k, Nc = np.loadtxt("numbers.txt", dtype=np.int32, unpack=True)
Fc = 0.997
t = 8
r = 180
path = "./data/"

if not os.path.exists(path):
    os.mkdir(path)

for i in range(0, N1.shape[0]):
    subprocess.call([prog, "-N1", str(N1[i]), "-N2", str(N2[i]), "-k", str(k[i]), "-Na", str(Na[i]), "-Nc", str(Nc[i]), "-Fc", str(Fc), "-t", str(t), "-r", str(r), "-o", path+str(i)+".txt"])
