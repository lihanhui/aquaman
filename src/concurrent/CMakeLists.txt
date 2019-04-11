add_library(concurrent  
                       event_executor.cxx)
install (TARGETS concurrent DESTINATION lib
         EXPORT aquaman-targets)
