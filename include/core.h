#pragma once

#include <string>
#include <memory>

#include "task.h"

namespace escalonador
{
    class Core
    {
    private:
        const int core_id_;
        std::unique_ptr<Task> current_task_;
        int task_in_;
        static int cores_counter_;

    public:
        Core();

        int getId();
        void setTask(std::unique_ptr<Task> task);
        bool isOccupied();
        Task &getTask();
        void process();
        std::string getCurrentTaskInfo();
    };
} // namespace escalonador