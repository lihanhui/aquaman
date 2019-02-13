#include <aquaman/concurrent/future.h>

#include <chrono>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

void event_executor::run(){
	while(true){
	    fprintf(stdout, "before===============\n");
	    std::lock_guard<std::mutex> guard(locker);
	    if(tasks.empty()){
	        fprintf(stdout, "===============\n");
	    	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	    	fprintf(stdout, "sleep over===============\n");
	    	continue;
	    }
	    fprintf(stdout, "after===============\n");
	    std::shared_ptr<runnable> task = tasks.front();
	    tasks.pop();
		try{
		    task->run();
		    fprintf(stdout, "user count %d\n", task.use_count());
		}catch(...){
			;
		}
	}
}
