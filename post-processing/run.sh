#!/bin/bash

# List of configuration paths
configs=(
    "/home/diogenes/qdmi.git/inputs/conf.json /home/diogenes/qdmi.git/inputs/props.json"
    "/home/diogenes/ibmq_config/fake_armonk/conf.json /home/diogenes/ibmq_config/fake_armonk/props.json"
    "/home/diogenes/ibmq_config/fake_cairo/conf.json /home/diogenes/ibmq_config/fake_cairo/props.json"
    "/home/diogenes/ibmq_config/ibm-100/conf.json /home/diogenes/ibmq_config/ibm-100/props.json"
    "/home/diogenes/ibmq_config/ibm-500/conf.json /home/diogenes/ibmq_config/ibm-500/props.json"
    "/home/diogenes/ibmq_config/ibm-1000/conf.json /home/diogenes/ibmq_config/ibm-1000/props.json"
    "/home/diogenes/ibmq_config/ibm-5000/conf.json /home/diogenes/ibmq_config/ibm-5000/props.json"
    "/home/diogenes/ibmq_config/ibm-10000/conf.json /home/diogenes/ibmq_config/ibm-10000/props.json"
)

# Path to the executable
executable_path="./qdmi-test"

# Loop over each configuration and run the executable
for config in "${configs[@]}"; do
    # Split the configuration into CONF_IBM and PROP_IBM
    read -r CONF_IBM PROP_IBM <<< "$config"
    
    # Export the environment variables
    export CONF_IBM="$CONF_IBM"
    export PROP_IBM="$PROP_IBM"

    # Print the environment variables (for debugging)
    echo "Running with CONF_IBM=$CONF_IBM and PROP_IBM=$PROP_IBM"

    # Run the executable
    $executable_path
    
    # Check if the executable ran successfully
    if [ $? -ne 0 ]; then
        echo "Execution failed for CONF_IBM=$CONF_IBM and PROP_IBM=$PROP_IBM"
        exit 1
    fi
done

echo "All executions completed successfully."
