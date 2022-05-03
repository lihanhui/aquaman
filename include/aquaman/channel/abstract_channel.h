#ifndef AQUAMAN_CHANNEL_ABSTRACT_CHANNEL
#define AQUAMAN_CHANNEL_ABSTRACT_CHANNEL

#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class AbstractChannel : public Channel{
private:
    std::shared_ptr<ChannelPipeline> pipeline;
    std::shared_ptr<EventExecutor> executor;
public:
    AbstractChannel(std::shared_ptr<ChannelPipeline> pipeline, std::shared_ptr<EventExecutor> executor){
    	this->pipeline = pipeline;
    	this->executor = executor;	
    }
    void set_pipeline(std::shared_ptr<ChannelPipeline> pipeline) override{
    	this->pipeline = pipeline;
    }
    std::shared_ptr<ChannelPipeline> get_pipeline() override{
        return pipeline;
    }
    std::shared_ptr<EventExecutor>   get_event_executor() override{
        return executor;
    }
    void invoke(std::shared_ptr<Event> ev) override {
         pipeline->invoke(ev);
    }
};

}; // namespace aquaman
#endif
