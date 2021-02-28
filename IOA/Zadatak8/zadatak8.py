# -*- coding: utf-8 -*-
"""
Created on Thu Dec 17 04:43:12 2020

@author: aleks
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

globalniMinimum = -1
globalniMinimumIndex = []
populacija = []
populacijaCenaKostanja = []
najbolji = np.zeros(100000)
populacijaY = []
novaPopulacija = []
cenaKostanja = []

for i in range(20):
    
  for createPop in range(2000):
    randNum = np.random.randint(2, size=64)
    populacija.append(randNum) # kreiranje populacije random niz 0 i 1

  minimumPopulacija = -1

  # imamo 100000 iteracija i 2000 populaciju 100000/2000 = 50
  for loop in range(49):
      
    populacijaCenaKostanja.clear()
    novaPopulacija.clear()
    
    for index in range(2000):
      ukupno = 0
      test_populacija = populacija[index]
      
      #cena kostanja
      for x_in_D in range(64):
          ukupno += D[x_in_D] * test_populacija[x_in_D]
      ukupno = 2**26 - ukupno
      if(ukupno < 0):
          vrednostCene = 2**26
      else:
          vrednostCene = ukupno

      pair = (index, vrednostCene)

      populacijaCenaKostanja.append(pair)

      if(minimumPopulacija == -1 or populacijaCenaKostanja[index][1] < minimumPopulacija):
        minimumPopulacija = populacijaCenaKostanja[index][1]
      populacijaY.append(minimumPopulacija)
      najbolji[loop * 2000 + index] += minimumPopulacija / 20.0
    
    populacijaCenaKostanja = sorted(populacijaCenaKostanja, key=lambda k:k[1]) # iz nekog razloga ne radi sort

    if(globalniMinimum == -1 or populacijaCenaKostanja[0][1] < globalniMinimum):
      globalniMinimumIndex = populacija[populacijaCenaKostanja[0][0]][:]
      globalniMinimum = populacijaCenaKostanja[0][1]    

    while(len(novaPopulacija) != 2000):
      if(random.random() < 0.8):
        dete1 = []
        dete2 =[]

        roditelj1 = random.randint(0, 400)
        roditelj2 = random.randint(0, 400)

        randP = random.randint(0, 48)

        p1 = populacija[populacijaCenaKostanja[roditelj1][0]][:randP + 1]
        p2 = populacija[populacijaCenaKostanja[roditelj1][0]][randP - 63:]

        q1 = populacija[populacijaCenaKostanja[roditelj2][0]][:randP + 1]
        q2 = populacija[populacijaCenaKostanja[roditelj2][0]][randP - 63:]

        dete1 = np.append(p1, q2)
        dete2 = np.append(q1, p2)

        novaPopulacija.append(dete1)
        novaPopulacija.append(dete2)
    
    # mutacija
    for mutation in range(2000):
      if(random.random() < 0.1):
        randMutiraniP = random.randint(0, 63)
        novaPopulacija[mutation][randMutiraniP] = 1 - novaPopulacija[mutation][randMutiraniP]
    
    populacija = novaPopulacija[:]

  for index in range(2000):
    ukupno = 0
    test_populacija = populacija[index]
    
    #cena kostanja
    for x_in_D in range(64):
        ukupno += D[x_in_D] * test_populacija[x_in_D]
    ukupno = 2**26 - ukupno
    if(ukupno < 0):
        vrednostCene = 2**26
    else:
        vrednostCene = ukupno

    pair = (index, vrednostCene)

    populacijaCenaKostanja.append(pair)

    if(minimumPopulacija == -1 or populacijaCenaKostanja[index][1] < minimumPopulacija):
      minimumPopulacija = populacijaCenaKostanja[index][1]
    populacijaY.append(minimumPopulacija)
    najbolji[49 * 2000 + index] += minimumPopulacija / 20.0
  
  populacijaCenaKostanja = sorted(populacijaCenaKostanja, key=lambda k:k[1])

  if(populacijaCenaKostanja[0][1] < globalniMinimum):
    globalniMinimumIndex = populacija[populacijaCenaKostanja[0][0]][:]
    globalniMinimum = populacijaCenaKostanja[0][1]
  #test = 'iter' + f'{i}'
  plt.plot(range(1,100001), populacijaY)#, label=test)
  populacijaY.clear()
  populacija.clear()

plt.style.use('dark_background')
plt.title("Kumulativni minimum")
plt.grid(True)
plt.xscale("log")
plt.yscale("log")
#plt.legend(frameon=True, loc='lower center', ncol=10) ne vidi se grafik lepo posle
plt.show()

plt.style.use('dark_background')
plt.title("Srednje najbolje resenje")
plt.plot(range(1,100001), najbolji, 'r', label="x_cumulative")
plt.xscale("log")
plt.yscale("log")
plt.grid(True)
plt.legend(frameon=True, loc='lower center')
plt.show()

print("Najbolji globalni minimum je : ")
print(globalniMinimum)

print("Najbolji globalni minimum cene kostanja je :")
print(globalniMinimumIndex)

