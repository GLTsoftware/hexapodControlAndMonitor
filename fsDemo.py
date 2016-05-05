#!/home/nimesh/anaconda/bin/python
"""
Acquires frequency-switched spectra.
For demos; no file saving

Usage:
fsDemo.py <N> <fc> <delta-f> 

N: No. of spectra to average
fc: center frequency MHz
delta-f: sw. btwn fc and fc+deltaf MHz
"""

from numpy import savetxt
from rtlsdr import *
#from pylab import *
import matplotlib.pyplot as plt
import numpy as np
import sys
import time
from matplotlib.mlab import psd

N = int(sys.argv[1])
frequency = float(sys.argv[2])
deltaf = float(sys.argv[3])
#fname = sys.argv[4]

gain = 40.
calFactor = 92000.

frequency2=frequency+deltaf

total=np.zeros(1024)

sdr = RtlSdr() 
sdr.sample_rate = 2.4e6
sdr.gain = gain

plt.ion()

plt.figure(1)

loop="y"

while (loop=="y"):
    for i in range(N):
        sdr.center_freq = float(frequency)*1.0e6
        samples = sdr.read_samples(256*1024)
        (power1,f1) = psd(samples, NFFT = 1024, Fs= sdr.sample_rate/1.0e6,scale_by_freq=True) 
        sdr.center_freq = float(frequency2)*1.0e6
        samples = sdr.read_samples(256*1024)
        (power2,f2) = psd(samples, NFFT = 1024, Fs= sdr.sample_rate/1.0e6,scale_by_freq=True)
        diff=power1-power2
        total=total+diff
    
    average=calFactor*(total/float(N))
    
    plt.plot(f1+frequency,average)
    plt.xlabel('Frequency (MHz)')
    plt.ylabel('Antenna temperature (K)')
    plt.show()
    
    loop = input("Enter y to continue, n to quit.")
    if (loop == "y"):
        plt.clf()
    
#---------------------------------------------------------------
#close("all")

#flabel = f1+frequency
#output = column_stack((f1+float(frequency),average))
#output = column_stack((flabel,average))
#savetxt(fname,output,fmt=('%.5f','%.7e'))
