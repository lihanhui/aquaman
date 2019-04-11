#ifndef AQUAMAN_CHANNEL_ABSTRACT_CHANNEL
#define AQUAMAN_CHANNEL_ABSTRACT_CHANNEL

#include <aquaman/channel/channel.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

namespace aquaman
{

class abstract_channel : public channel{
private:
    std::shared_ptr<channel_pipeline> pipeline;
    std::shared_ptr<event_executor> executor;
public:
    abstract_channel(std::shared_ptr<channel_pipeline> pipeline, std::shared_ptr<event_executor> executor){
    	this->pipeline = pipeline;
    	this->executor = executor;	
    }
    void set_pipeline(std::shared_ptr<channel_pipeline> pipeline) override{
    	this->pipeline = pipeline;
    }
    std::shared_ptr<channel_pipeline> get_pipeline() override{
        return pipeline;
    }
    std::shared_ptr<event_executor>   get_event_executor() override{
        return executor;
    }
    void invoke(std::shared_ptr<event> ev) override {
         pipeline->invoke(ev);
    }
};

}; // namespace aquaman
#endif