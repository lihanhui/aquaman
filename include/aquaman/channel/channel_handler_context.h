#ifndef AQUAMAN_CHANNEL_CHANNEL_HANDLER_CONTEXT
#define AQUAMAN_CHANNEL_CHANNEL_HANDLER_CONTEXT

#include <memory>

#include <xlog/xlog.h>

#include <aquaman/channel/channel.h>
#include <aquaman/channel/channel_invoker.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/channel/channel_handler.h>
#include <aquaman/concurrent/event_executor.h>
#include <aquaman/event/event.h>

namespace aquman
{
namespace channel
{
struct channel_pipeline;
struct channel_handler;         
struct channel;
struct channel_handler_context;

class event_wrapper: public runnable{
private:
    static xlog::logger logger;
	private:
	    std::shared_ptr<event> ev;
	    std::shared_ptr<channel_handler_context> context;
	public:
	    event_wrapper(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev );
	    void run() override ;
	protected:
	    void invoke(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev);
    public:
	    virtual ~event_wrapper(){
		    XLOG(logger, xlog::log_level::DEBUG, "event_wrapper destroied");
	    }
};
    
struct channel_handler_context: public channel_invoker, public std::enable_shared_from_this<channel_handler_context> {
private:
    static xlog::logger logger;
private:
    std::weak_ptr<channel_pipeline> pipeline;
    std::weak_ptr<channel_handler_context> prev;
    std::shared_ptr<channel_handler_context> next;

private: 
    void invoke0(std::shared_ptr<event> & ev);	
public:
    channel_handler_context(std::shared_ptr<channel_pipeline> pipeline);
    std::shared_ptr<channel_handler_context> get_prev();
    std::shared_ptr<channel_handler_context> get_next();
    
    void set_prev(std::shared_ptr<channel_handler_context> prev);
    void set_next(std::shared_ptr<channel_handler_context> next);
    
    virtual std::shared_ptr<channel> get_channel();
    virtual std::shared_ptr<event_executor> get_event_executor() ;
    virtual std::shared_ptr<channel_pipeline> get_pipeline();
    void invoke(std::shared_ptr<event> ev) override;
    
    virtual std::shared_ptr<channel_handler> get_channel_handler() = 0;


};

class head_context: public channel_handler_context{
public:
    head_context(std::shared_ptr<channel_pipeline> pipeline):channel_handler_context(pipeline){
    }     
    std::shared_ptr<channel_handler> get_channel_handler() override;   
};

class tail_context: public channel_handler_context{
public:
    tail_context(std::shared_ptr<channel_pipeline> pipeline):channel_handler_context(pipeline){
    } 
    std::shared_ptr<channel_handler> get_channel_handler() override;       
};
}; // namespace channel
}; // namespace aquman
#endif