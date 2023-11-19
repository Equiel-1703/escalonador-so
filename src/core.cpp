#include "core.h"
#include "scheduler.h"
#include <iostream>

namespace escalonador
{
    Core::Core(int core_id)
    {
        current_task_ = nullptr;
        task_in_ = -1;
        core_id_ = core_id;
    }

    void Core::setTask(Task *task)
    {
        current_task_ = task;
        task_in_ = Scheduler::getCounter();
    }

    bool Core::isTaskDone()
    {
        if (current_task_ == nullptr || (Scheduler::getCounter() - task_in_) >= current_task_->getDuration())
            return true;

        return false;
    }

    std::string Core::getCurrentTaskInfo()
    {
        if (current_task_ == nullptr)
            return "Core " + std::to_string(core_id_) + " have no task";

        return current_task_->getName() + ";" + std::to_string(task_in_) + ";" + std::to_string(Scheduler::getCounter());
    }
}