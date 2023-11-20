#include "core.h"

#include <iostream>

#include "scheduler.h"

namespace escalonador
{
    Core::Core(int core_id)
    {
        current_task_ = nullptr;
        task_in_ = -1;
        core_id_ = core_id;
    }

    int Core::getId()
    {
        return core_id_;
    }

    void Core::setTask(Task *task)
    {
        if (current_task_ != nullptr)
            delete current_task_;

        current_task_ = task;
        task_in_ = Scheduler::getCounter();
    }

    bool Core::isOccupied()
    {
        return current_task_ != nullptr;
    }

    Task * Core::getTask()
    {
        return current_task_;
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