import subprocess

# Run the command 10 times
for i in range(10):
    # Execute the command
    subprocess.run(["./qdmi-test"], capture_output=True, text=True)
    
    # Read the results from results.txt
    with open("results.txt", "r") as results_file:
        lines = results_file.readlines()

    # Remove any leading/trailing whitespace and join them as a single row
    formatted_row = ", ".join(line.strip() for line in lines)

    # Append the formatted row to compiled_results.txt
    with open("compiled_results.txt", "a") as compiled_file:
        compiled_file.write(formatted_row + "\n")

    print(f"Run {i+1} completed and results appended to compiled_results.txt")
