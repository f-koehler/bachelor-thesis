import numpy as np
from random import *

count = 20
nmin = 8
nmax = 32
nvals = [i for i in range(nmin, nmax+1)]

numbers = []
for n in nvals:
    for i in range(0, count):
        numbers.append(randint(2**(n-1), (2**n)-1))

f = open("numbers.txt", "w")
for n in numbers:
    f.write(str(n)+"\n")
f.close()
