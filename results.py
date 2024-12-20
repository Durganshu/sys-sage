import csv
from collections import defaultdict
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from datetime import datetime

class Qubit:
    def __init__(self, index):
        self.index = index
        self.timestamps = []
        self.properties = []
        self.neighbour_count = None

# Dictionary to store Qubit objects by their index
qubits = defaultdict(lambda: None)

csv_file = "/home/diogenes/sys-sage/build/examples/output.csv"

with open(csv_file, "r") as file:
    reader = csv.reader(file)
    for row in reader:
        timestamp, qubit_index, neighbour_count, qubit_property = row
        qubit_index = int(qubit_index)
        neighbour_count = int(neighbour_count)
        qubit_property = float(qubit_property)
        
        if qubits[qubit_index] is None:
            qubits[qubit_index] = Qubit(qubit_index)
            qubits[qubit_index].neighbour_count = neighbour_count
        
        qubits[qubit_index].timestamps.append(timestamp)
        qubits[qubit_index].properties.append(qubit_property)

# Example: Accessing data for a specific qubit
# for qubit_index, qubit in qubits.items():
#     print(f"Qubit {qubit_index}:")
#     print(f"  Neighbour Count: {qubit.neighbour_count}")
    #print(f"  Timestamps: {qubit.timestamps[:]}")  # Display first 5 timestamps
    #print(f"  Properties: {qubit.properties[:]}")  # Display first 5 properties

# Prepare data for heatmap
num_timestamps = 54
num_qubits = 20

# Initialize the matrix for weights
heatmap_data = np.full((num_timestamps, num_qubits), np.nan)

# Initialize the matrix for neighbor counts
neighbor_count_data = np.full((num_timestamps, num_qubits), np.nan)

# Find the unique sorted timestamps to create a mapping
unique_timestamps = sorted(set(ts for qubit in qubits.values() for ts in qubit.timestamps))
timestamp_to_index = {ts: i for i, ts in enumerate(unique_timestamps)}

# Populate the matrices
for qubit_index, qubit in qubits.items():
    for i, timestamp in enumerate(qubit.timestamps):
        # Map timestamp to a valid row index using the timestamp_to_index mapping
        ts_index = timestamp_to_index[timestamp]
        heatmap_data[ts_index, qubit_index] = qubit.properties[i]
        neighbor_count_data[ts_index, qubit_index] = qubit.neighbour_count

# Format timestamps
unique_timestamps = sorted(set(ts for qubit in qubits.values() for ts in qubit.timestamps))
formatted_timestamps = [
    datetime.strptime(str(ts), "%Y%m%d").strftime("%d-%m-%Y") for ts in unique_timestamps
]

# Reduce the number of labels by selecting every alternate timestamp
alternate_indices = np.arange(0, len(formatted_timestamps), 2)
alternate_timestamps = [formatted_timestamps[i] for i in alternate_indices]

# Plot heatmap for weights
plt.figure(figsize=(12, 8))
plt.title("Qubit Weights Heatmap")

plt.imshow(heatmap_data, aspect='auto', cmap='viridis')
plt.colorbar(label="Qubit Weight")
plt.xlabel("Qubit ID")
plt.ylabel("Timestamp")
plt.xticks(ticks=np.arange(len(qubits)), labels=[f"{i}" for i in range(len(qubits))])
plt.yticks(ticks=alternate_indices, labels=alternate_timestamps)

plt.tight_layout()
plt.show()

# Plot heatmap for neighbor counts
# plt.figure(figsize=(12, 8))
# plt.title("Qubit Neighbor Counts Heatmap")

# plt.imshow(neighbor_count_data, aspect='auto', cmap='plasma')
# plt.colorbar(label="Neighbor Count")
# plt.xlabel("Qubit ID")
# plt.ylabel("Timestamp")
# plt.xticks(ticks=np.arange(len(qubits)), labels=[f"Qubit {i}" for i in range(len(qubits))], rotation=45)
# plt.yticks(ticks=alternate_indices, labels=alternate_timestamps)

# plt.tight_layout()
# plt.show()

neighbor_counts = [qubit.neighbour_count for qubit in qubits.values()]

# Create the bar plot
plt.figure(figsize=(12, 6))
plt.title("Number of Neighbors for Each Qubit")

plt.bar(range(len(qubits)), neighbor_counts, color="skyblue")
plt.xlabel("Qubit ID")
plt.ylabel("Number of Neighbors")
plt.xticks(ticks=range(len(qubits)), labels=[f"{i}" for i in range(len(qubits))])
plt.tight_layout()
plt.show()