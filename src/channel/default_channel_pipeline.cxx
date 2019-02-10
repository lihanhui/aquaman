#include <aquaman/channel/default_channel_pipeline.h>
#include <aquaman/channel/channel_handler_context.h>
#include <aquaman/channel/channel_pipeline.h>
#include <aquaman/channel/default_channel_handler_context.h>

void default_channel_pipeline::add_first(std::string name, std::shared_ptr<channel_handler_context> ctx) {
    //std::shared_ptr<channel_handler_context> ctx ;//= std::make_shared<default_channel_handler_context>(pipeline, handler);

    std::shared_ptr<channel_handler_context> next = this->head->get_next();
    ctx->set_next(next);
    ctx->set_prev(this->head);
        
	this->head->set_next(ctx);
	next->set_prev(ctx);	
}
void default_channel_pipeline::add_last (std::string name, std::shared_ptr<channel_handler_context> ctx) {
    //std::shared_ptr<channel_handler_context> ctx ;//= std::make_shared<default_channel_handler_context>(pipeline, handler);

    std::shared_ptr<channel_handler_context> prev = this->head->get_prev();
    ctx->set_next(this->tail);
    ctx->set_prev(prev);
        
	this->tail->set_prev(ctx);
	prev->set_next(ctx);
}

void default_channel_pipeline::init_channel_handler_context(std::shared_ptr<channel_handler_context> head,
    						std::shared_ptr<channel_handler_context> tail){
	this->head = head;
	this->tail = tail;
	head->set_next(this->tail);
	tail->set_prev(this->head);
}