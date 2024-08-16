import matplotlib.pyplot as plt

# Data for x-axis (number of qubits) and y-axis (timings in milliseconds)
qubits = ['5', '7', '100', '500', '1000', '5000', '10000']
timings_createQcAllTopo = [0.141, 0.4223, 0.725, 4.197, 12.3790, 196.0385, 836.402]
timings_setQubits = [0.048, 0.25, 0.60, 3.930, 11.95, 194.41, 831.651]
timings_GetAllCouplingMaps = [0.00437, 0.01829, 0.039, 0.1425, 0.56325, 22.088, 101.7179]

# Create the plot
plt.figure(figsize=(10, 6))

# Plot the data
plt.plot(qubits, timings_createQcAllTopo, label="createQcAllTopo", marker='o')
plt.plot(qubits, timings_setQubits, label="setQubits", marker='o')
plt.plot(qubits, timings_GetAllCouplingMaps, label="GetAllCouplingMaps", marker='o')

# Set x-axis and y-axis labels with bold font
plt.xlabel('Number of Qubits', fontsize=12, fontweight='bold')
plt.ylabel('Time (ms)', fontsize=12, fontweight='bold')

# Set the title of the plot with bold font
plt.title('Timing Analysis of Functions by Number of Qubits', fontsize=14, fontweight='bold')

# Set the x-axis ticks with bold font
plt.xticks(qubits, fontsize=10, fontweight='bold')

# Set the y-axis ticks with bold font
plt.yticks(fontsize=10, fontweight='bold')

# Set the y-axis to a logarithmic scale
plt.yscale('log')

# Display the legend with bold font
plt.legend(fontsize=10)

# Show the plot
plt.grid(True)
plt.show()
