#ifndef AQUAMAN_CONCURRENT_GENERIC_FUTURE_LISTENER
#define AQUAMAN_CONCURRENT_GENERIC_FUTURE_LISTENER

#include <functional>

#include "aquaman/concurrent/event_listener.h"
#include "aquaman/concurrent/future.h"

namespace aquaman
{

template<class T> class Future;

template <typename T, typename F = Future<T>> class GenericFutureListener: public EventListener{
private:
	std::function<void(const std::shared_ptr<F> future)> callable;
public:
    GenericFutureListener(std::function<void(const std::shared_ptr<F> future)> callable){
        this->callable = callable;
    }
    void operationComplete(const std::shared_ptr<F> future){
    	callable(future);
    }
};

}; // namespace aquaman
//typedef GenericFutureListener<typename T> FutureListener<typename T>;
#endif
