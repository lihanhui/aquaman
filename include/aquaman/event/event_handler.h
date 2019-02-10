
#ifndef AQUAMAN_EVENT_EVENT_HANDLER
#define AQUAMAN_EVENT_EVENT_HANDLER

#include <aquaman/concurrent/promise.h>
#include <aquaman/concurrent/future.h>

template <typename V> class event_handler {
public: 
    virtual std::shared_ptr<future<V>>  get_future() = 0;

//protected:
//    virtual std::shared_ptr<promise<V>>  get_promise() = 0;
};
#endif
