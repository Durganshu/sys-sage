/* Possible exports
export CPATH=$CPATH:/home/diogenes/sys-sage/build/_deps/qinfo-src/include/
export CPATH=$CPATH:/home/diogenes/sys-sage/build/_deps/qdmi-src/include
export CONF_IBM=/home/diogenes/qdmi.git/inputs/conf.json
export QDMI_CONFIG_FILE=/home/diogenes/sys-sage/build/_deps/qdmi-src/.qdmi-config
export PROP_IBM=/home/diogenes/qdmi.git/inputs/props.json
*/

#include <iostream>
#include <string.h>
#include <iomanip>
#include "sys-sage.hpp"
#include <chrono>
#include <fstream>

int main()
{
    std::cout << std::setprecision(15);
    // Create an instance of the interface
    // To-Do: Consider QDMI_Parser as a static class
    QDMI_Parser qdmi;

    // Use QDMI_Parser to create the topology of either all the backends or one of the backends
    /*******************************************Method 1**********************************************/

    Topology* qc_topo = new Topology();
    auto start = std::chrono::high_resolution_clock::now();
    qdmi.createQcTopo(qc_topo);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    QDMI_Parser::timings.push_back(duration.count());
    // std::cout << "Time taken by createQcTopo: " << duration.count() << " milliseconds" << std::endl;
    // cout << "---------------- Printing the configuration of IBM Backend----------------" << endl;
    // qc_topo->PrintSubtree();
    // cout << "---------------- Printing Qubit Coupling Mappings for IBM Backend----------------" << endl;
    QuantumBackend* qc = dynamic_cast<QuantumBackend*>(qc_topo->GetChild(0));
    // int total_qubits = qc->CountAllSubcomponents();
    // for (int i = 0; i < total_qubits; i++)
    // {
    //     Qubit* q = dynamic_cast<Qubit*>(qc->GetChild(i));
    //     std::cout << "Qubit " << i << " has coupling map { ";
    //     auto coupling_map = q->GetCouplingMapping();
    //     for (long unsigned j = 0; j < coupling_map.size(); j++)
    //     {
    //         std::cout << coupling_map[j] << " ";
    //     }
    //     std::cout << "}\n";
    // }
    // cout << "---------------- Printing Supported Gate Types for IBM Backend----------------" << endl;
    // auto _1q_gates = qc->Get1QGates();
    // auto _2q_gates = qc->Get2QGates();
    // auto _mq_gates = qc->GetMQGates();
    // auto _0q_gates = qc->GetNoTypeGates();

    // if(_1q_gates.size())
    // {
    //     int size = _1q_gates.size();
    //     std::cout << "Total " << size << " 1-Qubit gate(s)\n";
    //     for (int i = 0; i < size; ++i)
    //     {   
    //         std::cout << "  Gate name:" << _1q_gates[i]->GetName() << ", ";
    //         std::cout << "Gate size:" << _1q_gates[i]->GetGateSize() << ", ";
    //         std::cout << "Gate fidelity:" << _1q_gates[i]->GetFidelity() << "\n";
    //     }

    // }
    // if(_2q_gates.size())
    // {
    //     int size = _2q_gates.size();
    //     std::cout << "Total " << size << " 2-Qubit gate(s)\n";
    //     for (int i = 0; i < size; ++i)
    //     {   
    //         std::cout << "  Gate name:" << _2q_gates[i]->GetName() << ", ";
    //         std::cout << "Gate size:" << _2q_gates[i]->GetGateSize() << ", ";
    //         std::cout << "Gate fidelity:" << _2q_gates[i]->GetFidelity() << "\n";
    //     }
        
    // }
    // if(_mq_gates.size())
    // {
    //     int size = _mq_gates.size();
    //     std::cout << "Total " << size << " M-Qubit gate(s)\n";
    //     for (int i = 0; i < size; ++i)
    //     {   
    //         std::cout << "  Gate name:" << _mq_gates[i]->GetName() << ", ";
    //         std::cout << "Gate size:" << _mq_gates[i]->GetGateSize() << ", ";
    //         std::cout << "Gate fidelity:" << _mq_gates[i]->GetFidelity() << "\n";
    //     }
        
    // }
    // if(_0q_gates.size())
    // {
    //     int size = _0q_gates.size();
    //     std::cout << "Total " << size << " gate(s) with no type\n";
    //     for (int i = 0; i < size; ++i)
    //     {   
    //         std::cout << "  Gate name:" << _0q_gates[i]->GetName() << ", ";
    //         std::cout << "Gate size:" << _0q_gates[i]->GetGateSize() << ", ";
    //         std::cout << "Gate fidelity:" << _0q_gates[i]->GetFidelity() << "\n";
    //     }
        
    // }
    

    // std::cout << "---------------- Printing Qubit Properties for IBM Backend----------------" << endl;
    // for (int i = 0; i < total_qubits; i++)
    // {
    //     Qubit* q = dynamic_cast<Qubit*>(qc->GetChild(i));
    //     std::cout << "Qubit " << i << " has following properties: \n";
    //     std::cout << "      T1: " << q->GetT1() << "\n";
    //     std::cout << "      T2: " << q->GetT2() << "\n";
    //     std::cout << "      Readout Error: " << q->GetReadoutError() << "\n";
    //     std::cout << "      Readout Length: " << q->GetReadoutLength() << "\n";
    // }

    // std::cout << "---------------- Printing Coupling Maps of all the Qubits----------------" << endl;
    start = std::chrono::high_resolution_clock::now();
    auto children = qc->GetAllCouplingMaps();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    QDMI_Parser::timings.push_back(duration.count());
    for (auto i : QDMI_Parser::timings)
    {
        std::cout << i << ", ";
    }
    std::cout << "\n";
    std::ofstream outFile("results.txt");
    if (outFile.is_open()) {
        // Write each element of the vector to the file
        for (const double& value : QDMI_Parser::timings) {
            outFile << value << "\n";  // Write each double value followed by a newline
        }

        // Close the file stream
        outFile.close();
        std::cout << "Data has been written to run.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file run.txt" << std::endl;
    }
    // for (auto it = children.begin(); it != children.end(); ++it) {
    //     std::cout << "{" << it->first << ", " << it->second << "}\n";
    // }


    // /*******************************************Method 2**********************************************/
    // // auto quantum_backends = qdmi.get_available_backends();
    // // std::cout << "Total " << quantum_backends.size() << " devices found.\n";
    // // QuantumBackend* qc_topo = new QuantumBackend(0, quantum_backends[0].first);
    // // qdmi.createQcTopo(qc_topo, quantum_backends[0].second);

    // // cout << "---------------- Printing the configuration of QLM Backend ----------------" << endl;
    // // qc_topo->PrintSubtree();
    // // cout << "---------------- Printing Qubit Coupling Mappings of QLM Backend----------------" << endl;
    // // int total_qubits = qc_topo->CountAllSubcomponents();
    // // for (int i = 0; i < total_qubits; i++)
    // // {
    // //     Qubit* q = dynamic_cast<Qubit*>(qc_topo->GetChild(i));
    // //     std::cout << "Qubit " << i << " has coupling map { ";
    // //     auto coupling_map = q->GetCouplingMapping();
    // //     for (long unsigned j = 0; j < coupling_map.size(); j++)
    // //     {
    // //         std::cout << coupling_map[j] << " ";
    // //     }
    // //     std::cout << "}\n";
    // // }
       
    return 0;
}
