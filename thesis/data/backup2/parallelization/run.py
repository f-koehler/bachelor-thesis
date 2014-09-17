import os
import subprocess
import numpy as np

prog = "../../bin/onestep"
N = np.loadtxt("numbers.txt", dtype=np.int32, unpack=True)
Na = 500
Nc = 500
Fc = 0.997
t = [1, 2, 4, 8]
r = 20

for _t in t:
    if not os.path.exists("./data"+str(_t)+"/"):
        os.mkdir("./data"+str(_t)+"/")

for _t in t:
    for i in range(0, N.shape[0]):
        subprocess.call([prog, "-N", str(N[i]), "-k", "auto", "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(_t), "-r", str(r), "-o", "./data"+str(_t)+"/"+str(i)+".txt"])
