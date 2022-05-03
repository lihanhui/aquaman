#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER_CONTEXT
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER_CONTEXT

#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/channel/channel_handler.h"
#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/concurrent/runnable.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class DefaultChannelHandlerContext : public ChannelHandlerContext{
private:
    std::shared_ptr<ChannelHandler> handler;
	
public:
    DefaultChannelHandlerContext(
    		std::shared_ptr<ChannelPipeline> pipeline,
    		std::shared_ptr<ChannelHandler>  handler): ChannelHandlerContext(pipeline){
    	this->handler  = handler;
    	//this->set_next(nullptr);
    	//this->set_prev(nullptr);
    }

    std::shared_ptr<ChannelHandler> get_channel_handler() override{
    	return handler;
    }
};

}; // namespace aquaman
#endif
