import matplotlib.pyplot as plt

# Data
x = [1, 10, 100, 1000, 10000]
y = [1, 10, 100, 1000, 10000]

# Log-log plot
plt.loglog(x, y)
plt.title('Log-Log Plot')
plt.xlabel('X values (log scale)')
plt.ylabel('Y values (log scale)')

# Show plot
plt.show()
