
#ifndef AQUAMAN_EVENT_EVENT_HANDLER
#define AQUAMAN_EVENT_EVENT_HANDLER

#include <aquaman/concurrent/channel_promise.h>

template <typename V> class event_handler {
public: 
    virtual std::shared_ptr<channel_promise<V>> & get_promise() = 0;
};
#endif
