#include "Simulation.h"
#include <iostream>
Simulation::Simulation(ModelBase& model) :
    _model(model)
{

}

void Simulation::nextStep()
{
    _model.calculateOneStep();
}

void Simulation::startSimulation()
{
    while (!_model.getGraph().hasConsensus())
    {
        _model.calculateOneStep();
    }
}

void Simulation::printInfoAboutChange(size_t vertexIndex, int opinion) const
{
    std::cout << vertexIndex << " : " << opinion << std::endl;
}
