#ifndef AQUAMAN_CONCURRENT_GENERIC_FUTURE_LISTENER
#define AQUAMAN_CONCURRENT_GENERIC_FUTURE_LISTENER

#include <functional>

#include <aquaman/concurrent/event_listener.h>
#include <aquaman/concurrent/future.h>

template<class T> class future;

template <typename T, typename F = future<T>> class generic_future_listener: public event_listener{
private:
	std::function<void(const std::shared_ptr<F> &future)> callable;
public:
    generic_future_listener(std::function<void(const std::shared_ptr<F> &future)> callable){
        this->callable = callable;
    }
    void operationComplete(const std::shared_ptr<F> & future){
    	callable(future);
    }
};

//typedef generic_future_listener<typename T> future_listener<typename T>;
#endif
