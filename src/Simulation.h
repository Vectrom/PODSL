#pragma once
#include "ModelBase.h"
#include <type_traits>

namespace podsl
{
    class Simulation
    {
    public:
        Simulation() = default;
        void nextStep();
        void startSimulation();
        void setMaxIterations(uint64_t maxIterations);
        void enableAverageOpinion();
        void disableAverageOpinion();
        void enablePrintingInfoAboutChanges();
        void disablePrintingInfoAboutChanges();
        void enableCountingOpinions();
        void disableCountingOpinions();
        void saveResultInfoToFile(const std::string& output);
        void setModel(DerivedFromModelBase auto model)
        {
            _model = std::make_unique<decltype(model)>(std::move(model));
        }
        const Graph& getGraph() const;
        void setGraph(Graph graph);
        void readConfig(const std::string& pathToConfig);
        ModelBase& getModel() const;

    private:
        void checkRequirements() const;
        void doSingleStep();
        void printInfoAboutChange(const std::map<std::string, int>& changes) const;
        std::unique_ptr<ModelBase> _model;
        uint64_t _maxIterations = 0;
        uint64_t _iteration = 1;
        bool _averageOpinion = false;
        bool _printingInfoAboutChanges = false;
        bool _countingOpinions = false;
        std::vector<double> _averageOpinions;
        std::vector<size_t> _positiveOpinions;
        std::vector<size_t> _negativeOpinions;
        Graph _graph;
    };
}