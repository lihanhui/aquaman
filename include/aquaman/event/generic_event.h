#ifndef AQUAMAN_EVENT_GENERIC_EVENT
#define AQUAMAN_EVENT_GENERIC_EVENT

#include "aquaman/concurrent/channel_promise.h"
#include "aquaman/concurrent/promise.h"
#include "aquaman/concurrent/future.h"
#include "aquaman/event/result.h"
#include "aquaman/event/event.h"
#include "aquaman/event/event_handler.h"
namespace aquaman
{

template <typename V> class GenericEvent: public EventHandler<V>, public Event {
private:
    std::shared_ptr<ChannelPromise<V>> promise_;
public: 
    GenericEvent(){
    	promise_ = std::make_shared<ChannelPromise<V>>();
    }
    std::shared_ptr<Future<V>> get_future() override {
    	return promise_;
    }
    
    bool failure(std::exception_ptr cause) override{ 
        return promise_->failure(cause);
    }
    
    bool aborted() override {
    	return promise_->done();
    }
protected:
    std::shared_ptr<Promise<V>> get_promise() {
    	return promise_;
    }
};

}; // namespace aquaman
#endif
