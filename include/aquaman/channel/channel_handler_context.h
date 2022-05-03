#ifndef AQUAMAN_CHANNEL_CHANNEL_HANDLER_CONTEXT
#define AQUAMAN_CHANNEL_CHANNEL_HANDLER_CONTEXT

#include <memory>

#include <xlog/xlog.h>

#include "aquaman/channel/channel.h"
#include "aquaman/channel/channel_invoker.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/channel/channel_handler.h"
#include "aquaman/concurrent/event_executor.h"
#include "aquaman/event/event.h"

namespace aquaman
{
struct ChannelPipeline;
struct ChannelHandler;         
struct Channel;
struct ChannelHandlerContext;

class EventWrapper: public Runnable{
private:
    static xlog::logger logger;
	private:
	    std::shared_ptr<Event> ev;
	    std::shared_ptr<ChannelHandlerContext> context;
	public:
	    EventWrapper(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev );
	    void run() override ;
	protected:
	    void invoke(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev);
    public:
	    virtual ~EventWrapper(){
		    //XLOG(logger, xlog::log_level::DEBUG, "event_wrapper destroied");
	    }
};
    
struct ChannelHandlerContext: public ChannelInvoker, public std::enable_shared_from_this<ChannelHandlerContext> {
private:
    static xlog::logger logger;
private:
    std::weak_ptr<ChannelPipeline> pipeline;
    std::weak_ptr<ChannelHandlerContext> prev;
    std::shared_ptr<ChannelHandlerContext> next;

private: 
    void invoke0(std::shared_ptr<Event> & ev);	
public:
    ChannelHandlerContext(std::shared_ptr<ChannelPipeline> pipeline);
    std::shared_ptr<ChannelHandlerContext> get_prev();
    std::shared_ptr<ChannelHandlerContext> get_next();
    
    void set_prev(std::shared_ptr<ChannelHandlerContext> prev);
    void set_next(std::shared_ptr<ChannelHandlerContext> next);
    
    virtual std::shared_ptr<Channel> get_channel();
    virtual std::shared_ptr<EventExecutor> get_event_executor() ;
    virtual std::shared_ptr<ChannelPipeline> get_pipeline();
    void invoke(std::shared_ptr<Event> ev) override;
    
    virtual std::shared_ptr<ChannelHandler> get_channel_handler() = 0;


};

class HeadContext: public ChannelHandlerContext{
public:
    HeadContext(std::shared_ptr<ChannelPipeline> pipeline):ChannelHandlerContext(pipeline){
    }     
    std::shared_ptr<ChannelHandler> get_channel_handler() override;   
};

class TailContext: public ChannelHandlerContext{
public:
    TailContext(std::shared_ptr<ChannelPipeline> pipeline):ChannelHandlerContext(pipeline){
    } 
    std::shared_ptr<ChannelHandler> get_channel_handler() override;       
};

}; // namespace aquaman
#endif
