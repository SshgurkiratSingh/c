import matplotlib.pyplot as plt
import numpy as np


data = np.random.randn(1000)
plt.hist(data,bins=50)
plt.title("Histogram")
plt.xlabel("Value")
plt.ylabel("Frequency")

plt.show()