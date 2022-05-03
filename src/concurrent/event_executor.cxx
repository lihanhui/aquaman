#include <chrono>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include <xlog/xlog.h>

#include "aquaman/concurrent/future.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

using namespace aquaman;

xlog::logger EventExecutor::logger = xlog::logger("EventExecutor");

void EventExecutor::run(){
	while(true){
	    //XLOG(event_executor::logger, xlog::log_level::DEBUG, "{}", "try to dequeue event");
	    std::lock_guard<std::mutex> guard(locker);
	    if(tasks.empty()){
	    	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    	continue;
	    }
	    //XLOG(EventExecutor::logger, xlog::log_level::DEBUG, "{}", "try to process one event");
	    std::shared_ptr<Runnable> task = tasks.front();
	    tasks.pop();
		try{
		    task->run();
		    //XLOG(EventExecutor::logger, xlog::log_level::DEBUG, "user count {}", task.use_count());
		}catch(...){
			;
		}
	}
}
