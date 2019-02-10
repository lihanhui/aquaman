#ifndef AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER
#define AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER

#include <aquaman/event/event.h>
#include <aquaman/schedule/abstract_scheduler.h>
#include <aquaman/util/util.h>

struct default_scheduler: public abstract_scheduler {

public:
    default_scheduler(): abstract_scheduler(8, 32){
    }
    default_scheduler(int thread_count, int max_channel_count): abstract_scheduler(thread_count, max_channel_count) {
	}
    void submit_event(const std::string & key, std::shared_ptr<event>  ev) override{
         fprintf(stdout, "submit_event\n");
         int hash = util::hash(key);
         fprintf(stdout, "hash\n");
         int index = hash%this->get_thread_count();
         std::shared_ptr<channel> chan = this->get_channel(index);
         fprintf(stdout, "channel \n");
         chan->invoke(ev);
    }
};

#endif 