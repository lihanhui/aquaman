add_library(schedule SHARED scheduler.cxx)

install (TARGETS schedule DESTINATION lib
         EXPORT aquaman-targets)
