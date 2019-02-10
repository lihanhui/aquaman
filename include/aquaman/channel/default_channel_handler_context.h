#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER_CONTEXT
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER_CONTEXT

#include <aquaman/channel/channel.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/channel/channel_handler.h>
#include <aquaman/channel/channel_handler_context.h>
#include <aquaman/concurrent/runnable.h>
#include <aquaman/event/event.h>

class default_channel_handler_context : public channel_handler_context{
private:
    std::shared_ptr<channel_handler> handler;
	
public:
    default_channel_handler_context(
    		std::shared_ptr<channel_pipeline> pipeline,
    		std::shared_ptr<channel_handler>  handler): channel_handler_context(pipeline){
    	this->handler  = handler;
    	this->set_next(nullptr);
    	this->set_prev(nullptr);
    }

    std::shared_ptr<channel_handler> get_channel_handler() override{
    	return handler;
    }
};
#endif