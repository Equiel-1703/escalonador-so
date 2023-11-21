#include "core.h"

#include <iostream>

#include "scheduler.h"

namespace escalonador
{
    int Core::cores_counter_ = 0;

    Core::Core() : core_id_(cores_counter_)
    {
        task_in_ = -1;
        cores_counter_++;
    }

    int Core::getId()
    {
        return core_id_;
    }

    void Core::setTask(std::unique_ptr<Task> task)
    {
        current_task_ = std::move(task);
        task_in_ = Scheduler::getCounter();
    }

    bool Core::isOccupied()
    {
        return current_task_ != nullptr;
    }

    Task &Core::getTask()
    {
        return *current_task_;
    }

    void Core::process()
    {
        if(current_task_ != nullptr)
            current_task_->doWork();
    }

    std::string Core::getCurrentTaskInfo()
    {
        if (current_task_ == nullptr)
            return "Core " + std::to_string(core_id_) + " have no task";

        return current_task_->getName() + ";" + std::to_string(task_in_) + ";" + std::to_string(Scheduler::getCounter());
    }
}