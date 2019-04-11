cmake_minimum_required (VERSION 3.0)
set (CXX_STANDARD "c++17")
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

find_package(PkgConfig REQUIRED)
pkg_check_modules(uv REQUIRED libuv)
message ("${uv_INCLUDE_DIRS} ${uv_LIBRARIES} ${uv_LINK_LIBRARIES}")

find_package(xlog 0.9 REQUIRED)
if(xlog_FOUND)
    message("found - ${xlog_INCLUDE_DIRS} - ${xlog_LIBRARIES}")
endif()
include_directories("${xlog_INCLUDE_DIRS}")

add_subdirectory(src/event)
add_subdirectory(src/channel)
add_subdirectory(src/concurrent)
add_subdirectory(src/schedule)

find_library(XLOG_LIBRARY xlog HINTS /usr/local/lib)
#set(EXTRA_LIBS ${EXTRA_LIBS} event channel concurrent schedule ${XLOG_LIBRARY})
set(EXTRA_LIBS ${EXTRA_LIBS} event channel concurrent schedule ${xlog_LIBRARIES})

add_executable(aquaman-test src/main.cxx)
target_compile_options(aquaman-test PUBLIC ${uv_CFLAGS_OTHER})
target_link_libraries(aquaman-test  ${EXTRA_LIBS} ${uv_LINK_LIBRARIES})

add_library(aquaman SHARED src/main.cxx)
target_link_libraries(aquaman  ${EXTRA_LIBS})

# add the install targets
install (TARGETS aquaman DESTINATION lib
         EXPORT aquaman-targets)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/aquaman"        
         DESTINATION include)
install (EXPORT aquaman-targets
         DESTINATION lib/cmake/aquaman)

#export (TARGETS aquaman wrapper FILE aquaman-targets.cmake)
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/aquaman-config.cmake.in"
                 "${PROJECT_BINARY_DIR}/aquaman-config.cmake" @ONLY)
                 
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/aquaman-config-version.cmake.in"
                 "${PROJECT_BINARY_DIR}/aquaman-config-version.cmake" @ONLY)
                 
install (FILES 
        "${PROJECT_BINARY_DIR}/aquaman-config.cmake"
        "${PROJECT_BINARY_DIR}/aquaman-config-version.cmake"
        DESTINATION lib/cmake/aquaman)