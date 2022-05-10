# -*- coding: utf-8 -*-
"""
Created on Tue Oct 19 14:09:54 2021

@author: sumne
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def linear(x,m,b):
    return (m*x)+b

def quadratic(x,a,b,c):
    return (a*(x**2) + b*x +c)

x = np.array([37,38,35,32,12,20,24,30, 25,22,23,18,11,])
y = np.array([33.38,33.64,32.61,27.80,6.46,17.32,22.88,31.32,24.83,18.07,21.76,14.17,15.5])

plt.figure(1)
popt, pcov1 = curve_fit(linear, x, y)
print('slope 1:', popt[0])
best_fit1 = linear(x,popt[0],popt[1])
chi_square1 = ((x - best_fit1)**2).sum()
print('Chi-squared:',chi_square1)
print('linear fit',best_fit1) 
plt.scatter(x,y, marker='d', color='red')
plt.plot(x,best_fit1,label= 'slope:' + str(round(popt[0],2))+ '+' + str(round(popt[1],2)))
plt.title('Linear Optimization of Ardunio vs Voltage Probe Reading')
plt.xlabel('Front Face Voltage')
plt.ylabel('Ardunio Voltage')
plt.legend()

plt.figure(2)
popt2, pcov2 = curve_fit(quadratic, x, y)
print('a:', popt2[0],'b:',popt2[1],'c:',popt2[2])
best_fit2 = quadratic(x,popt2[0],popt2[1],popt2[2])
chi_square2 = ((x - best_fit2)**2).sum()
print('Quadratic fit',best_fit2) 
print('Chi-squared:',chi_square2)
plt.scatter(x,y, marker='d', color='red')
plt.plot(x,best_fit2,label= 'a:'+ str(round(popt2[0],2)) + 'b:'+ str(round(popt2[1],2)) +'c:'+ str(round(popt2[2],2)))
plt.title('Quadratic Optimization of Ardunio vs Voltage Probe Reading')
plt.xlabel('Front Face Voltage')
plt.ylabel('Ardunio Voltage')
plt.legend()
