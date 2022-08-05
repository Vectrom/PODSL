#include "Simulation.h"
#define RAPIDJSON_NOMEMBERITERATORCLASS 
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
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
    while (_iteration == _maxIterations || !_model.getGraph().hasConsensus())
    {
        std::map<std::string, int> changes = _model.calculateOneStep();
        printInfoAboutChange(changes);
        _iteration++;
    }
}

void Simulation::setMaxIterations(uint64_t maxIterations)
{
    _maxIterations = maxIterations;
}

//#include<windows.h>
void Simulation::printInfoAboutChange(const std::map<std::string, int>& changes) const
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("step", _iteration, allocator);

    rapidjson::Value changesArray(rapidjson::kArrayType);
    for (const auto& [index, opinion] : changes)
    {
        rapidjson::Value node(rapidjson::kObjectType);
        node.AddMember("node", rapidjson::StringRef(index.c_str()), allocator)
            .AddMember("opinion", opinion, allocator);

        changesArray.PushBack(node, allocator);
    }
    document.AddMember("changes", changesArray, allocator);

    rapidjson::StringBuffer buffer;

    buffer.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << "[STEP]" << buffer.GetString();
    //OutputDebugString(buffer.GetString());
}
