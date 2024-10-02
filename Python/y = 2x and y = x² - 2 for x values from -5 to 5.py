# Question 1: Plot two functions: y = 2x and y = x² - 2 for x values from -5 to 5. Customize the line styles and colors. Add markers and a grid.

import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(-5, 5, 15)
y1 = 2*x
y2 = x**2 - 2
plt.plot(x, y1, color="#212121", linestyle="--", marker=".", label="y=2x")
plt.plot(x, y2, color="green", linestyle=":", marker="o", label="y=x²-2")
plt.grid(True)
plt.title("Line Style,Market,Grid,Legends")
plt.legend()
plt.show()