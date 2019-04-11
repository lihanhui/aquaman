#ifndef AQUAMAN_CHANNEL_CHANNEL_INVOKER
#define AQUAMAN_CHANNEL_CHANNEL_INVOKER

#include <memory>

#include <aquaman/event/event.h>

namespace aquman
{
namespace channel
{
struct channel_invoker {
    virtual void invoke(std::shared_ptr<event> ev) = 0;
};
}; // namespace channel
}; // namespace aquman
#endif