add_library(mymath SHARED math.cxx)
install (TARGETS mymath DESTINATION bin)
install (FILES ${PROJECT_SOURCE_DIR}/include/math/mymath.h DESTINATION include)

