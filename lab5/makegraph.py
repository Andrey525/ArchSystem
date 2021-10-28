#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

def main():
    datafiles = ["results/PT.dat", "results/OMP.dat", "results/MPI.dat"]
    labels = ["pthreads", "OpenMP", "MPI"]
    cm = 1/2.54  # centimeters in inche
    fig = plt.figure(figsize=(16*cm, 10*cm))
    ax = fig.add_subplot(111)
    colors=["blue", "red", "orange"]
    ax.set(xlabel="number threads(proc)", ylabel="speedup", title="Speedup of parallel matrix multiplicaton")
    
    for axis in [ax.xaxis]:
        axis.set_major_locator(ticker.MaxNLocator(integer=True))

    # ax.set_yscale('log')
    # Draw data files
    for i in range(len(datafiles)):
        data = np.loadtxt(datafiles[i])
        x = data[:, 1]
        y = data[:, 4]
        ax.plot(x,y,'o-',markersize=2,c=colors[i],label=labels[i])
        ax.legend();

    data = np.loadtxt(datafiles[1])
    x = data[:, 1]
    y = data[:, 1]
    ax.plot(x,y,'o-',markersize=2,c="black",label="linear speedup")
    ax.legend();

    fig.savefig('results/speedup.png', dpi=300)

if __name__ == "__main__":
    main()