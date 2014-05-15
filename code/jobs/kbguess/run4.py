import numpy as np
import os
import subprocess
from math import log

# program
prog = "../../bin/semiprime"

# parameters
N1 = 66889
N2 = 104723
#k = [i**3 for i in range(1, 16)]
k = np.linspace(1, 16, 16)
k = k**3
Na = 1000
Nc = 80000
Fc = 0.997
t  = 8
r  = 1500
path = "./data4/"

# create a directory or clear it
if not os.path.exists(path):
    os.mkdir(path)

# run
for i in range(0, k.shape[0]):
    subprocess.call([prog, "-N1", str(N1), "-N2", str(N2), "-k", str(k[i]), "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(t), "-r", str(r), "-o", path+str(i)+".txt"])
