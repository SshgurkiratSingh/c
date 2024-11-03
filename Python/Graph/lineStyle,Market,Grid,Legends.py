import matplotlib.pyplot as plt
x = [1, 2, 3, 4, 5]
y1 = [1, 4, 9, 16, 25]
y2 = [1, 8, 27, 64, 125]
plt.plot(x, y1, color="red", linestyle="--", marker="o", label="y=x**2")
plt.plot(x, y2, color="b", linestyle=":", marker="o", label="y=x**3")
plt.grid(True)
plt.title("Line Style,Market,Grid,Legends")
plt.xlabel("Value")
plt.ylabel("Square of Value")
plt.legend()
plt.show()
