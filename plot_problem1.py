#!/usr/bin/env python3

import matplotlib
matplotlib.rcParams['font.family'] = 'serif'
import matplotlib.pyplot as plt
import numpy as np

dt = 0.01

for n in range(101):
    print(n)
    t = n * dt
    data = np.loadtxt(f"data{n}.csv", delimiter=",")
    x = data[:, 0]
    u = data[:, 1]
    plt.plot(x, u)
    ax = plt.gca()
    ax.set_xlabel("x")
    ax.set_ylabel("u")
    ax.set_title(f"t = {t:.2f}")
    plt.savefig(f"u_{n:03d}.png", bbox_inches="tight")
    plt.close()
