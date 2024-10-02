# Question 1: Create a simple plot of y = 2x for x values from 0 to 10. Add appropriate labels and a title

import matplotlib.pyplot as plt
import numpy as np
x=np.linspace(0,10,15)
y=2*x
plt.plot(x,y)
plt.title("y=2x")
plt.xlabel("x")
plt.ylabel("y")
plt.show()