# Create a log-log plot for y = x³ for x values from 1 to 1000. Add appropriate labels and a title.
import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(1, 1000, 1000)
y = x**3

# Create a figure and a set of subplots
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 10))

# First subplot: log-log plot
ax1.loglog(x, y)
ax1.set_title("y = x³ (Log-Log)")
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.grid(True)
ax1.legend(["y = x³"])

# Second subplot: linear plot
ax2.plot(x, y)
ax2.set_title("y = x³")
ax2.set_xlabel("x")
ax2.set_ylabel("y")
ax2.grid(True)
ax2.legend(["y = x³"])

# Adjust layout and show the plot
plt.tight_layout()
plt.show()
