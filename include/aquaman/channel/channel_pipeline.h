#ifndef AQUAMAN_CHANNEL_CHANNEL_PIPELINE
#define AQUAMAN_CHANNEL_CHANNEL_PIPELINE

#include <memory>

#include <aquaman/channel/channel_handler.h>
#include <aquaman/channel/channel_handler_context.h>
#include <aquaman/channel/channel.h>
#include <aquaman/channel/channel_invoker.h>

namespace aquman
{
namespace channel
{
struct channel;
struct channel_pipeline : public channel_invoker{
    virtual std::shared_ptr<channel> get_channel() = 0;
    virtual void init_channel_handler_context(std::shared_ptr<channel_handler_context> head, std::shared_ptr<channel_handler_context> tail) = 0;
    virtual void add_first(std::string name, std::shared_ptr<channel_handler_context> ctx) = 0;
    virtual void add_last (std::string name, std::shared_ptr<channel_handler_context> ctx) = 0;
};
}; // namespace channel
}; // namespace aquman
#endif