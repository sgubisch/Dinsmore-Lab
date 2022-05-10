# -*- coding: utf-8 -*-
"""
Created on Mon Oct 18 11:14:12 2021

@author: sumne
"""

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import pandas as pd
import os
from scipy.optimize import curve_fit

name="12.1.21_PlateE_Trial6.txt"
path='C:/Users/Sumne/Desktop/Dinsmore'
joined_path = os.path.join(path,name)
print(joined_path)

x = np.genfromtxt(joined_path,delimiter=',', skip_header=0, usecols=0)#*(.0025)
y = np.genfromtxt(joined_path,delimiter=',', skip_header=0, usecols=1)#*(.00165)
V = np.genfromtxt(joined_path,delimiter=',', skip_header=0, usecols=2)
#V2 = np.genfromtxt(joined_path,delimiter=',', skip_header=0, usecols=3)
# t = np.genfromtxt(joined_path,delimiter=',', skip_header=0, usecols=4)



data = pd.DataFrame({'X': x, 'Y': y, 'V': V}) #'V2':V2})#'t':t})

# bavg = data[data["Y"] < 850]["V"].mean()
# data["V_centered"] = -(data["V"] - bavg)



# data_pivoted = data.pivot("Y","X", "V_centered")
# ax = sns.heatmap(data_pivoted,cbar_kws={'label': 'volts'},cmap="viridis")
# ax.set_xlabel("cm")
# ax.set_ylabel("cm")
# ax.set_title(name)
# print(bavg)

# bavg2 = data[data["Y"] < 850]["V2"].mean()
# data["V2_centered"] = -(data["V2"] - bavg2)

# plt.figure(2)
# data_pivoted = data.pivot("Y","X", "V2_centered")
# ax2 = sns.heatmap(data_pivoted,cbar_kws={'label': 'volts'},cmap="viridis")
# ax2.set_xlabel("in")
# ax2.set_ylabel("in")
# ax2.set_title('Diff Op'+name)
# plt.show()
# print(bavg2)

# plt.figure(3)
# plt.plot(x,data["V_centered"])
# plt.xlabel("cm")
# plt.ylabel("Voltage (V)")
# plt.title(name)

# plt.figure(4)
# plt.plot(x,data["V2_centered"])
# plt.xlabel("in")
# plt.ylabel("Voltage (V)")
# plt.title('Diff Op'+name)



# t2=data[data["Y"]==1350][["t"]]
# V2=-(data[data["Y"]==1350][["V"]])

# plt.scatter(t2,V2,c='red',marker='.')
# plt.title('Decay of Voltage With time at X-step=1350')
# plt.xlabel('Time (ms)')
# plt.ylabel('Voltage (V)')
# plt.grid()

realx = data[data["Y"] == 800]["X"]
voltage = data[data["Y"] == 800]["V"]

realxd = realx*.0025

def tanh(x,a,b,c,d):
    return (a+(-b*np.tanh((x-c)/d)))

popt, pcov = curve_fit(tanh, x, V)
print('a:', popt[0],'b:',popt[1],'c:',popt[2], 'd:',popt[3])
best_fit = tanh(realx,popt[0],popt[1],popt[2],popt[3])


plt.figure(3)
plt.scatter(x*(.0025),V, color="blue",marker='.', label="Data")
plt.plot(realxd, best_fit, color='red', label ="Best fit")
plt.xlabel("in")
plt.ylabel("Voltage (V)")
plt.xlim([1.5,4.5])
plt.legend()
plt.grid()
plt.title(name)
