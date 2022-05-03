#include <xlog/xlog.h>

#include "aquaman/channel/default_channel_pipeline.h"
#include "aquaman/channel/channel_handler_context.h"
#include "aquaman/channel/channel_pipeline.h"
#include "aquaman/channel/default_channel_handler_context.h"

using namespace aquaman;

xlog::logger DefaultChannelPipeline::logger = xlog::logger("DefaultChannelPipeline");

void DefaultChannelPipeline::add_first(std::string name, std::shared_ptr<ChannelHandlerContext> ctx) {
    //std::shared_ptr<ChannelHandlerContext> ctx ;//= std::make_shared<DefaultChannelHandlerContext>(pipeline, handler);
    //XLOG(logger, xlog::log_level::DEBUG, "add_first") ;
    std::shared_ptr<ChannelHandlerContext> next = this->head->get_next();
    ctx->set_next(next);
    ctx->set_prev(this->head);
        
	this->head->set_next(ctx);
	next->set_prev(ctx);
	//XLOG(logger, xlog::log_level::DEBUG, "add_first ...after") ;	
}
void DefaultChannelPipeline::add_last (std::string name, std::shared_ptr<ChannelHandlerContext> ctx) {
    //std::shared_ptr<ChannelHandlerContext> ctx ;//= std::make_shared<DefaultChannelHandlerContext>(pipeline, handler);

    std::shared_ptr<ChannelHandlerContext> prev = this->head->get_prev();
    ctx->set_next(this->tail);
    ctx->set_prev(prev);
        
	this->tail->set_prev(ctx);
	prev->set_next(ctx);
}

void DefaultChannelPipeline::init_channel_handler_context(std::shared_ptr<ChannelHandlerContext> head,
    						std::shared_ptr<ChannelHandlerContext> tail){
    //XLOG(logger, xlog::log_level::DEBUG, "init_channel_handler_context") ;
	this->head = head;
	this->tail = tail;
	head->set_next(this->tail);
	head->set_prev(this->tail);
	tail->set_next(this->head);
	tail->set_prev(this->head);
	//XLOG(logger, xlog::log_level::DEBUG, "init_channel_handler_context ...") ;
}
