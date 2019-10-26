cmake_minimum_required (VERSION 3.0)
set (CXX_STANDARD "c++17")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=${CXX_STANDARD}")

project (aquaman VERSION 1.0.0)

#set (aquaman_VERSION_MAJOR 1)
#set (aquaman_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")

find_package(PkgConfig REQUIRED)
pkg_check_modules(uv REQUIRED libuv)
message ("${uv_INCLUDE_DIRS} ${uv_LIBRARIES} ${uv_LINK_LIBRARIES}")

find_library(FMT_LIBRARY fmt HINTS /usr/local/lib)
set(EXTRA_LIBS ${EXTRA_LIBS} ${FMT_LIBRARY}) 
message("fmt-libraries - ${FMT_LIBRARY}")

find_library(XLOG_LIBRARY xlog HINTS /usr/local/lib)
set(EXTRA_LIBS ${EXTRA_LIBS} ${XLOG_LIBRARY})
message("xlog-libraries - ${XLOG_LIBRARY}")

find_package(xlog 0.9 REQUIRED)
if(xlog_FOUND)
	message("found - ${xlog_INCLUDE_DIRS} - ${xlog_LIBRARIES} - ${XLOG_LIBRARY}")
endif()
include_directories("${xlog_INCLUDE_DIRS}")

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    set(EXTRA_LIBS ${EXTRA_LIBS} pthread)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "APPLE")
    MESSAGE(STATUS "current platform: APPLE")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

message("current platform ${CMAKE_SYSTEM_NAME}" )

set_target_properties(aquaman PROPERTIES VERSION 1.0 SOVERION 1)
add_library(aquaman SHARED src/concurrent/event_executor.cxx
	        src/event/event.cxx
	        src/schedule/scheduler.cxx
	        src/channel/default_channel_pipeline.cxx
	        src/channel/channel_handler_context.cxx
	        src/math/math.cxx)
target_link_libraries(aquaman  ${EXTRA_LIBS})


add_executable(aquaman-test src/main.cxx)
target_compile_options(aquaman-test PUBLIC ${uv_CFLAGS_OTHER})
target_link_libraries(aquaman-test  ${EXTRA_LIBS} ${uv_LINK_LIBRARIES} aquaman )

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
