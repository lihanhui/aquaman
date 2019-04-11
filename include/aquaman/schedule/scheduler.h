#ifndef AQUAMAN_SCHEDULE_SCHEDULER
#define AQUAMAN_SCHEDULE_SCHEDULER

#include <string>

#include <aquaman/event/event.h>
namespace aquman
{
namespace schedule
{
struct scheduler {
    virtual void submit_event(const std::string & key, std::shared_ptr<event> ev) = 0;
};
}; // namespace schedule
}; // namespace aquman
#endif 