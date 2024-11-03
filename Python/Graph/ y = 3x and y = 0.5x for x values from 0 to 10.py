# Question 2: Create a plot of the functions y = 3x and y = 0.5x for x values from 0 to 10. Use different markers and line styles for each, and ensure that both functions appear in the legend.

import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(0, 10, 15)
y1 = 3*x
y2 = 0.5*x
plt.plot(x, y1, color="red", linestyle="--", marker="+", label="y=3x")
plt.plot(x, y2, color="b", linestyle=":", marker="*", label="y=0.5x")
plt.legend()
plt.show()