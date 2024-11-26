/**
 * @file qdmi-parser.hpp
 * @brief sys-sage's interface to QDMI.
 */

#include "qdmi-parser.hpp"

//QInfo QdmiParser::info; 
QDMI_Session QdmiParser::session; 

extern "C" QdmiParser::QdmiParser() : num_devices(0)
{
    initiateSession();
}

extern "C" int QdmiParser::initiateSession()
{
    auto ret = QDMI_Driver_init();
    if(ret == QDMI_SUCCESS)
        std::cout << "Driver Initialized\n";
    else
        std::cout << "Error starting the driver\n";
       
    ret =  QDMI_session_alloc(&session);
    if(ret == QDMI_SUCCESS)
        std::cout << "Session allocated\n";
    else
        std::cout << "Error allocating the session\n";
    
    std::cout << "   [sys-sage]...............Initiated "
                  << "QDMI session\n";

    size_t num_entries = 1;
    ret = QDMI_session_get_devices(session, num_entries, &device, &num_devices);
    if(ret == QDMI_SUCCESS)
        std::cout << "Found " << num_devices << " devices.\n";
    else
        std::cout << "Unable to find any device.\n";
    return 0;    

}

size_t QdmiParser::get_qubits_num() const
{
    size_t num_qubits = 0;
    const int ret =
        QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_QUBITSNUM,
                                   sizeof(size_t), &num_qubits, nullptr);
    //throw_if_error(ret, "Failed to query the number of qubits.");
    return num_qubits;
}

std::map<std::string, QDMI_Operation> QdmiParser::get_operation_map() const
{
    size_t ops_num = 0;
    int ret = QDMI_query_get_operations(device, 0, nullptr, &ops_num);
    //throw_if_error(ret, "Failed to retrieve operation number.");
    std::vector<QDMI_Operation> ops(ops_num);
    ret = QDMI_query_get_operations(device, ops_num, ops.data(), nullptr);
   // throw_if_error(ret, "Failed to retrieve operations.");
    std::map<std::string, QDMI_Operation> ops_map;
    for (const auto &op : ops) {
      size_t name_length = 0;
      ret = QDMI_query_operation_property(device, op, 0, nullptr,
                                          QDMI_OPERATION_PROPERTY_NAME, 0,
                                          nullptr, &name_length);
      //throw_if_error(ret, "Failed to retrieve operation name length.");
      std::string name(name_length, '\0');
      ret = QDMI_query_operation_property(device, op, 0, nullptr,
                                          QDMI_OPERATION_PROPERTY_NAME,
                                          name_length, name.data(), nullptr);
      //throw_if_error(ret, "Failed to retrieve operation name.");
      ops_map.emplace(name, op);
    }
    return ops_map;
}

std::vector<std::pair<QDMI_Site, QDMI_Site>> QdmiParser::get_coupling_map() const
{
    size_t size = 0;
    int ret = QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_COUPLINGMAP,
                                         0, nullptr, &size);
    //throw_if_error(ret, "Failed to query the coupling map size.");
    const auto coupling_map_size = size / sizeof(QDMI_Site);
    if (coupling_map_size % 2 != 0) {
      throw std::runtime_error("The coupling map needs to have an even number of "
                               "elements.");
    }
    // `std::vector` guarantees that the elements are contiguous in memory.
    std::vector<std::pair<QDMI_Site, QDMI_Site>> coupling_pairs(
        coupling_map_size / 2);
    ret = QDMI_query_device_property(
        device, QDMI_DEVICE_PROPERTY_COUPLINGMAP, size,
        static_cast<void *>(coupling_pairs.data()), nullptr);
    //throw_if_error(ret, "Failed to query the coupling map.");
    return coupling_pairs;
}
  
// extern "C" void QdmiParser::getCouplingMapping(QDMI_Device dev, QDMI_Qubit qubit, std::vector<int> &coupling_mapping, int &coupling_map_size)
// {

//     if (qubit->size_coupling_mapping == 0)
//     {
//         std::cout << "   [sys-sage]...............No coupling mapping for qubit\n";
//         return;
//     }

//     coupling_map_size = qubit->size_coupling_mapping;
//     coupling_mapping.resize(coupling_map_size);

//     std::copy(qubit->coupling_mapping, qubit->coupling_mapping + coupling_map_size, coupling_mapping.begin());
// }

// extern "C" void QdmiParser::getQubitProperties(QDMI_Device dev, QDMI_Qubit qubit)
// {
//     int scope;
//     // Declare prop as a vector
//     std::vector<int> prop{QDMI_T1_TIME, QDMI_T2_TIME, QDMI_READOUT_ERROR, QDMI_READOUT_LENGTH};
//     std::array<std::string, 4> properties{"T1", "T2", "readout_error", "readout_length"};
//     double value;
//     for (size_t i = 0; i < 4; ++i)
//     {
//         // QDMI_Qubit_property prop_index;
//         QDMI_Qubit_property prop_index = new (QDMI_Qubit_property_impl_t);
//         prop_index->name = prop[i];
//         int err = QDMI_query_qubit_property_exists(dev, qubit, prop_index, &scope);
//         if(err)
//         {
//             std::cout << "   [sys-sage]...............Queried property doesn't exist: " << i <<"\n";
//             continue;
//         }

//         if(prop_index->type == QDMI_DOUBLE){
//             err = QDMI_query_qubit_property_d(dev, qubit, prop_index, &value);
//             if(err)
//             {
//                 std::cout << "   [sys-sage]...............Unable to query property: " << i <<"\n";
//                 continue;
//             }

//         }
//         delete prop_index;

//     }
    
// }

extern "C" void QdmiParser::setQubits(QuantumBackend *backend, QDMI_Device dev)
{
    // QDMI_Qubit qubits;
    // int err, num_qubits = 0;

    // err = QDMI_query_all_qubits(dev, &qubits);

    // if (err != QDMI_SUCCESS || qubits == NULL)
    // {
    //     std::cout << "   [sys-sage]...............Could not obtain available "
    //               << "qubits via QDMI\n";
    //     return;
    // }

    // num_qubits = backend->GetNumberofQubits();
    
    // for (int i = 0; i < num_qubits; i++)
    // {
    //     Qubit* q = new Qubit(backend, i);
        
    //     // Set coupling map
    //     int coupling_map_size; 
    //     std::vector<int> coupling_mapping;
    //     getCouplingMapping(dev, &qubits[i], coupling_mapping, coupling_map_size);
    //     q->SetCouplingMapping(coupling_mapping, coupling_map_size);

    //     // Set all the qubit properties
    //     getQubitProperties(dev, &qubits[i]);
    //     q->SetProperties(qubits[i].t1, qubits[i].t2, qubits[i].readout_error, qubits[i].readout_length);
    // }

    // free(qubits);
    // return;
}

extern "C" void QdmiParser::setGateSets(QuantumBackend *backend, QDMI_Device dev)
{
    // QDMI_Gate gates;
    // int err, num_gates;
    
    // err = QDMI_query_all_gates(dev, &gates);

    // if (err != QDMI_SUCCESS || gates == NULL)
    // {
    //     std::cout << "   [sys-sage]...............Could not obtain available "
    //               << "gates via QDMI\n";
    //     return;
    // }

    // err = QDMI_query_gateset_num(dev, &num_gates);

    // if (err != QDMI_SUCCESS || num_gates == 0)
    // {
    //     std::cout << "   [sys-sage]...............Could not obtain number of "
    //               << "available gates via QDMI\n";
    //     return;
    // }
    // else 
    // {
    //     std::cout << "   [sys-sage]...............Found "
    //               << num_gates << " supported gates.\n";
    // }

    // for (int i = 0; i < num_gates; i++)
    // {

    //     std::string name = gates[i].name;
    //     double fidelity = gates[i].fidelity;
    //     std::string unitary = gates[i].unitary;
    //     size_t gate_size = gates[i].gate_size;

    //     // Add a constructor
    //     QuantumGate *qgate = new QuantumGate(gate_size);
    //     qgate->SetGateProperties(name, fidelity, unitary);

    //     backend->addGate(qgate);
    // }
    
    
    // free(gates);

    // return;
}

extern "C" void QdmiParser::createAllQcTopo(Topology *topo)
{
    // auto quantum_backends = get_available_backends();

    // int total_quantum_backends = quantum_backends.size();

    // for (auto i = 0; i < total_quantum_backends; ++i)
    // {
    //     QuantumBackend* qc = new QuantumBackend(topo, i);
    //     createQcTopo(qc, quantum_backends[i]);
    // }

}

extern "C" Topology QdmiParser::createAllQcTopo()
{

    Topology qc_topo = Topology();
    createAllQcTopo(&qc_topo);

    return qc_topo;
}

extern "C" void QdmiParser::createQcTopo(QuantumBackend *backend, QDMI_Device dev)
{
    // backend->SetNumberofQubits(get_num_qubits(dev));
    // setQubits(backend, dev);
    // setGateSets(backend, dev);
}

extern "C" QuantumBackend QdmiParser::createQcTopo(QDMI_Device dev, int device_index, std::string device_name)
{
    QuantumBackend qc = QuantumBackend(device_index, device_name);
    createQcTopo(&qc, dev);

    return qc;
}

void QuantumBackend::RefreshTopology(std::set<int> qubit_indices)
{
    
    for (auto q : qubit_indices) {
        auto qubit = dynamic_cast<Qubit*>(GetChild(q));
        qubit->RefreshProperties();
    }
}

void Qubit::RefreshProperties()
{

    // QuantumBackend *qc = dynamic_cast<QuantumBackend*> (this->GetParent());
    // QdmiParser::refreshQubitProperties(qc->GetQDMIDevice(), this);
    
}