#pragma once

#include <string>

namespace escalonador
{

    class Task
    {
    private:
        std::string name_;
        int duration_;
        int time_in_cpu_;

    public:
        Task(std::string name, int duration);
        bool operator<=(const Task& t) const;

        std::string getName();
        int getDuration();
        void doWork();
        bool isDone();
        void print();
    };

} // namespace escalonador