# -*- coding: utf-8 -*-
"""
Created on Thu Dec 24 01:03:35 2020

@author: aleks
"""

import numpy as np
import math
import random
import matplotlib.pyplot as plt
from sys import exit

S = [
    2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01,   
    1.022985539042393e-01, 7.905975891960761e-02,
    5.717509542148174e-02, 3.155886625106896e-02, 
    -6.242228581847679e-03,-6.565183775481365e-02,
    -8.482380513926287e-02,-1.828677714588237e-02,  
    3.632382803076845e-02, 7.654845872485493e-02, 
    1.152250132891757e-01, 1.631742367154961e-01,
    2.358469152696193e-01, 3.650430801728451e-01,  
    5.816044173713664e-01, 5.827732223753571e-01,  
    3.686942505423780e-01
]

populacija = []
finalyPopulacijaVersion = []
D = 6
Cr = 0.9

# ja sam koristio i varijantu 50 i varijantu 10 * D, obe varijante rade, pa sam prvu ostavio pod komentar a drugu ostavio da radi
# nadam se da to ne predstavlja problem
#for i in range(50):
for i in range(10 * D): # na slajdu 18 je zapisano ili 50 ili 10 * D
    populacija_array = np.random.uniform(-15, 15, 6)
    populacija.append(populacija_array)
    #populacija_array.clear()
    
beginT = []
for i in range(20):
    inner = 2 * math.pi * i
    first = 15 * math.cos(inner / 20) # N = 20 - 20 tacaka, 15 je poluprecnik R0 = 15m
    second = 15 * math.sin(inner / 20) # N = 20 - 20 tacaka, 15 je poluprecnik R0 = 15m
    beginT.append([first, second])
    
for i in range(10000):

    finalyPopulacijaVersion.clear()
    
    #for x in range(50):
    for x in range(10 * D):
        
        x_a = -1
        while(x_a == -1):
            #random_number = random.randint(0,49)
            random_number = random.randint(0, 10 * D - 1)
            if(x != random_number):
                x_a = random_number
                
        x_b = -1
        while(x_b == -1):
            #random_number = random.randint(0,49)
            random_number = random.randint(0, 10 * D - 1)
            if(x != random_number):
                x_b = random_number
        
        x_c = -1
        while(x_c == -1):
            #random_number = random.randint(0,49)
            random_number = random.randint(0, 10 * D - 1)
            if(x != random_number):
                x_c = random_number
                
        
        
        F = 0.8
        
        pop_x_a = populacija[x_a]
        pop_x_b = populacija[x_b]
        pop_x_c = populacija[x_c]
            
        final_populacija = pop_x_a + F * (pop_x_b - pop_x_c)
        
        random_number = random.randint(0, D)
        
        if(random_number != 0):
            random_number = random_number - 1
            
        array_ones = np.ones(6)
        
        for new_pop in range(6):
            if(random.random() < Cr or new_pop == random_number):
                array_ones[new_pop] = final_populacija[new_pop]
            else:
                array_ones[new_pop] = populacija[x][new_pop]
            
            #if(new_pop == random_number):
            #    array_ones[new_pop] = final_populacija[new_pop]
            #else:
            #    array_ones[new_pop] = populacija[x][new_pop]
        
        finalyPopulacijaVersion.append(array_ones[:])
        
    
    #for opt in range(50):
    for opt in range(10 * D):
        function_x = 0  
        function_y = 0
        
        if((math.sqrt(math.pow(populacija[opt][0],2) + math.pow(populacija[opt][1],2))) < 15 and (math.sqrt(math.pow(populacija[opt][2],2) + math.pow(populacija[opt][3],2))) < 15):
            for func in range(20):
                powBegin0 = beginT[func][0]
                powBegin1 = beginT[func][1]
                
                firstPow = math.pow(powBegin0 - populacija[opt][0], 2)
                secondPow = math.pow(powBegin1 - populacija[opt][1], 2)
                thirdPow = math.pow(powBegin0 - populacija[opt][2], 2)
                forthPow = math.pow(powBegin1 - populacija[opt][3], 2)
                
                firstSqrt = math.sqrt(firstPow + secondPow)
                secondSqrt = math.sqrt(thirdPow + forthPow)
                
                A1 = populacija[opt][4]
                A2 = populacija[opt][5]
                
                finalyResult = A1 / firstSqrt + A2 / secondSqrt - S[func]
                function_x += math.pow(finalyResult,2)
        else:
            function_x = 100
        
        # desava mi se da ovde nekad baci error a nekada ne u vecini slucajeva kod radi
        if(math.sqrt(math.pow(finalyPopulacijaVersion[opt][0],2) + math.pow(finalyPopulacijaVersion[opt][1],2)) < 15 and math.sqrt(math.pow(finalyPopulacijaVersion[opt][2],2) + math.pow(finalyPopulacijaVersion[opt][3],2))):
            for func in range(20):
                powBegin0 = beginT[func][0]
                powBegin1 = beginT[func][1]
                
                firstPow = math.pow(powBegin0 - finalyPopulacijaVersion[opt][0], 2)
                secondPow = math.pow(powBegin1 - finalyPopulacijaVersion[opt][1], 2)
                thirdPow = math.pow(powBegin0 - finalyPopulacijaVersion[opt][2], 2)
                forthPow = math.pow(powBegin1 - finalyPopulacijaVersion[opt][3], 2)
                
                firstSqrt = math.sqrt(firstPow + secondPow)
                secondSqrt = math.sqrt(thirdPow + forthPow)
                
                A1 = finalyPopulacijaVersion[opt][4]
                A2 = finalyPopulacijaVersion[opt][5]
                
                finalyResult = A1 / firstSqrt + A2 / secondSqrt - S[func]
                
                function_y += math.pow(finalyResult,2)
        else:
            function_y = 100
        
        if(math.pow(10,-14) >= function_x):
            print("Koordinate pozicija i konstante nepoznatih izvora: (Xp1, Yp1, Xp2, Yp2, A1, A2)")
            print(populacija[opt])
            print("Nasa finalna optimizacija koja ispunjava uslov")
            print(function_x)
            exit(1)
            
        if(function_x > function_y):
            populacija[opt] = finalyPopulacijaVersion[opt][:]
            
            
    