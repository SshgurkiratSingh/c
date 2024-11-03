import matplotlib.pyplot as plt

# Data
x = [1, 2, 3, 4, 5]
y = [1, 10, 100, 1000, 10000]

# Semilog plot (y-axis log scale)
plt.semilogy(x, y)
plt.title('Semilog Plot (y-axis log scale)')
plt.xlabel('X values')
plt.ylabel('Y values (log scale)')

# Show plot
plt.show()
