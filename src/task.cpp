#include "task.h"

#include <string>
#include <iostream>

namespace escalonador
{
    Task::Task(std::string name, int duration)
    {
        name_.assign(name);
        duration_ = duration;
        time_in_cpu_ = 0;
    }

    Task::Task(const Task& t)
    {
        this->duration_ = t.duration_;
        this->name_ = std::move(t.name_);
        this->time_in_cpu_ = t.time_in_cpu_;
    }

    bool Task::operator<=(const Task &t) const
    {
        return this->duration_ <= t.duration_;
    }

    std::string Task::getName()
    {
        return name_;
    }

    int Task::getDuration()
    {
        return duration_;
    }

    void Task::doWork()
    {
        ++time_in_cpu_;
    }

    bool Task::isDone()
    {
        return time_in_cpu_ >= duration_;
    }

    void Task::print()
    {
        std::cout << "Task name: " << name_ << " | Duration: " << duration_ << std::endl;
    }

} // namespace escalonador