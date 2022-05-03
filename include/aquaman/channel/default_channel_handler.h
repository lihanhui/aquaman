#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER

#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class DefaultChannelHandler : public ChannelHandler{
public:
    DefaultChannelHandler(){}
    void invoke(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev) override {
		  try{
        ev->handle_event();
      }catch(...){
        ev->failure(std::current_exception());
      }
    }
};

}; // namespace aquaman
#endif
