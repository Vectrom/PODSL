#include "Simulation.h"
#define RAPIDJSON_NOMEMBERITERATORCLASS 
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
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

        if(_averageOpinion)
        {
            _averageOpinions.push_back(_model.getGraph().getAverageOpinion());
        }

        printInfoAboutChange(changes);
        _iteration++;
    }
}

void Simulation::setMaxIterations(uint64_t maxIterations)
{
    _maxIterations = maxIterations;
}

void Simulation::enableAverageOpinion()
{
    _averageOpinion = true;
}

void Simulation::disableAverageOpinion()
{
    _averageOpinion = false;
}

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

    rapidjson::Value statsArray(rapidjson::kArrayType);
    if(_averageOpinion)
    {
        rapidjson::Value averageOpinion(rapidjson::kObjectType);
        rapidjson::Value values(rapidjson::kArrayType);
        values.PushBack(_averageOpinions.back(), allocator);

        averageOpinion
            .AddMember("name", "average-opinion", allocator)
            .AddMember("values", values, allocator);
    
        statsArray.PushBack(averageOpinion, allocator);
    }
    document.AddMember("stats", statsArray, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << "[STEP]" << buffer.GetString() << std::endl;
}

void Simulation::saveResultInfoToFile(const std::string& output)
{

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("step", _iteration-1, allocator);

    rapidjson::Value statsArray(rapidjson::kArrayType);
    if (_averageOpinion)
    {
        rapidjson::Value averageOpinion(rapidjson::kObjectType);
        rapidjson::Value values(rapidjson::kArrayType);

        for(const double avg : _averageOpinions)
            values.PushBack(avg, allocator);

        averageOpinion
            .AddMember("name", "average-opinion", allocator)
            .AddMember("values", values, allocator);

        statsArray.PushBack(averageOpinion, allocator);
    }
    document.AddMember("stats", statsArray, allocator);

    std::ofstream outputStream(output);
    rapidjson::OStreamWrapper oStreamWrapper(outputStream);

    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(oStreamWrapper);
    document.Accept(writer);

}
