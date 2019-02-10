#ifndef AQUAMAN_EVENT_GENERIC_EVENT
#define AQUAMAN_EVENT_GENERIC_EVENT

#include <aquaman/concurrent/channel_promise.h>
#include <aquaman/event/result.h>
#include <aquaman/event/event.h>
#include <aquaman/event/event_handler.h>

template <typename V> class generic_event: public event_handler<V>, public event {
private:
    std::shared_ptr<channel_promise<V>> promise;
public: 
    generic_event(){
    	promise = std::make_shared<channel_promise<V>>();
    }
    std::shared_ptr<channel_promise<V>> & get_promise() override {
    	return promise;
    }
    
    bool failure(std::exception_ptr cause) override{ 
        return promise->failure(cause);
    }
};
#endif
