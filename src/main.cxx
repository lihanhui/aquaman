// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <functional>
#include <thread>
#include "config.h"

#include <aquaman/concurrent/channel_future.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/result.h>
#include <aquaman/event/generic_event.h>
#include <aquaman/schedule/default_scheduler.h>
 
 struct myclass {
  void operator()() {;}
};
class my_event: public generic_event<int>{
public:
    my_event():generic_event(){
    }
	void handle_event() override{
	    fprintf(stdout, "my_event\n");
	    get_promise()->success(1);
	}
};
int main (int argc, char *argv[]){
    std::function<void(const std::shared_ptr<future<int>> &future)> mylambda 
    	= [](const std::shared_ptr<future<int>> &future)->void {fprintf(stdout, "xxxxxxxxx\n");};
    
    fprintf(stdout, "function %lu\n", sizeof(std::shared_ptr<my_event>));
    const std::shared_ptr<my_event> event = std::make_shared<my_event>();
    std::shared_ptr<future<int>> future = event->get_future();
    future->add_listener(std::make_shared<generic_future_listener<int>>(mylambda));
    
    fprintf(stdout, "scheduler\n");
    std::shared_ptr<scheduler> sched = std::make_shared<default_scheduler>(1,2);
    fprintf(stdout, "submit_event\n");
    sched->submit_event(std::string("event"), event);
    //std::shared_ptr<event_executor> executor = std::make_shared<event_executor>();
    //executor->insert_event_handler(event);
    //executor->start();
    while(true){
	    std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    continue;
	}
    if (argc < 2)
    {
        fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            aquaman_VERSION_MAJOR,
            aquaman_VERSION_MINOR);
        fprintf(stdout,"Usage: %s number\n",argv[0]);
        return 1;
    }
    double inputValue = atof(argv[1]);
    double outputValue = sqrt(inputValue);
    fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
    return 0;
}

