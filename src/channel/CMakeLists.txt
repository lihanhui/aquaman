add_library(channel channel_handler_context.cxx default_channel_pipeline.cxx)

install (TARGETS channel DESTINATION lib
         EXPORT aquaman-targets)