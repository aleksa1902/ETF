# -*- coding: utf-8 -*-
"""
Created on Wed Jan 13 18:14:41 2021

@author: aleks
ba170578
"""

import numpy as np
import math
import matplotlib.pyplot as plt

tacke_bez_uslova = []
tacke_sa_uslovom = []

funkcija1_bez_uslova = []
funkcija2_bez_uslova = []
funkcija1_sa_uslovom = []
funkcija2_sa_uslovom = []

for iteration in range(10000):
    x = np.random.uniform(-1, 1)
    y = np.random.uniform(-1, 1)
    
    tacke_bez_uslova.append([x, y])
    
    # uslov
    while((x * y + (1/4)) < 0):
        x = np.random.uniform(-1, 1)
        y = np.random.uniform(-1, 1)
        
    tacke_sa_uslovom.append([x, y])
    
    # prvi deo zadatka za bez uslova
    x_pow = math.pow(tacke_bez_uslova[iteration][0], 2)
    y_pow = math.pow(tacke_bez_uslova[iteration][1], 2)
    
    f1 = 2 * x_pow + y_pow
    
    funkcija1_bez_uslova.append(f1)
    
    x_y_pow = math.pow(tacke_bez_uslova[iteration][0] - tacke_bez_uslova[iteration][1], 2)
    
    f2 = -1 * x_y_pow
    
    funkcija2_bez_uslova.append(f2) 
    
    # drugi deo zadatka za sa uslovom
    x_pow = math.pow(tacke_sa_uslovom[iteration][0], 2)
    y_pow = math.pow(tacke_sa_uslovom[iteration][1], 2)
    
    f1 = 2 * x_pow + y_pow
    
    funkcija1_sa_uslovom.append(f1)
    
    x_y_pow = math.pow(tacke_sa_uslovom[iteration][0] - tacke_sa_uslovom[iteration][1], 2)
    
    f2 = -1 * x_y_pow
    
    funkcija2_sa_uslovom.append(f2) 
    
    
nasaoBolji_bez_uslova = 0
nasaoBolji_sa_uslovom = 0

pareto_za_x_bez_uslova = []
pareto_za_y_bez_uslova = []

pareto_za_x_sa_uslovom = []
pareto_za_y_sa_uslovom = []

for i in range(10000):
    for j in range(10000):
        
        if(i != j):
            # bez uslova
            if(nasaoBolji_bez_uslova == 0):
                if(funkcija1_bez_uslova[i] >= funkcija1_bez_uslova[j] and funkcija2_bez_uslova[i] >= funkcija2_bez_uslova[j]):
                    if(funkcija1_bez_uslova[i] > funkcija1_bez_uslova[j] or funkcija2_bez_uslova[i] > funkcija2_bez_uslova[j]):
                        nasaoBolji_bez_uslova = 1
            
            # sa uslovom
            if(nasaoBolji_sa_uslovom == 0):
                if(funkcija1_sa_uslovom[i] >= funkcija1_sa_uslovom[j] and funkcija2_sa_uslovom[i] >= funkcija2_sa_uslovom[j]):
                    if(funkcija1_sa_uslovom[i] > funkcija1_sa_uslovom[j] or funkcija2_sa_uslovom[i] > funkcija2_sa_uslovom[j]):
                        nasaoBolji_sa_uslovom = 1
                    
    # pareto bez uslova
    if(nasaoBolji_bez_uslova == 0):
        pareto_za_x_bez_uslova.append(funkcija1_bez_uslova[i])
        pareto_za_y_bez_uslova.append(funkcija2_bez_uslova[i])
        
    nasaoBolji_bez_uslova = 0
    
    # pareto sa uslovom
    if(nasaoBolji_sa_uslovom == 0):
        pareto_za_x_sa_uslovom.append(funkcija1_sa_uslovom[i])
        pareto_za_y_sa_uslovom.append(funkcija2_sa_uslovom[i])
        
    nasaoBolji_sa_uslovom = 0
        
plt.style.use('dark_background')
plt.title("Pareto front")
plt.grid(True)
plt.xlabel("f1")
plt.ylabel("f2")
plt.legend(frameon=True, loc='lower center')
f1_f2 = plt.scatter(funkcija1_bez_uslova, funkcija2_bez_uslova, color = 'aqua', marker='.')
pareto_x1_x2 = plt.scatter(pareto_za_x_bez_uslova, pareto_za_y_bez_uslova, color = 'red', marker='x')

plt.legend((f1_f2, pareto_x1_x2),('resenja', 'pareto front'),scatterpoints=1,loc='lower left',fontsize=8)

plt.show()
    
plt.style.use('dark_background')
plt.title("Pareto front sa dodatnim uslovom")
plt.grid(True)
plt.xlabel("f1")
plt.ylabel("f2")
plt.legend(frameon=True, loc='lower center')
plt.scatter(funkcija1_sa_uslovom, funkcija2_sa_uslovom, color = 'aqua', marker='.' )
plt.scatter(pareto_za_x_sa_uslovom, pareto_za_y_sa_uslovom, color = 'red', marker='x')
plt.legend((f1_f2, pareto_x1_x2),('resenja', 'pareto front'),scatterpoints=1,loc='lower left',fontsize=8)

plt.show()