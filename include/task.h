#include <string>

namespace escalonador
{

    class Task
    {
    private:
        std::string name_;
        int duration_;

    public:
        Task(std::string name, int duration);

        std::string getName();
        int getDuration();
        void print();
    };

} // namespace escalonador