#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_PIPELINE
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_PIPELINE

#include <xlog/xlog.h>

#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/channel/default_channel_handler_context.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class default_channel_pipeline : public channel_pipeline{
private:
    static xlog::logger logger;
private:
    std::weak_ptr<channel> chan;
    std::shared_ptr<channel_handler_context> tail;
    std::shared_ptr<channel_handler_context> head;
public:
    default_channel_pipeline(std::shared_ptr<channel> chan,
    						std::shared_ptr<channel_handler_context> tail,
    						std::shared_ptr<channel_handler_context> head	){
    	this->chan = chan;
    	this->tail = tail;
    	this->head = head;
    }
	void invoke(std::shared_ptr<event> event) override{
		head->invoke(event);
	}
	std::shared_ptr<channel> get_channel() override {
		return chan.lock();
	}
	void init_channel_handler_context(std::shared_ptr<channel_handler_context> head,
    						std::shared_ptr<channel_handler_context> tail) override;
    void add_first(std::string name, std::shared_ptr<channel_handler_context> ctx) override;
    void add_last (std::string name, std::shared_ptr<channel_handler_context> ctx) override;
};

}; // namespace aquaman
#endif