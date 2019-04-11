add_library(schedule scheduler.cxx)

install (TARGETS schedule DESTINATION lib
         EXPORT aquaman-targets)