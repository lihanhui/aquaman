add_library(mymath math.cxx)
install (TARGETS mymath DESTINATION bin)
install (FILES ${PROJECT_SOURCE_DIR}/include/math/mymath.h DESTINATION include)

