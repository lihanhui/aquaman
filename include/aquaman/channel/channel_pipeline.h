#ifndef AQUAMAN_CHANNEL_CHANNEL_PIPELINE
#define AQUAMAN_CHANNEL_CHANNEL_PIPELINE

#include <memory>

#include "aquaman/channel/channel_handler.h"
#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_invoker.h"

namespace aquaman
{

struct Channel;
struct ChannelPipeline : public ChannelInvoker{
    virtual std::shared_ptr<Channel> get_channel() = 0;
    virtual void init_channel_handler_context(std::shared_ptr<ChannelHandlerContext> head, std::shared_ptr<ChannelHandlerContext> tail) = 0;
    virtual void add_first(std::string name, std::shared_ptr<ChannelHandlerContext> ctx) = 0;
    virtual void add_last (std::string name, std::shared_ptr<ChannelHandlerContext> ctx) = 0;
};

}; // namespace aquaman
#endif
