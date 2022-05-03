#ifndef AQUAMAN_SCHEDULE_ABSTRACT_SCHEDULER
#define AQUAMAN_SCHEDULE_ABSTRACT_SCHEDULER

#include <memory>

#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/channel/default_channel.h"
#include "aquaman/channel/default_channel_handler_context.h"
#include "aquaman/channel/default_channel_handler.h"
#include "aquaman/channel/default_channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"
#include "aquaman/schedule/scheduler.h"
namespace aquaman
{

struct AbstractScheduler: public Scheduler {
private:
    int thread_count;
    int max_channel_count;
	std::vector<std::shared_ptr<EventExecutor>> executors;
	std::vector<std::shared_ptr<Channel>> chans;

  public:
    AbstractScheduler(): AbstractScheduler(8, 32){
    
    }
    AbstractScheduler(int thread_count, int max_channel_count) {
		this->thread_count = thread_count;
		this->max_channel_count = max_channel_count;

		this->executors = std::vector<std::shared_ptr<EventExecutor>>();
		for(int i = 0; i < this->thread_count; i++){
			std::shared_ptr<EventExecutor> executor = std::make_shared<EventExecutor>();
			executor->start();
		    this->executors.push_back(executor);
		}
		for(int i = 0; i < this->max_channel_count; i++) {
			std::shared_ptr<EventExecutor> executor = this->executors[i % this->thread_count];
			std::shared_ptr<Channel> chan = std::make_shared<DefaultChannel>(nullptr, executor);

			std::shared_ptr<ChannelPipeline> pipeline = std::make_shared<DefaultChannelPipeline>(chan, nullptr, nullptr);
			std::shared_ptr<ChannelHandlerContext> head = std::make_shared<HeadContext>(pipeline);
			std::shared_ptr<ChannelHandlerContext> tail = std::make_shared<TailContext>(pipeline);
			pipeline->init_channel_handler_context(head, tail);
			
			chan->set_pipeline(pipeline);
			std::shared_ptr<ChannelHandler> handler = std::make_shared<DefaultChannelHandler>();
			pipeline->add_first("default", std::make_shared<DefaultChannelHandlerContext>(pipeline, handler));

			chans.push_back(chan);
		}
	}
	std::shared_ptr<Channel> get_channel(int index)
	{
		return chans[index];
	}
protected:
	int get_thread_count(){
	    return this->thread_count;
	}
};

}; // namespace aquaman
#endif 
