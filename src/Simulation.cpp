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
    uint64_t iteration = 1;

    while (iteration == _maxIterations || !_model.getGraph().hasConsensus())
    {
        _model.calculateOneStep();
        iteration++;
    }
}

void Simulation::setMaxIterations(uint64_t maxIterations)
{
    _maxIterations = maxIterations;
}

void Simulation::printInfoAboutChange(size_t vertexIndex, int opinion) const
{
    std::cout << vertexIndex << " : " << opinion << std::endl;
}
