#include "../include/task.h"
#include <string>
#include <iostream>

namespace escalonador
{
    Task::Task(std::string name, int duration)
    {
        name_.assign(name);
        duration_ = duration;
    }

    bool Task::operator<(Task const& t)
    {
        return this->duration_ < t.duration_;
    }

    std::string Task::getName()
    {
        return name_;
    }

    int Task::getDuration()
    {
        return duration_;
    }

    void Task::print() {
        std::cout << "Task name: " << name_ << " | Duration: " << duration_ << std::endl;
    }



} // namespace escalonador