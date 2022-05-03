
#ifndef AQUAMAN_EVENT_EVENT_HANDLER
#define AQUAMAN_EVENT_EVENT_HANDLER

#include "aquaman/concurrent/promise.h"
#include "aquaman/concurrent/future.h"

namespace aquaman
{

template <typename V> class EventHandler {
public: 
    virtual std::shared_ptr<Future<V>>  get_future() = 0;

//protected:
//    virtual std::shared_ptr<Promise<V>>  get_promise() = 0;
};

};
#endif
