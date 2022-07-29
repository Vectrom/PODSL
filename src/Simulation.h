#pragma once
#include "ModelBase.h"

class Simulation
{
public:
    Simulation(ModelBase& model);
    void nextStep();
    void startSimulation();
    void setMaxIterations(uint64_t maxIterations);

private:
    void printInfoAboutChange(size_t vertexIndex, int opinion) const;
    ModelBase& _model;
    uint64_t _maxIterations;
};