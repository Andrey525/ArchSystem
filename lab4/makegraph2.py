#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

def main():
    datafiles = ["results/def.dat", "results/transpose.dat", "results/block.dat"]
    labels = ["dgemm_def", "dgemm_transpose", "dgemm_block"]
    cm = 1/2.54  # centimeters in inche
    fig = plt.figure(figsize=(16*cm, 10*cm))
    ax = fig.add_subplot(111)
    colors=["black", "blue", "red"]
    ax.set(xlabel="n", ylabel="time", title="DGEMM")
    # ax.set_yscale('log')
    # Draw data files
    for i in range(len(datafiles)):
        data = np.loadtxt(datafiles[i])
        x = data[:, 0]
        y = data[:, 1]
        ax.plot(x,y,'o-',markersize=2,c=colors[i],label=labels[i])
        ax.legend();

    fig.savefig('dgemm_time.png', dpi=300)

if __name__ == "__main__":
    main()