#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER

#include <aquaman/channel/channel.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

class default_channel_handler : public channel_handler{
public:
    default_channel_handler(){}
    void invoke(channel_handler_context * context, std::shared_ptr<event> ev) override {
		ev->handle_event();
    }
};
#endif