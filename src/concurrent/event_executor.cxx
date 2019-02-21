#include <aquaman/concurrent/future.h>

#include <chrono>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include <xlog/xlog.h>

#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

xlog::logger event_executor::logger = xlog::logger("event_executor");

void event_executor::run(){
	while(true){
	    XLOG(event_executor::logger, xlog::log_level::DEBUG, "{}", "try to dequeue event");
	    std::lock_guard<std::mutex> guard(locker);
	    if(tasks.empty()){
	    	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    	continue;
	    }
	    XLOG(event_executor::logger, xlog::log_level::DEBUG, "{}", "try to process one event");
	    std::shared_ptr<runnable> task = tasks.front();
	    tasks.pop();
		try{
		    task->run();
		    XLOG(event_executor::logger, xlog::log_level::DEBUG, "user count {}", task.use_count());
		}catch(...){
			;
		}
	}
}
