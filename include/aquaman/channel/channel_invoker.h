#ifndef AQUAMAN_CHANNEL_CHANNEL_INVOKER
#define AQUAMAN_CHANNEL_CHANNEL_INVOKER

#include <memory>

#include "aquaman/event/event.h"

namespace aquaman
{

struct ChannelInvoker {
    virtual void invoke(std::shared_ptr<Event> ev) = 0;
};

}; // namespace aquaman
#endif
