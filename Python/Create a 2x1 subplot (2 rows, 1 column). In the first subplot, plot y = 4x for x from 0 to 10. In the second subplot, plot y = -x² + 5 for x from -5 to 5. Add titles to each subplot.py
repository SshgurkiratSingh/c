# Create a 2x1 subplot (2 rows, 1 column). In the first subplot, plot y = 4x for x from 0 to 10. In the second subplot, plot y = -x² + 5 for x from -5 to 5. Add titles to each subplot

import matplotlib.pyplot as plt
import numpy as np
x1 = np.linspace(0, 10, 15)
y2 = 4*x1
x2 = np.linspace(-5, 5, 15)
y2 = -x2**2 + 5
plt.subplot(2, 1, 1)
plt.plot(x1, y2)
plt.title("y=4x")
plt.subplot(2, 1, 2)
plt.plot(x2, y2)
plt.title("y=-x²+5")
plt.show()
