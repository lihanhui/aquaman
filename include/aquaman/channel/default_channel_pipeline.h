#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_PIPELINE
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_PIPELINE

#include <xlog/xlog.h>

#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/channel/default_channel_handler_context.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class DefaultChannelPipeline : public ChannelPipeline{
private:
    static xlog::logger logger;
private:
    std::weak_ptr<Channel> chan;
    std::shared_ptr<ChannelHandlerContext> tail;
    std::shared_ptr<ChannelHandlerContext> head;
public:
    DefaultChannelPipeline(std::shared_ptr<Channel> chan,
    						std::shared_ptr<ChannelHandlerContext> tail,
    						std::shared_ptr<ChannelHandlerContext> head	){
    	this->chan = chan;
    	this->tail = tail;
    	this->head = head;
    }
	void invoke(std::shared_ptr<Event> event) override{
		head->invoke(event);
	}
	std::shared_ptr<Channel> get_channel() override {
		return chan.lock();
	}
	void init_channel_handler_context(std::shared_ptr<ChannelHandlerContext> head,
    						std::shared_ptr<ChannelHandlerContext> tail) override;
    void add_first(std::string name, std::shared_ptr<ChannelHandlerContext> ctx) override;
    void add_last (std::string name, std::shared_ptr<ChannelHandlerContext> ctx) override;
};

}; // namespace aquaman
#endif
