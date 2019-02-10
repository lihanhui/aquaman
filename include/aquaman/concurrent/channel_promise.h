#ifndef AQUAMAN_CONCURRENT_CHANNEL_PROMISE
#define AQUAMAN_CONCURRENT_CHANNEL_PROMISE

#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include <aquaman/concurrent/channel_future.h>
#include <aquaman/concurrent/generic_future_listener.h>
#include <aquaman/concurrent/promise.h>
#include <aquaman/event/result.h>

template <typename T> class channel_promise: public channel_future<T>, public promise<T> {
private:
    std::mutex locker;
    std::atomic_bool done;
    std::atomic_bool succeeded;
    std::exception_ptr ex;
    
    std::list<std::shared_ptr<generic_future_listener<T>>> listeners;
    
private:
    std::mutex& get_locker(){
    	return locker;
    	
    }
    bool get_done(){
    	return done.load();
    }
    void set_done(){
    	return done.store(true);
    }
    std::list<std::shared_ptr<generic_future_listener<T>>> & get_listeners(){
    	return listeners;
    }    
public:
    channel_promise(){
    	done      = false;
    	succeeded = false;
    	ex        = nullptr;
    }
    virtual ~channel_promise(){
    }
    
    ///////////////////////
    bool success() override { return succeeded; }
    std::exception_ptr cause() override { return ex; }
    
    void add_listener(std::shared_ptr<generic_future_listener<T>> listener) override {
        std::lock_guard<std::mutex> guard(locker);
        if(get_done()){
        	listener->operationComplete(this->shared_from_this());
        }
        listeners.push_back(listener);
    }
    
    T get() override{ 
        return this->get_future().get();
    }
    
    //////////////////////
    bool success(T v) override{
        std::lock_guard<std::mutex> guard(locker);
        if(done) return false;
         
        this->set_value(v);
        this->done = true;
        this->succeeded = true;
    	for(std::shared_ptr<generic_future_listener<T>> &listener: listeners){
    		listener->operationComplete(this->shared_from_this());
    	}
        return true;
    }
    bool try_success(T v) override{
    	std::lock_guard<std::mutex> guard(locker);
    	if(done) return false;
    	
    	this->set_value(v);
    	this->done = true;
    	this->succeeded = true;
    	
    	for(std::shared_ptr<generic_future_listener<T>> &listener: listeners){
    		listener->operationComplete(this->shared_from_this());
    	}
        return true;
    }
    
    bool failure(std::exception_ptr cause) override{
    	std::lock_guard<std::mutex> guard(locker);
    	if(done) return false;
    	
    	this->done = true;
    	this->succeeded = false;
    	this->set_exception(cause);
    	this->ex = cause;
    	
    	for(std::shared_ptr<generic_future_listener<T>> &listener: listeners){
    		listener->operationComplete(this->shared_from_this());
    	}
        return true;
    }
    
    bool try_failure(std::exception_ptr cause) override{
    	std::lock_guard<std::mutex> guard(locker);
    	if(done) return false;
    	
    	this->done = true;
    	this->succeeded = false;
    	this->set_exception(cause);
    	this->ex = cause;
    	
    	for(std::shared_ptr<generic_future_listener<T>> &listener: listeners){
    		listener->operationComplete(this->shared_from_this());
    	}
        return true;
    }
    
};
#endif