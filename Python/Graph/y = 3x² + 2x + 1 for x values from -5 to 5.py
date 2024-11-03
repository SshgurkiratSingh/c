# Question 2: Plot a quadratic equation y = 3x² + 2x + 1 for x values from -5 to 5. Use the xlabel and ylabel functions to label the axes.

import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(-5, 5, 15)
y = 3*x**2+2*x+1
plt.plot(x, y)
plt.title("y=3x²+2x+1")
plt.xlabel("x")
plt.ylabel("y")
plt.show()