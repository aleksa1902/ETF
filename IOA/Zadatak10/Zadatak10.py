# -*- coding: utf-8 -*-
"""
Created on Sat Dec 26 00:22:05 2020

@author: aleks
"""

import numpy as np
import math
import random

D = 6

# def pocetnih tacaka
tacka_A = np.array([1, 5, 1])
tacka_B = np.array([3, 2, 0])
tacka_C = np.array([5, 7, 1])
tacka_D = np.array([6, 3, 3])

P_best = []
P_best_suma = []
G_best = []
G_best_suma = -1
vektor_brzine = []
jato = []
 
#for i in range(50):
for i in range(10 * D):
    #tacka s1
    s1_x = np.random.randint(0, 10)
    s1_y = np.random.randint(0, 10)
    s1_z = np.random.randint(0, 4)
    
    #tacka s2
    s2_x = np.random.randint(0, 10)
    s2_y = np.random.randint(0, 10)
    s2_z = np.random.randint(0, 4)
    
    # dodavanje ptice u jato
    jato.append(np.array([s1_x, s1_y, s1_z, s2_x, s2_y, s2_z]))
    
    # dodavanje u p_best zato sto nam je u ovom trenutku to nabolje
    P_best.append(np.array([s1_x, s1_y, s1_z, s2_x, s2_y, s2_z]))
    
    suma_razdaljina = 0
    
    # tacka S1 i tacka S2
    raz_S1_S2_x = s1_x - s2_x
    pow_S1_S2_x = math.pow(raz_S1_S2_x, 2)
    
    raz_S1_S2_y = s1_y - s2_y
    pow_S1_S2_y = math.pow(raz_S1_S2_y, 2)
    
    raz_S1_S2_z = s1_z - s2_z
    pow_S1_S2_z = math.pow(raz_S1_S2_z, 2)
    
    suma_S1_S2 = pow_S1_S2_x + pow_S1_S2_y + pow_S1_S2_z
    
    razdaljina_S1_S2 = math.sqrt(suma_S1_S2)
    
    # tacka A i tacka S1
    raz_A_S1_x = tacka_A[0] - s1_x
    pow_A_S1_x = math.pow(raz_A_S1_x, 2)
    
    raz_A_S1_y = tacka_A[1] - s1_y
    pow_A_S1_y = math.pow(raz_A_S1_y, 2)
    
    raz_A_S1_z = tacka_A[2] - s1_z
    pow_A_S1_z = math.pow(raz_A_S1_z, 2)
    
    suma_A_S1 = pow_A_S1_x + pow_A_S1_y + pow_A_S1_z
    
    razdaljina_A_S1 = math.sqrt(suma_A_S1)
    
    # tacka B i tacka S1
    raz_B_S1_x = tacka_B[0] - s1_x
    pow_B_S1_x = math.pow(raz_B_S1_x, 2)
    
    raz_B_S1_y = tacka_B[1] - s1_y
    pow_B_S1_y = math.pow(raz_B_S1_y, 2)
    
    raz_B_S1_z = tacka_B[2] - s1_z
    pow_B_S1_z = math.pow(raz_B_S1_z, 2)
    
    suma_B_S1 = pow_B_S1_x + pow_B_S1_y + pow_B_S1_z
    
    razdaljina_B_S1 = math.sqrt(suma_B_S1)
    
    # tacka C i tacka S2
    raz_C_S2_x = tacka_C[0] - s2_x
    pow_C_S2_x = math.pow(raz_C_S2_x, 2)
    
    raz_C_S2_y = tacka_C[1] - s2_y
    pow_C_S2_y = math.pow(raz_C_S2_y, 2)
    
    raz_C_S2_z = tacka_C[2] - s2_z
    pow_C_S2_z = math.pow(raz_C_S2_z, 2)
    
    suma_C_S2 = pow_C_S2_x + pow_C_S2_y + pow_C_S2_z
    
    razdaljina_C_S2 = math.sqrt(suma_C_S2)
    
    # tacka D i tacka S2
    raz_D_S2_x = tacka_D[0] - s2_x
    pow_D_S2_x = math.pow(raz_D_S2_x, 2)
    
    raz_D_S2_y = tacka_D[1] - s2_y
    pow_D_S2_y = math.pow(raz_D_S2_y, 2)
    
    raz_D_S2_z = tacka_D[2] - s2_z
    pow_D_S2_z = math.pow(raz_D_S2_z, 2)
    
    suma_D_S2 = pow_D_S2_x + pow_D_S2_y + pow_D_S2_z
    
    razdaljina_D_S2 = math.sqrt(suma_D_S2)
    
    # Suma razdaljina
    suma_razdaljina = razdaljina_S1_S2 + razdaljina_A_S1 + razdaljina_B_S1 + razdaljina_C_S2 + razdaljina_D_S2
    
    # pamcenje sume za svakog clana jata
    P_best_suma.append(suma_razdaljina)
    
    if(G_best_suma == -1 or G_best_suma > suma_razdaljina):
        G_best = P_best[i][:]
        G_best_suma = suma_razdaljina
        
    # vektor brzine za datu pticu u jatu
    nule = np.zeros(6) # trenutno stojimo u mestu
    vektor_brzine.append(nule)

w = 0.5 # preporuka profesora
V_max = 1.4 # preporuka profesora

c1 = c2 = 1.494 # sa prezentacije
        
for i in range(1500):
    for j in range(10 * D):
        razlika_P_best_jato = P_best[j] - jato[j]
        razlika_G_best_jato = G_best - jato[j]
        
        vektor_brzine_n = w * vektor_brzine[j] + c1 * random.random() * razlika_P_best_jato + c2 * random.random() * razlika_G_best_jato
        
        for granica in range(6):
            if(V_max < vektor_brzine_n[granica]):
                vektor_brzine_n[granica] = V_max
                
        suma_jato_vektor_brzine_n = jato[j] + vektor_brzine_n
        
        jato[j] = suma_jato_vektor_brzine_n
        vektor_brzine[j] = vektor_brzine_n
        
        suma_razdaljina = 0
    
        # tacka S1 i tacka S2
        raz_S1_S2_x = jato[j][0] - jato[j][3]
        pow_S1_S2_x = math.pow(raz_S1_S2_x, 2)
        
        raz_S1_S2_y = jato[j][1] - jato[j][4]
        pow_S1_S2_y = math.pow(raz_S1_S2_y, 2)
        
        raz_S1_S2_z = jato[j][2] - jato[j][5]
        pow_S1_S2_z = math.pow(raz_S1_S2_z, 2)
        
        suma_S1_S2 = pow_S1_S2_x + pow_S1_S2_y + pow_S1_S2_z
        
        razdaljina_S1_S2 = math.sqrt(suma_S1_S2)
        
        # tacka A i tacka S1
        raz_A_S1_x = tacka_A[0] - jato[j][0]
        pow_A_S1_x = math.pow(raz_A_S1_x, 2)
        
        raz_A_S1_y = tacka_A[1] - jato[j][1]
        pow_A_S1_y = math.pow(raz_A_S1_y, 2)
        
        raz_A_S1_z = tacka_A[2] - jato[j][2]
        pow_A_S1_z = math.pow(raz_A_S1_z, 2)
        
        suma_A_S1 = pow_A_S1_x + pow_A_S1_y + pow_A_S1_z
        
        razdaljina_A_S1 = math.sqrt(suma_A_S1)
        
        # tacka B i tacka S1
        raz_B_S1_x = tacka_B[0] - jato[j][0]
        pow_B_S1_x = math.pow(raz_B_S1_x, 2)
        
        raz_B_S1_y = tacka_B[1] - jato[j][1]
        pow_B_S1_y = math.pow(raz_B_S1_y, 2)
        
        raz_B_S1_z = tacka_B[2] - jato[j][2]
        pow_B_S1_z = math.pow(raz_B_S1_z, 2)
        
        suma_B_S1 = pow_B_S1_x + pow_B_S1_y + pow_B_S1_z
        
        razdaljina_B_S1 = math.sqrt(suma_B_S1)
        
        # tacka C i tacka S2
        raz_C_S2_x = tacka_C[0] - jato[j][3]
        pow_C_S2_x = math.pow(raz_C_S2_x, 2)
        
        raz_C_S2_y = tacka_C[1] - jato[j][4]
        pow_C_S2_y = math.pow(raz_C_S2_y, 2)
        
        raz_C_S2_z = tacka_C[2] - jato[j][5]
        pow_C_S2_z = math.pow(raz_C_S2_z, 2)
        
        suma_C_S2 = pow_C_S2_x + pow_C_S2_y + pow_C_S2_z
        
        razdaljina_C_S2 = math.sqrt(suma_C_S2)
        
        # tacka D i tacka S2
        raz_D_S2_x = tacka_D[0] - jato[j][3]
        pow_D_S2_x = math.pow(raz_D_S2_x, 2)
        
        raz_D_S2_y = tacka_D[1] - jato[j][4]
        pow_D_S2_y = math.pow(raz_D_S2_y, 2)
        
        raz_D_S2_z = tacka_D[2] - jato[j][5]
        pow_D_S2_z = math.pow(raz_D_S2_z, 2)
        
        suma_D_S2 = pow_D_S2_x + pow_D_S2_y + pow_D_S2_z
        
        razdaljina_D_S2 = math.sqrt(suma_D_S2)
        
        # Suma razdaljina
        suma_razdaljina = razdaljina_S1_S2 + razdaljina_A_S1 + razdaljina_B_S1 + razdaljina_C_S2 + razdaljina_D_S2
        
        if(suma_razdaljina < G_best_suma):
            G_best = jato[j][:]
            G_best_suma = suma_razdaljina
        
        if(suma_razdaljina < P_best_suma[j]):
            P_best[j] = jato[j][:]
            P_best_suma[j] = suma_razdaljina
       
print("Najbolji minimum pronadjen iz optimizacione funkcije jata(PSO) : ")            
print(G_best_suma)            

print("Tacka S1(x,y,z) : ")
print(G_best[0], G_best[1], G_best[2])     

print("Tacka S2(x,y,z) : ")
print(G_best[3], G_best[4], G_best[5])      
            
    