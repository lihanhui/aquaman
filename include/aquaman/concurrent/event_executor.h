#ifndef AQUAMAN_CONCURRENT_EVENT_EXECUTOR
#define AQUAMAN_CONCURRENT_EVENT_EXECUTOR

#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include <xlog/xlog.h>

#include <aquaman/concurrent/runnable.h>
namespace aquman
{
namespace concurrent
{
class event_executor {
private:
    static xlog::logger logger;
private:
    std::mutex locker; 
    std::queue<std::shared_ptr<runnable>> tasks;
    std::thread::id this_id;
    std::thread thrd;
    
public:
    
    void insert_task(std::shared_ptr<runnable> task) {
        std::lock_guard<std::mutex> guard(locker);
        tasks.push(task);
    }
    bool in_eventloop(){
    	return this_id == std::this_thread::get_id();
    }
    void run();
    void start(){
        std::packaged_task<void(event_executor *)> task(&event_executor::run0);
    	std::future<void> result = task.get_future();
 
    	thrd = std::thread (std::move(task), this);
    	//ret = task_td.get_future()
        //*/
	} 
	
protected:    
    void run0(){
    	this_id = std::this_thread::get_id();
    	run();
    }
   
};
}; // namespace concurrent
}; // namespace aquman
#endif 
