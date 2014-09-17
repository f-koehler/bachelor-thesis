import os
import subprocess
import numpy as np

prog = "../../bin/onestep"
N = np.loadtxt("numbers.txt", dtype=np.int32, unpack=True)
Na = 500
Nc = 1000
Fc = 0.997
t = 8
r = 20
path = "./data/"

if not os.path.exists(path):
    os.mkdir(path)

for i in range(0, N.shape[0]):
    subprocess.call([prog, "-N", str(N[i]), "-k", "auto", "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(t), "-r", str(r), "-o", path+str(i)+".txt"])
