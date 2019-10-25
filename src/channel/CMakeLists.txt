add_library(channel SHARED channel_handler_context.cxx default_channel_pipeline.cxx)

install (TARGETS channel DESTINATION lib
         EXPORT aquaman-targets)
