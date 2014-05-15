import os
import subprocess
import numpy as np

prog = "../../bin/factorize"
N = np.loadtxt("numbers.txt", dtype=np.int32)
Na = 1000
Nc = 1000
Fc = 0.997
t = 8
r = 1000
path = "./data/"

if not os.path.exists(path):
    os.mkdir(path)

i = 0
for n in N:
    subprocess.call([prog, "-N", str(n), "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(t), "-r", str(r), "-o", path+str(i)+".txt"])
    i = i+1
