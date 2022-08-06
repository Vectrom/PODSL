#pragma once
#include "ModelBase.h"

class Simulation
{
public:
    Simulation(ModelBase& model);
    void nextStep();
    void startSimulation();
    void setMaxIterations(uint64_t maxIterations);
    void enableAverageOpinion();
    void disableAverageOpinion();

private:
    void printInfoAboutChange(const std::map<std::string, int>& changes) const;
    ModelBase& _model;
    uint64_t _maxIterations;
    uint64_t _iteration = 1;
    bool _averageOpinion = false;
};