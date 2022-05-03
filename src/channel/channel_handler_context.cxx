#include <xlog/xlog.h>

#include "aquaman/channel/channel_handler_context.h"

using namespace aquaman;
xlog::logger EventWrapper::logger = xlog::logger("EventWrapper");

EventWrapper::EventWrapper(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev ){
    this->ev = ev;
    this->context = context;
}
void EventWrapper::run() {
    try {
        //XLOG(logger, xlog::log_level::DEBUG, "event_wrapper::run");
        invoke(this->context, this->ev);
    } catch(...){
    	;
   }
}
void EventWrapper::invoke(std::shared_ptr<ChannelHandlerContext> context, std::shared_ptr<Event> ev) {
    context->invoke(ev);
}  

xlog::logger ChannelHandlerContext::logger = xlog::logger("ChannelHandlerContext");      
void ChannelHandlerContext::invoke0(std::shared_ptr<Event> & ev){
    //XLOG(logger, xlog::log_level::DEBUG, "invoke0") ;
    std::shared_ptr<ChannelHandlerContext> next = get_next();
    if(next == nullptr){
        //XLOG(logger, xlog::log_level::DEBUG, "null next") ;
        return;
    }
    //XLOG(logger, xlog::log_level::DEBUG, "executor") ;
    std::shared_ptr<EventExecutor> executor = next->get_event_executor();
    if (executor->in_eventloop()) {
        next->invoke(ev);
    } else {
        executor->insert_task(std::make_shared<EventWrapper>(next, ev));
    }
}	
    
ChannelHandlerContext::ChannelHandlerContext(std::shared_ptr<ChannelPipeline> pipeline){
	this->pipeline = pipeline;
    //this->prev = nullptr;
    //this->next = nullptr;
}
std::shared_ptr<ChannelHandlerContext> ChannelHandlerContext::get_prev(){
    if(this->prev.expired()){	
    	return nullptr;
    }
	return prev.lock();
}
std::shared_ptr<ChannelHandlerContext> ChannelHandlerContext::get_next(){
	return this->next;
}
void ChannelHandlerContext::set_prev(std::shared_ptr<ChannelHandlerContext> prev){
	if(prev != nullptr){
		this->prev = prev;
	}
}
void ChannelHandlerContext::set_next(std::shared_ptr<ChannelHandlerContext> next){
	this->next = next;
}
std::shared_ptr<Channel> ChannelHandlerContext::get_channel(){
	return pipeline.lock()->get_channel();
}
std::shared_ptr<EventExecutor> ChannelHandlerContext::get_event_executor() {
	return get_channel()->get_event_executor();
}
        
std::shared_ptr<ChannelPipeline> ChannelHandlerContext::get_pipeline(){
    return pipeline.lock();
}
    
void ChannelHandlerContext::invoke(std::shared_ptr<Event> ev) {
    if( ev->aborted() ){
        return ;
    }
    //XLOG(logger, xlog::log_level::DEBUG, "invoke") ;
    std::shared_ptr<ChannelHandler> handler = get_channel_handler();
    if(handler != nullptr){
    	handler->invoke(this->shared_from_this(), ev);
    }else{
		invoke0(ev);
	}
}

std::shared_ptr<ChannelHandler> HeadContext::get_channel_handler() {
	return nullptr;
}     

std::shared_ptr<ChannelHandler> TailContext::get_channel_handler() {
    return nullptr;
}

        
