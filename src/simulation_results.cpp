#include "simulation_results.h"

namespace escalonador
{
    SimulationResults::SimulationResults()
    : cores_results_(new std::unordered_map<int, std::list<std::string>>())
    {
        total_time_ = -1;
    }

    void SimulationResults::addCoreResult(int core_id, std::string result)
    {
        // Se não existe a chave, ela é criada
        if (cores_results_->find(core_id) == cores_results_->end())
            cores_results_->insert(std::make_pair(core_id, std::list<std::string>()));

        cores_results_->at(core_id).push_back(result);
    }

    std::list<std::string> &SimulationResults::getCoreResults(int core_id)
    {
        return cores_results_->at(core_id);
    }

    void SimulationResults::setTotalTime(int time)
    {
        total_time_ = time;
    }

    int SimulationResults::getTotalTime()
    {
        return total_time_;
    }

    std::unique_ptr<std::list<std::string>> SimulationResults::getReport()
    {
        auto report = new std::list<std::string>();

        // Como temos que percorrer cada lista de cada chave, esse laço é O(k * n)
        for (auto it : *cores_results_)
        {
            report->push_back("Tarefas realizadas pelo nucleo [" + std::to_string(it.first) + "]:\n");
            for (auto it_list : it.second)
            {
                report->push_back(it_list + "\n");
            }
            report->push_back("\n");
        }

        report->push_back("Tempo total de processamento: " + std::to_string(total_time_));

        return std::unique_ptr<std::list<std::string>>(report);
    }

} // namespace escalonador