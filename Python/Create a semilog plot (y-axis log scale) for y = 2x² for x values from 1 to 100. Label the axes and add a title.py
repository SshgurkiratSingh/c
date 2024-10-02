import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(1, 100, 100)
y = 2 * x ** 2

# Create a figure and a set of subplots
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 10))

# First subplot: semilog plot
ax1.semilogy(x, y)
ax1.set_title("y = 2x² (Semilog)")
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.grid(True)
ax1.legend(["y = 2x²"])

# Second subplot: linear plot
ax2.plot(x, y)
ax2.set_title("y = 2x²")
ax2.set_xlabel("x")
ax2.set_ylabel("y")
ax2.grid(True)
ax2.legend(["y = 2x²"])

# Adjust layout and show the plot
plt.tight_layout()
plt.show()
