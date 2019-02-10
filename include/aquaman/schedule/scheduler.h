#ifndef AQUAMAN_SCHEDULE_SCHEDULER
#define AQUAMAN_SCHEDULE_SCHEDULER

#include <string>

#include <aquaman/event/event.h>

struct scheduler {
    virtual void submit_event(const std::string & key, std::shared_ptr<event> ev) = 0;
};

#endif 