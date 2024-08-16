import csv
import statistics

# Initialize lists to hold values from each column
column1 = []
column2 = []
column3 = []

# Read the data from the file
with open('results.txt', 'r') as file:
    reader = csv.reader(file, delimiter=',')
    
    # Loop through each row in the file and append values to respective columns
    for row in reader:
        column1.append(float(row[0]))
        column2.append(float(row[1]))
        column3.append(float(row[2]))

# Calculate min, max, and avg for each column
min_col1, max_col1, avg_col1 = min(column1), max(column1), statistics.mean(column1)
min_col2, max_col2, avg_col2 = min(column2), max(column2), statistics.mean(column2)
min_col3, max_col3, avg_col3 = min(column3), max(column3), statistics.mean(column3)

# Print the results
print(f"Column 2 - Min: {min_col2}, Max: {max_col2}, Avg: {avg_col2}")
print(f"Column 1 - Min: {min_col1}, Max: {max_col1}, Avg: {avg_col1}")
print(f"Column 3 - Min: {min_col3}, Max: {max_col3}, Avg: {avg_col3}")
