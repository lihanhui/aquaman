#ifndef AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER
#define AQUAMAN_SCHEDULE_DEFAULT_SCHEDULER

#include <xlog/xlog.h>

#include "aquaman/event/event.h"
#include "aquaman/schedule/abstract_scheduler.h"
#include "aquaman/util/util.h"
namespace aquaman
{

struct default_scheduler: public abstract_scheduler {
private:
    static xlog::logger logger;
public:
    default_scheduler(): abstract_scheduler(8, 32){
    }
    default_scheduler(int thread_count, int max_channel_count): abstract_scheduler(thread_count, max_channel_count) {
	}
    void submit_event(const std::string &key, std::shared_ptr<event> ev) override
    {
        XLOG(logger, xlog::log_level::DEBUG, "submit_event");
        int hash = util::hash(key);
        XLOG(logger, xlog::log_level::DEBUG, "hash");
        int index = hash % this->get_thread_count();
        std::shared_ptr<channel> chan = this->get_channel(index);
        XLOG(logger, xlog::log_level::DEBUG, "channel");
        chan->invoke(ev);
    }
};

}; // namespace aquaman
#endif 