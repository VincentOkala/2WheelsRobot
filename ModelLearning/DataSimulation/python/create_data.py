import math as m
import sys
import numpy as np
from datetime import datetime
from random import seed
from random import gauss


wc = np.array([0.5515, 1.06])
t = np.array([0.0])

c = np.array([[m.sin(wc[0] * t[0]), m.sin(wc[1] * t[0])]])

g = np.array([[0.001, 0.002, 0.003]]) * wc[0]
a = np.array([[0.002, 0.005, 0.009]]) * wc[1]

MAX_SAMPLES = int(sys.argv[1])
FILE_NAME = "simdata.txt"
t = np.append(t, [t[0] + 0.01])
for i in range(1, MAX_SAMPLES):
    t = np.append(t, t[i] + 0.01)
    c = np.append(c, [[m.sin(wc[0] * t[i]) + gauss(0,0.01), m.sin(wc[1] * t[i]) + gauss(0,0.01)]], axis=0)
    g = np.append(g, [[(m.sin(g[i-1][0]) + c[i-1][0] - g[i-1][1] * c[i-1][1]*2 + g[i-1][2] + 0.1)/(np.sum(g[i-1]*g[i-1] + 0.5)),
                       (m.sin(g[i-1][1]) + m.sin(c[i-1][0]) - g[i-1][2] * c[i-1][1]*4 + g[i-1][0] + 0.2)/(np.sum(g[i-1]*g[i-1] + 0.5)),
                       (m.sin(g[i-1][2]) + c[i-1][0] - m.sin(g[i-1][0] * c[i-1][1])*6 + g[i-1][1] + 0.3)/(np.sum(g[i-1]*g[i-1] + 0.5))]], axis=0)
    a = np.append(a, [[(m.sin(a[i-1][0]) + c[i-1][1]*1 - a[i-1][1] * m.sin(c[i-1][0]) +  a[i-1][2] +0.2)/np.sum(a[i-1]*a[i-1] + 0.5),
                       (m.sin(a[i-1][1]) + c[i-1][1]*3 - a[i-1][2] * c[i-1][0] +  m.sin(a[i-1][0] +0.1))/np.sum(a[i-1]*a[i-1] + 0.5),
                       (m.sin(a[i-1][2]) + c[i-1][1]*5 - m.sin(a[i-1][0] * c[i-1][0]) +  a[i-1][1] +0.2)/np.sum(a[i-1]*a[i-1] + 0.5)]], axis=0)


f = open(FILE_NAME, "w+")
for i in range(MAX_SAMPLES):
    f.write("%f, %f, %f, %f, %f, %f, %f, %f\n"
            % (g[i][0], g[i][1], g[i][2], a[i][0], a[i][1], a[i][2], c[i][0], c[i][1]))

f.close()