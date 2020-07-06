import sys
import numpy as np
import matplotlib.pyplot as plt


fID = open("simdata.txt", "r")

g = np.array([[0, 0, 0]])
a = np.array([[0, 0, 0]])
c = np.array([[0, 0]])
for line in fID:
    numbers = line.split(", ")
    g = np.append(g, [[float(numbers[0]), float(numbers[1]), float(numbers[2])]], axis=0)
    a = np.append(a, [[float(numbers[3]), float(numbers[4]), float(numbers[5])]], axis=0)
    c = np.append(c, [[float(numbers[6]), float(numbers[7])]], axis=0)
fID.close()

STOP_IDX = 1000
plt.figure(1)
plt.subplot(421)
plt.plot(c[1:STOP_IDX, 0])
plt.subplot(422)
plt.plot(c[1:STOP_IDX, 1])
plt.subplot(423)
plt.plot(g[1:STOP_IDX, 0])
plt.subplot(425)
plt.plot(g[1:STOP_IDX, 1])
plt.subplot(427)
plt.plot(g[1:STOP_IDX, 2])
plt.subplot(424)
plt.plot(a[1:STOP_IDX, 0])
plt.subplot(426)
plt.plot(a[1:STOP_IDX, 1])
plt.subplot(428)
plt.plot(a[1:STOP_IDX, 2])
plt.show()