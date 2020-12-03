# -*- coding: utf-8 -*-
"""Zadatak7.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1MffbBVnlO4W0gcocGfVHOQz9bEaCcjiY
"""

import numpy as np
import math 
import random
import matplotlib.pyplot as plt


D = [
    173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708, 631252, 148665,
    150254, 4784408, 344759, 440109, 4198037, 329673, 28602, 144173, 1461469, 187895, 
    369313, 959307, 1482335, 2772513, 1313997, 254845,486167, 2667146, 264004, 297223, 
    94694, 1757457, 576203, 8577828, 498382, 8478177, 123575, 4062389, 3001419, 
    196884, 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834, 
    201919, 56080, 2142553, 326263,8172117, 2304253, 4761871, 205387, 6148422, 
    414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571
]
    
    
srednje_naj_r_f = 0
srednje_naj_r_x = []

plt.style.use('dark_background')
plt.ylabel("Vrednost cost funkcije")

Tk = 2**25
x_tacke = np.zeros(100000)
iteracija = []

for i in range(20):
    
    x = np.random.randint(2, size=64)
    
    min_sum = 0
    
    for m in range(64):
        min_sum += D[m] * x[m]
    
    min_sum = 2**26 - min_sum
    
    if(min_sum > 0):
        minF = min_sum
    else:
        minF = 2**26        
        
    for j in range(100000):
        
        newX = np.array(x, copy=True)
        
        for k in random.sample(range(64), int(np.round(32 - 24 * j / 100000))):
            if(newX[k] == 1):
                newX[k] = 0
            else:
                newX[k] = 1
                
        f_sum = 0
        
        for m in range(64):
            f_sum += D[m] * x[m]
            
        f_sum = 2**26 - f_sum
        
        if(f_sum > 0):
            f = f_sum
        else:
            f = 2**26

        newF_sum = 0
        
        for m in range(64):
            newF_sum += D[m] * newX[m]
        
        newF_sum = 2**26 - newF_sum
        
        if(newF_sum > 0):
            newF = newF_sum
        else:
            newF = 2**26            
        

        if(f < newF):
            p_math = (f - newF)/Tk
            p = math.exp(p_math)
            if(random.random() < p):
                x = np.array(newX, copy=True)
        else:
            x = np.array(newX, copy=True)
        
        Tk *= 0.95

        if(minF > f):
            minF = f

        if(f <= 32):
            if(srednje_naj_r_f == 0):
                srednje_naj_r_x = np.array(x, copy=True)
                srednje_naj_r_f = f
            elif(srednje_naj_r_f > minF):
                srednje_naj_r_x = np.array(x, copy=True)
                srednje_naj_r_f = f

        x_tacke[j] += minF / 20.0
        
        if(Tk != 2**25):
            Tk = 2**25
        
        iteracija.append(minF)
        
    test = str(i + 1)
    
    plt.plot(range(1,100001), iteracija, label=test)

    iteracija.clear()
    
print("Minimalno resenje optimizacione funkcije(uslov manje od 32) : ")        
print(srednje_naj_r_f)
print("Najbolje pronadjeno resenje : ")
for i in srednje_naj_r_x:
    print(i)


plt.xlabel("iter")
plt.ylabel("Vrednost cost funkcije")
plt.xscale("log")
plt.yscale("log")
plt.grid(True)
plt.legend(frameon=True, loc='lower center', ncol=10)
plt.show()

plt.style.use('dark_background')
plt.title('Srednje najbolje pronadjeno resenje')
plt.plot(range(1,100001), x_tacke, 'r', label="x_cumulative")
plt.xlabel("iter")
plt.ylabel("Average cumulative minimum of cost-function")
plt.xscale('log')
plt.yscale('log') 
plt.grid(True)
plt.legend(frameon=True, loc='lower center', ncol=1)
plt.show()