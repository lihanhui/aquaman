add_library(concurrent SHARED  
                       event_executor.cxx)
install (TARGETS concurrent DESTINATION lib
         EXPORT aquaman-targets)
