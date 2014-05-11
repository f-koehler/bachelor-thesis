import os
import subprocess
from math import log

# program
prog = "../../../code/primefac-build/semiprime"

# parameters
N1 = 66889
N2 = 104723
k = [(7.0+i*0.25)**3 for i in range(0, 9)]
Na = 1000
Nc = 100000
Fc = 0.997
t  = 8
r  = 1000
path = "./data/"

# create a directory or clear it
if not os.path.exists(path):
    os.mkdir(path)
else:
    for f in os.listdir(path):
        os.remove(path + f)

# run
for i in range(0, len(k)):
    subprocess.call([prog, "-N1", str(N1), "-N2", str(N2), "-k", str(k[i]), "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(t), "-r", str(r), "-o", path+str(i)+".txt"])
