cmake_minimum_required (VERSION 3.0)
set (CXX_STANDARD "c++14")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

project (aquaman)

set (aquaman_VERSION_MAJOR 1)
set (aquaman_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")

add_subdirectory(src/event)
add_subdirectory(src/channel)
add_subdirectory(src/concurrent)
add_subdirectory(src/schedule)
set(EXTRA_LIBS ${EXTRA_LIBS} event channel concurrent schedule)

add_executable(aquaman-test src/main.cxx)
target_link_libraries(aquaman-test  ${EXTRA_LIBS})

add_library(aquaman SHARED src/main.cxx)
target_link_libraries(aquaman  ${EXTRA_LIBS})

# add the install targets
install (TARGETS aquaman DESTINATION lib)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/aquaman"        
         DESTINATION include)
