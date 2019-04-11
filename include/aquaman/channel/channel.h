#ifndef AQUAMAN_CHANNEL_CHANNEL
#define AQUAMAN_CHANNEL_CHANNEL

#include <aquaman/channel/channel_invoker.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/concurrent/event_executor.h>

namespace aquman{
    namespace channel{
struct channel : public channel_invoker{
    virtual void set_pipeline(std::shared_ptr<channel_pipeline> pipeline) = 0;
    virtual std::shared_ptr<channel_pipeline> get_pipeline() = 0;
    virtual std::shared_ptr<event_executor>  get_event_executor() = 0;
};
};
};
#endif
