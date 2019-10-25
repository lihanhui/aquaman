add_library(event SHARED event.cxx)

install (TARGETS event DESTINATION lib
         EXPORT aquaman-targets)
