#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL

#include "aquaman/channel/channel.h"
#include "aquaman/channel/abstract_channel.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class DefaultChannel : public AbstractChannel{
public:
    DefaultChannel(std::shared_ptr<ChannelPipeline> pipeline, std::shared_ptr<EventExecutor> executor): AbstractChannel(pipeline, executor){
	
    }
};

}; // namespace aquaman
#endif
