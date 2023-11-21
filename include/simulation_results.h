#pragma once

#include <string>
#include <unordered_map>
#include <list>

namespace escalonador
{

    class SimulationResults
    {
    private:
        int total_time_;
        std::unordered_map<int, std::list<std::string>> *cores_results;

    public:
        SimulationResults();
        ~SimulationResults();

        void addCoreResult(int core_id, std::string result);
        std::list<std::string> &getCoreResults(int core_id);
        void setTotalTime(int time);
        int getTotalTime();

        std::list<std::string> *getReport();
    };

} // namespace escalonador