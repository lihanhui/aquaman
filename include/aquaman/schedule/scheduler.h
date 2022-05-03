#ifndef AQUAMAN_SCHEDULE_SCHEDULER
#define AQUAMAN_SCHEDULE_SCHEDULER

#include <string>

#include "aquaman/event/event.h"
namespace aquaman
{

struct Scheduler {
    virtual void submit_event(const std::string & key, std::shared_ptr<Event> ev) = 0;
};

}; // namespace aquaman
#endif 
