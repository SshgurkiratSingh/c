import matplotlib.pyplot as plt

# Data for bar chart
categories = ['A', 'B', 'C', 'D']
values = [3, 7, 2, 5]

# Vertical bar chart
plt.bar(categories, values)
plt.title('Bar Chart Example')
plt.xlabel('Categories')
plt.ylabel('Values')

# Show plot
plt.show()
