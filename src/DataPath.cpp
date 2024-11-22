#include "DataPath.hpp"

#include <cstdint>
#include <algorithm>

void Relation::SetType(int _type) {type = _type;}
int Relation::GetType(){ return type;}
void Relation::SetId(int _id) {id = _id;}
int Relation::GetId(){ return id;}
void Relation::SetName(std::string _name) { name = _name;}
std::string Relation::GetName() {return name;}

DataPath* NewDataPath(Component* _source, Component* _target, int _oriented, int _type){
    DataPath *dp = new DataPath(_source, _target, _oriented, _type, -1, -1);
    return dp;
}
DataPath* NewDataPath(Component* _source, Component* _target, int _oriented, double _bw, double _latency){
    DataPath *dp = new DataPath(_source,_target,_oriented,SYS_SAGE_DATAPATH_TYPE_NONE,_bw,_latency);
    return dp;
}
DataPath* NewDataPath(Component* _source, Component* _target, int _oriented, int _type, double _bw, double _latency)
{
    DataPath* dp = new DataPath(_source, _target, _oriented, _type, _bw, _latency);
    return dp;
}

Component * DataPath::GetSource() {return source;}
Component * DataPath::GetTarget() {return target;}
double DataPath::GetBandwidth() {return bw;}
void DataPath::SetBandwidth(double _bandwidth) { bw = _bandwidth;}
double DataPath::GetLatency() {return latency;}
void DataPath::SetLatency(double _latency) { latency = _latency; }
int DataPath::GetDataPathType() {return dp_type;}
int DataPath::GetOrientation() {return oriented;}

void DataPath::UpdateSource(Component * _new_source)
{
    if(oriented == SYS_SAGE_DATAPATH_BIDIRECTIONAL)
    {
        std::vector<DataPath*>* source_dp_outgoing = source->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        std::vector<DataPath*>* source_dp_incoming = source->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);

        source_dp_outgoing->erase(std::remove(source_dp_outgoing->begin(), source_dp_outgoing->end(), this), source_dp_outgoing->end());
        source_dp_incoming->erase(std::remove(source_dp_incoming->begin(), source_dp_incoming->end(), this), source_dp_incoming->end());

        _new_source->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
        _new_source->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);

    }
    else if(oriented == SYS_SAGE_DATAPATH_ORIENTED)
    {
        std::vector<DataPath*>* source_dp_outgoing = source->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        source_dp_outgoing->erase(std::remove(source_dp_outgoing->begin(), source_dp_outgoing->end(), this), source_dp_outgoing->end());

        _new_source->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
    }

    source = _new_source;

}

void DataPath::UpdateTarget(Component * _new_target)
{
    if(oriented == SYS_SAGE_DATAPATH_BIDIRECTIONAL)
    {
        std::vector<DataPath*>* target_dp_outgoing = target->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        std::vector<DataPath*>* target_dp_incoming = target->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);

        target_dp_outgoing->erase(std::remove(target_dp_outgoing->begin(), target_dp_outgoing->end(), this), target_dp_outgoing->end());
        target_dp_incoming->erase(std::remove(target_dp_incoming->begin(), target_dp_incoming->end(), this), target_dp_incoming->end());

        _new_target->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
        _new_target->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);

    }
    else if(oriented == SYS_SAGE_DATAPATH_ORIENTED)
    {
        std::vector<DataPath*>* target_dp_incoming = target->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);
        target_dp_incoming->erase(std::remove(target_dp_incoming->begin(), target_dp_incoming->end(), this), target_dp_incoming->end());
        
        _new_target->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);
    }

    target = _new_target;

}

DataPath::DataPath(Component* _source, Component* _target, int _oriented, int _type): DataPath(_source, _target, _oriented, _type, -1, -1) {}
DataPath::DataPath(Component* _source, Component* _target, int _oriented, double _bw, double _latency): DataPath(_source, _target, _oriented, SYS_SAGE_DATAPATH_TYPE_NONE, _bw, _latency) {}
DataPath::DataPath(Component* _source, Component* _target, int _oriented, int _type, double _bw, double _latency): source(_source), target(_target), oriented(_oriented), bw(_bw), latency(_latency)
{
    type = _type;
    if(_oriented == SYS_SAGE_DATAPATH_BIDIRECTIONAL)
    {
        _source->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
        _target->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
        _source->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);
        _target->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);
    }
    else if(_oriented == SYS_SAGE_DATAPATH_ORIENTED)
    {
        _source->AddDataPath(this, SYS_SAGE_DATAPATH_OUTGOING);
        _target->AddDataPath(this, SYS_SAGE_DATAPATH_INCOMING);
    }
    else
    {
        delete this;
        return;//error
    }
}

void DataPath::DeleteDataPath()
{
    if(oriented == SYS_SAGE_DATAPATH_BIDIRECTIONAL)
    {
        std::vector<DataPath*>* source_dp_outgoing = source->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        std::vector<DataPath*>* source_dp_incoming = source->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);
        std::vector<DataPath*>* target_dp_outgoing = target->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        std::vector<DataPath*>* target_dp_incoming = target->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);

        source_dp_outgoing->erase(std::remove(source_dp_outgoing->begin(), source_dp_outgoing->end(), this), source_dp_outgoing->end());
        target_dp_outgoing->erase(std::remove(target_dp_outgoing->begin(), target_dp_outgoing->end(), this), target_dp_outgoing->end());
        source_dp_incoming->erase(std::remove(source_dp_incoming->begin(), source_dp_incoming->end(), this), source_dp_incoming->end());
        target_dp_incoming->erase(std::remove(target_dp_incoming->begin(), target_dp_incoming->end(), this), target_dp_incoming->end());
    }
    else if(oriented == SYS_SAGE_DATAPATH_ORIENTED)
    {
        std::vector<DataPath*>* source_dp_outgoing = source->GetDataPaths(SYS_SAGE_DATAPATH_OUTGOING);
        std::vector<DataPath*>* target_dp_incoming = target->GetDataPaths(SYS_SAGE_DATAPATH_INCOMING);
        source_dp_outgoing->erase(std::remove(source_dp_outgoing->begin(), source_dp_outgoing->end(), this), source_dp_outgoing->end());
        target_dp_incoming->erase(std::remove(target_dp_incoming->begin(), target_dp_incoming->end(), this), target_dp_incoming->end());
    }
    delete this;
}


void DataPath::Print()
{
    cout << "DataPath src: (" << source->GetComponentTypeStr() << ") id " << source->GetId() << ", target: (" << target->GetComponentTypeStr() << ") id " << target->GetId() << " - bw: " << bw << ", latency: " << latency;
    if(!attrib.empty())
    {
        cout << " - attrib: ";
        for (const auto& n : attrib) {
            uint64_t* val = (uint64_t*)n.second;
            std::cout << n.first << " = " << *val << "; ";
        }
    }
    cout << endl;
}

void DataPath::DeleteRelation()
{
    DeleteDataPath();
}

QuantumGate::QuantumGate()
{
    gate_size = 1;
    type = SYS_SAGE_1Q_QUANTUM_GATE;
}

QuantumGate::QuantumGate(size_t _gate_size) : gate_size(_gate_size){}

QuantumGate::QuantumGate(size_t _gate_size, std::string _name, double _fidelity, std::string _unitary)
: gate_size(_gate_size), fidelity(_fidelity), unitary(_unitary){ name =_name ;}

QuantumGate::QuantumGate(size_t _gate_size, const std::vector<Qubit *> & _qubits)
: gate_size(_gate_size), qubits(_qubits) {}

QuantumGate::QuantumGate(size_t _gate_size, const std::vector<Qubit *> & _qubits, std::string _name, double _fidelity, std::string _unitary)
: gate_size(_gate_size), qubits(_qubits), fidelity(_fidelity), unitary(_unitary) { name =_name ;}

void QuantumGate::SetGateProperties(std::string _name, double _fidelity, std::string _unitary)
{
    name = _name;
    fidelity = _fidelity;
    unitary = _unitary;
    SetType();
}


void QuantumGate::SetType()
{
    if(gate_size == 1)
    {
        if(name == "id") type = SYS_SAGE_QUANTUMGATE_TYPE_ID;
        else if(name == "rz") type = SYS_SAGE_QUANTUMGATE_TYPE_RZ;
        else if(name == "sx") type = SYS_SAGE_QUANTUMGATE_TYPE_SX;
        else if(name == "x") type = SYS_SAGE_QUANTUMGATE_TYPE_X;
        else type = SYS_SAGE_QUANTUMGATE_TYPE_UNKNOWN;
    }

    else if(gate_size == 2)
    {
        if(name == "cx") type = SYS_SAGE_QUANTUMGATE_TYPE_CNOT;
        else type = SYS_SAGE_QUANTUMGATE_TYPE_UNKNOWN;
    }

    else if(gate_size > 2)
    {
        if(name == "toffoli") type = SYS_SAGE_QUANTUMGATE_TYPE_TOFFOLI;
        else type = SYS_SAGE_QUANTUMGATE_TYPE_UNKNOWN;
    }

    else
    {
        type = SYS_SAGE_QUANTUMGATE_TYPE_UNKNOWN;
    }

}

int QuantumGate::GetType()
{
    return type;
}

double QuantumGate::GetFidelity() const
{
    return fidelity;
}

size_t QuantumGate::GetGateSize() const
{
    return gate_size;
}

std::string QuantumGate::GetUnitary() const
{
    return unitary;
}

std::string QuantumGate::GetName()
{
    return name;
}

void QuantumGate::Print()
{
}

void QuantumGate::DeleteRelation()
{
}
