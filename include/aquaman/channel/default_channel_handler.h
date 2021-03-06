#ifndef AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER
#define AQUAMAN_CHANNEL_DEFAULT_CHANNEL_HANDLER

#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

namespace aquaman
{

class default_channel_handler : public channel_handler{
public:
    default_channel_handler(){}
    void invoke(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev) override {
		  try{
        ev->handle_event();
      }catch(...){
        ev->failure(std::current_exception());
      }
    }
};

}; // namespace aquaman
#endif