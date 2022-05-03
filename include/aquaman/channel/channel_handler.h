#ifndef AQUAMAN_CHANNEL_CHANNEL_HANDLER
#define AQUAMAN_CHANNEL_CHANNEL_HANDLER

#include <memory>

#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/event/event.h"

namespace aquaman
{

struct ChannelHandlerContext;
struct ChannelHandler {
    virtual void invoke(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev) = 0;
};

}; // namespace aquaman
#endif
