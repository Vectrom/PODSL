#include "Simulation.h"
#include "PODSLEnums.h"
#include "MajorityModel.h"
#include "SznajdModel.h"
#include "VoterModel.h"
#define RAPIDJSON_NOMEMBERITERATORCLASS 

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 5054)
#endif

#include <rapidjson/document.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <iostream>

using namespace podsl;

void Simulation::nextStep()
{
    if(_iteration == 1)
        checkRequirements();

    doSingleStep();
}

void Simulation::startSimulation()
{
    checkRequirements();

    while ((_iteration <= _maxIterations || _maxIterations == 0) && !_graph.hasConsensus())
    {
        doSingleStep();
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

    if (_countingOpinions)
    {

        rapidjson::Value positiveOpinions(rapidjson::kObjectType);
        rapidjson::Value positiveOpinionsValues(rapidjson::kArrayType);
        positiveOpinionsValues.PushBack(static_cast<uint64_t>(_positiveOpinions.back()), allocator);
        positiveOpinions
            .AddMember("name", "positive-opinions", allocator)
            .AddMember("values", positiveOpinionsValues, allocator);
        statsArray.PushBack(positiveOpinions, allocator);

        rapidjson::Value negativeOpinions(rapidjson::kObjectType);
        rapidjson::Value negativeOpinionsValues(rapidjson::kArrayType);
        negativeOpinionsValues.PushBack(static_cast<uint64_t>(_negativeOpinions.back()), allocator);
        negativeOpinions
            .AddMember("name", "negative-opinions", allocator)
            .AddMember("values", negativeOpinionsValues, allocator);
        statsArray.PushBack(negativeOpinions, allocator);
    }

    document.AddMember("stats", statsArray, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::cout << "[STEP]" << buffer.GetString() << std::endl;
}

void podsl::Simulation::checkRequirements() const
{
    if (_model->getModelType() == ModelType::Majority)
    {
        MajorityModel& majorityModel = dynamic_cast<MajorityModel&>(*_model);
        majorityModel.checkMajorityModelRequirements(_graph);
    }
}

void Simulation::doSingleStep()
{
    std::map<std::string, int> changes = _model->calculateOneStep(_graph);

    if (_averageOpinion)
    {
        _averageOpinions.push_back(_graph.getAverageOpinion());
    }

    if(_countingOpinions)
    {
        _positiveOpinions.push_back(_graph.getNumberOfPositiveOpinions());
        _negativeOpinions.push_back(_graph.getNumberOfNegativeOpinions());
    }

    if (_printingInfoAboutChanges)
        printInfoAboutChange(changes);
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

    if (_countingOpinions)
    {
        rapidjson::Value positiveOpinions(rapidjson::kObjectType);
        rapidjson::Value positiveOpinionsValues(rapidjson::kArrayType);

        for (const size_t opinion : _positiveOpinions)
            positiveOpinionsValues.PushBack(opinion, allocator);
        positiveOpinions
            .AddMember("name", "positive-opinions", allocator)
            .AddMember("values", positiveOpinionsValues, allocator);

        statsArray.PushBack(positiveOpinions, allocator);

        rapidjson::Value negativeOpinions(rapidjson::kObjectType);
        rapidjson::Value negativeOpinionsValues(rapidjson::kArrayType);

        for (const size_t opinion : _negativeOpinions)
            negativeOpinionsValues.PushBack(opinion, allocator);
        negativeOpinions
            .AddMember("name", "negative-opinions", allocator)
            .AddMember("values", negativeOpinionsValues, allocator);

        statsArray.PushBack(negativeOpinions, allocator);
    }
    document.AddMember("stats", statsArray, allocator);

    std::ofstream outputStream(output);
    rapidjson::OStreamWrapper oStreamWrapper(outputStream);

    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(oStreamWrapper);
    document.Accept(writer);
}

ModelBase& Simulation::getModel() const
{
    return *_model;
}

void Simulation::enablePrintingInfoAboutChanges()
{
    _printingInfoAboutChanges = true;
}

void Simulation::disablePrintingInfoAboutChanges()
{
    _printingInfoAboutChanges = false;
}

void Simulation::enableCountingOpinions()
{
    _countingOpinions = true;
}

void Simulation::disableCountingOpinions()
{
    _countingOpinions = false;
}


void Simulation::readConfig(const std::string& pathToConfig)
{
    std::ifstream inputStream(pathToConfig);
    rapidjson::IStreamWrapper iStreamWrapper(inputStream);

    rapidjson::Document document;
    document.ParseStream(iStreamWrapper);

    _graph.load(document["pathToGraph"].GetString());

    std::string modelName = document["model"].GetString();
    if (modelName == "MajorityModel")
    {
        uint64_t groupSize = document["modelParams"]["groupSize"].GetUint64();
        _model = std::make_unique<MajorityModel>(groupSize);
    }
    else if (modelName == "SznajdModel")
    {
        _model = std::make_unique<SznajdModel>();
    }
    else if (modelName == "VoterModel")
    {
        _model = std::make_unique<VoterModel>();
    }

    if (document.HasMember("maxIterations"))
        setMaxIterations(document["maxIterations"].GetUint64());

    if (document.HasMember("averageOpinion") && document["averageOpinion"].GetBool())
        enableAverageOpinion();

    if (document.HasMember("countingOpinions") && document["countingOpinions"].GetBool())
        enableCountingOpinions();

    if (document.HasMember("printInfoAboutChanges") && document["printInfoAboutChanges"].GetBool())
        enablePrintingInfoAboutChanges();
}

const Graph& Simulation::getGraph() const 
{
    return _graph;
}

void Simulation::setGraph(Graph graph)
{
    _graph = std::move(graph);
}
