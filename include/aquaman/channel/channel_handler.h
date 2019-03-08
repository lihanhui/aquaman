#ifndef AQUAMAN_CHANNEL_CHANNEL_HANDLER
#define AQUAMAN_CHANNEL_CHANNEL_HANDLER

#include <memory>

#include <aquaman/channel/channel_handler_context.h>
#include <aquaman/event/event.h>

struct channel_handler_context;
struct channel_handler {
    virtual void invoke(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev) = 0;
};
#endif