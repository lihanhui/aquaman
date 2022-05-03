#ifndef AQUAMAN_CHANNEL_CHANNEL
#define AQUAMAN_CHANNEL_CHANNEL

#include "aquaman/channel/channel_invoker.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"

namespace aquaman
{

struct Channel : public ChannelInvoker{
    virtual void set_pipeline(std::shared_ptr<ChannelPipeline> pipeline) = 0;
    virtual std::shared_ptr<ChannelPipeline> get_pipeline() = 0;
    virtual std::shared_ptr<EventExecutor>  get_event_executor() = 0;
};

};
#endif
