/**
* @file iqm-parser.hpp
* @brief sys-sage's interface to IQM Q-Systems.
*/

#ifndef IQM_PARSER_HPP
#define IQM_PARSER_HPP

#include "Component.hpp"
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

//user calls only these functions
int parseIQM(Component* parent, string dataSourcePath, int qcId, int tsForHistory = -1);
int parseIQM(QuantumBackend* parent, string dataSourcePath, int qcId, int tsForHistory = -1, bool createTopo = true);

class IQMParser
{
public: 

    IQMParser(QuantumBackend* _qc,std::string filepath);
    int CreateQcTopo();
    int ParseDynamicData(int tsForHistory);
private:
    double t1_max, t2_max, q1_fidelity_max, readout_fidelity_max;

    json jsonData;
    QuantumBackend * backend;
};

#endif // IQM_PARSER_HPP