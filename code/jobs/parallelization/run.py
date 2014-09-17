import os
import subprocess
import numpy as np

prog = "../../bin/onestep"
N = 783061
Na = 500
Nc = 200
Fc = 0.997
t = [1, 2, 3, 4, 5, 6, 7, 8]
r = 200

for _t in t:
    subprocess.call([prog, "-N", str(N), "-k", "auto", "-Na", str(Na), "-Nc", str(Nc), "-Fc", str(Fc), "-t", str(_t), "-r", str(r), "-o", str(_t)+".txt"])
