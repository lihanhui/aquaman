// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include "config.h"

#include <aquaman/concurrent/channel_future.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/result.h>
#include <aquaman/event/generic_event.h>
#include <aquaman/schedule/default_scheduler.h>
 
#include <xlog/xlog.h>

using namespace aquaman;
struct myclass {
  void operator()() {;}
};
class my_event: public generic_event<int>{
private:
    static xlog::logger logger;
public:
    my_event():generic_event(){
    }
    void handle_event() override{
        XLOG(logger, xlog::log_level::DEBUG, "{}", "my_event");
        get_promise()->success(1);
    }
    virtual ~my_event(){
        XLOG(logger, xlog::log_level::DEBUG, "{}", "my event destroied");
    }
};
xlog::logger my_event::logger = xlog::logger("my_event");

int main (int argc, char *argv[]){
    xlog::logger logger = xlog::logger("main");
    XLOG(logger, xlog::log_level::DEBUG, "{}", "this is main func of xlog test");
    
    std::function<void(const std::shared_ptr<future<int>> &future)> mylambda 
        = [&](const std::shared_ptr<future<int>> &future)->void { XLOG(logger, xlog::log_level::DEBUG, "{}", "==============xxxxxxxxx"); };
    
    XLOG(logger, xlog::log_level::DEBUG, "function {}", sizeof(std::shared_ptr<my_event>));
    std::shared_ptr<my_event> event = std::make_shared<my_event>();
    XLOG(logger, xlog::log_level::DEBUG, "typeid(event).name() = {}", typeid(event).name());
    std::shared_ptr<future<int>> future = event->get_future();
    future->add_listener(std::make_shared<generic_future_listener<int>>(mylambda));
    
    XLOG(logger, xlog::log_level::DEBUG, "{}", "scheduler");
    std::shared_ptr<scheduler> sched = std::make_shared<default_scheduler>(1,2);
    XLOG(logger, xlog::log_level::DEBUG, "{}", "submit_event");
    sched->submit_event(std::string("event"), event);
    event = std::make_shared<my_event>();
    //std::shared_ptr<event_executor> executor = std::make_shared<event_executor>();
    //executor->insert_event_handler(event);
    //executor->start();
    while(true){
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    continue;
	}
    if (argc < 2)
    {
        XLOG(logger, xlog::log_level::DEBUG, "{} Version {}.{}",
            argv[0],
            aquaman_VERSION_MAJOR,
            aquaman_VERSION_MINOR);
        XLOG(logger, xlog::log_level::DEBUG, "Usage: {} number",argv[0]);
        return 1;
    }
    double inputValue = atof(argv[1]);
    double outputValue = sqrt(inputValue);
    XLOG(logger, xlog::log_level::DEBUG, "The square root of {} is {}",
          inputValue, outputValue);
    return 0;
}

