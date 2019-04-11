#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL

#include <aquaman/channel/channel.h>
#include <aquaman/channel/abstract_channel.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

namespace aquman
{
namespace channel
{
class default_channel : public abstract_channel{
public:
    default_channel(std::shared_ptr<channel_pipeline> pipeline, std::shared_ptr<event_executor> executor): abstract_channel(pipeline, executor){
	
    }
};
}; // namespace channel
}; // namespace aquman
#endif