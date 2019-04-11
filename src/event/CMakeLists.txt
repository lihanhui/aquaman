add_library(event event.cxx)

install (TARGETS event DESTINATION lib
         EXPORT aquaman-targets)