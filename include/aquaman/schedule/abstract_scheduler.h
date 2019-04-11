#ifndef AQUAMAN_SCHEDULE_ABSTRACT_SCHEDULER
#define AQUAMAN_SCHEDULE_ABSTRACT_SCHEDULER

#include <memory>

#include <aquaman/channel/channel_handler_context.h>
#include <aquaman/channel/default_channel.h>
#include <aquaman/channel/default_channel_handler_context.h>
#include <aquaman/channel/default_channel_handler.h>
#include <aquaman/channel/default_channel_pipeline.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>
#include <aquaman/schedule/scheduler.h>
namespace aquman
{
namespace schedule
{
struct abstract_scheduler: public scheduler {
private:
    int thread_count;
    int max_channel_count;
    std::vector<std::shared_ptr<event_executor>> executors;
    std::vector<std::shared_ptr<channel>> chans;
public:
    abstract_scheduler(): abstract_scheduler(8, 32){
    
    }
    abstract_scheduler(int thread_count, int max_channel_count) {
		this->thread_count = thread_count;
		this->max_channel_count = max_channel_count;

		this->executors = std::vector<std::shared_ptr<event_executor>>();
		for(int i = 0; i < this->thread_count; i++){
			std::shared_ptr<event_executor> executor = std::make_shared<event_executor>();
			executor->start();
		    this->executors.push_back(executor);
		}
		for(int i = 0; i < this->max_channel_count; i++) {
		    std::shared_ptr<event_executor> executor = this->executors[i % this->thread_count];
			std::shared_ptr<channel> chan = std::make_shared<default_channel>(nullptr, executor);
			
			std::shared_ptr<channel_pipeline> pipeline = std::make_shared<default_channel_pipeline>(chan, nullptr, nullptr);
			std::shared_ptr<channel_handler_context> head = std::make_shared<head_context>(pipeline);
			std::shared_ptr<channel_handler_context> tail = std::make_shared<tail_context>(pipeline);
			pipeline->init_channel_handler_context(head, tail);
			
			chan->set_pipeline(pipeline);
			std::shared_ptr<channel_handler> handler = std::make_shared<default_channel_handler>();
			pipeline->add_first("default", std::make_shared<default_channel_handler_context>(pipeline, handler));
			
			chans.push_back(chan);
		}
	}
	std::shared_ptr<channel> get_channel(int index){
		return chans[index];
	}
protected:
	int get_thread_count(){
	    return this->thread_count;
	}
};
}; // namespace schedule
}; // namespace aquman
#endif 