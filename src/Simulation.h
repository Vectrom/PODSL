#pragma once
#include "ModelBase.h"

class Simulation
{
public:
    Simulation(ModelBase& model);
    Simulation(const std::string& pathToConfig);
    void nextStep();
    void startSimulation();
    void setMaxIterations(uint64_t maxIterations);
    void enableAverageOpinion();
    void disableAverageOpinion();
    void saveResultInfoToFile(const std::string& output);
    ModelBase& getModel() const;

private:
    void printInfoAboutChange(const std::map<std::string, int>& changes) const;
    std::shared_ptr<ModelBase> _model;
    uint64_t _maxIterations;
    uint64_t _iteration = 1;
    bool _averageOpinion = false;
    std::vector<double> _averageOpinions;
};