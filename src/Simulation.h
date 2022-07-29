#pragma once
#include "ModelBase.h"

class Simulation
{
public:
    Simulation(ModelBase& model);
    void nextStep();
    void startSimulation();

private:
    void printInfoAboutChange(size_t vertexIndex, int opinion) const;
    ModelBase& _model;
};