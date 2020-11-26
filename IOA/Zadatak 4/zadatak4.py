# -*- coding: utf-8 -*-
"""Zadatak4.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1fA6ISA8Lj_qdbH_cDMBQF2bTnNe99LjV
"""

import matplotlib.pyplot as plt
import numpy as np
from scipy import special


x = np.arange(0, 20, 0.25)


plt.style.use('dark_background')
plt.title('Sferna baselova funkcija od 0 do 20')


plt.plot(x, special.spherical_jn(1, x), label="n = 1")   
plt.plot(x, special.spherical_jn(2, x), label="n = 2")  

plt.xlabel('x')
plt.ylabel('Jn(x)')
plt.grid()
plt.legend(frameon=True, loc='lower center', ncol=2)
plt.show()