#include <xlog/xlog.h>

#include <aquaman/channel/channel_handler_context.h>

xlog::logger event_wrapper::logger = xlog::logger("event_wrapper");

event_wrapper::event_wrapper(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev ){
    this->ev = ev;
    this->context = context;
}
void event_wrapper::run() {
    try {
        invoke(this->context, this->ev);
    } catch(...){
    	;
   }
}
void event_wrapper::invoke(std::shared_ptr<channel_handler_context> context, std::shared_ptr<event> ev) {
    context->invoke(ev);
}  

xlog::logger channel_handler_context::logger = xlog::logger("channel_handler_context");      
void channel_handler_context::invoke0(std::shared_ptr<event> & ev){
    XLOG(logger, xlog::log_level::DEBUG, "invoke0") ;
    std::shared_ptr<channel_handler_context> next = get_next();
    if(next == nullptr){
        XLOG(logger, xlog::log_level::DEBUG, "null next") ;
        return;
    }
    XLOG(logger, xlog::log_level::DEBUG, "executor") ;
    std::shared_ptr<event_executor> executor = next->get_event_executor();
    if (executor->in_eventloop()) {
        next->invoke(ev);
    } else {
        executor->insert_task(std::make_shared<event_wrapper>(next, ev));
    }
}	
    
channel_handler_context::channel_handler_context(std::shared_ptr<channel_pipeline> pipeline){
	this->pipeline = pipeline;
    //this->prev = nullptr;
    //this->next = nullptr;
}
std::shared_ptr<channel_handler_context> channel_handler_context::get_prev(){
    if(this->prev.expired()){	
    	return nullptr;
    }
	return prev.lock();
}
std::shared_ptr<channel_handler_context> channel_handler_context::get_next(){
	return this->next;
}
void channel_handler_context::set_prev(std::shared_ptr<channel_handler_context> prev){
	if(prev != nullptr){
		this->prev = prev;
	}
}
void channel_handler_context::set_next(std::shared_ptr<channel_handler_context> next){
	this->next = next;
}
std::shared_ptr<channel> channel_handler_context::get_channel(){
	return pipeline.lock()->get_channel();
}
std::shared_ptr<event_executor> channel_handler_context::get_event_executor() {
	return get_channel()->get_event_executor();
}
        
std::shared_ptr<channel_pipeline> channel_handler_context::get_pipeline(){
    return pipeline.lock();
}
    
void channel_handler_context::invoke(std::shared_ptr<event> ev) {
    if( ev->aborted() ){
        return ;
    }
    XLOG(logger, xlog::log_level::DEBUG, "invoke") ;
    std::shared_ptr<channel_handler> handler = get_channel_handler();
    if(handler != nullptr){
    	handler->invoke(this, ev);
    }else{
		invoke0(ev);
	}
}

std::shared_ptr<channel_handler> head_context::get_channel_handler() {
	return nullptr;
}     

std::shared_ptr<channel_handler> tail_context::get_channel_handler() {
    return nullptr;
}

        
