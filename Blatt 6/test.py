#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import scipy.stats

(X, Y) = np.loadtxt('output.dat', unpack=True)

matplotlib.rc('text', usetex = True)
params = {'text.latex.preamble' : ['\\usepackage{amsmath}', '\\usepackage{siunitx}', '\\sisetup{per-mode=fraction}', '\\sisetup{separate-uncertainty=true}']}
plt.rcParams.update(params)

plt.plot(X, Y)

plt.xlabel('$x$')
plt.ylabel('$f(x)$')

if len(sys.argv) == 1:
	plt.show()
else:
	plt.savefig(sys.argv[1])
