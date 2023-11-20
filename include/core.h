#pragma once

#include "task.h"
#include <string>

namespace escalonador
{
    class Core
    {
    private:
        int core_id_;
        Task *current_task_;
        int task_in_;

    public:
        Core(int core_id);

        void setTask(Task *task);
        bool isTaskDone();
        std::string getCurrentTaskInfo();
    };
} // namespace escalonador