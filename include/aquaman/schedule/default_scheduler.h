#ifndef AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER
#define AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER

#include <xlog/xlog.h>

#include "aquaman/event/event.h"
#include "aquaman/schedule/abstract_scheduler.h"
#include "aquaman/util/util.h"
namespace aquaman
{

struct DefaultScheduler: public AbstractScheduler {
private:
    static xlog::logger logger;
public:
    DefaultScheduler(): AbstractScheduler(8, 32){
    }
    DefaultScheduler(int thread_count, int max_channel_count): AbstractScheduler(thread_count, max_channel_count) {
	}
    void submit_event(const std::string &key, std::shared_ptr<Event> ev) override
    {
        //XLOG(logger, xlog::log_level::DEBUG, "submit_event");
        int hash = Util::hash(key);
        //XLOG(logger, xlog::log_level::DEBUG, "hash");
        int index = hash % this->get_thread_count();
        std::shared_ptr<Channel> chan = this->get_channel(index);
        //XLOG(logger, xlog::log_level::DEBUG, "channel");
        chan->invoke(ev);
    }
};

}; // namespace aquaman
#endif 
