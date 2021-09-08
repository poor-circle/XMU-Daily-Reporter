cmake_minimum_required(VERSION 3.8.0)

project(daily_reporter VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(static_link true) # set if enable static link

#set include path
include_directories(include)
#set cpp file path
aux_source_directory(src SRC_LIST)
add_executable(daily_reporter ${SRC_LIST})

#add third-party library: mailio, OpenSSL, fmt, nlohammn_json and httplib
find_path(MAILIO_INCLUDE_DIR "mailio/smtp.hpp")
if(MSVC)
    find_library(MAILIO_LIBRARY "mailio")
else(MSVC)
    find_library(MAILIO_LIBRARY "libmailio")
endif()
target_include_directories(daily_reporter PRIVATE ${MAILIO_INCLUDE_DIR})
target_link_libraries(daily_reporter PRIVATE ${MAILIO_LIBRARY})

find_package(OpenSSL REQUIRED)
    target_link_libraries(daily_reporter PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(fmt CONFIG REQUIRED)
    target_link_libraries(daily_reporter PRIVATE fmt::fmt-header-only)

find_package(nlohmann_json CONFIG REQUIRED)
    target_link_libraries(daily_reporter PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
    target_include_directories(daily_reporter PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#config about static link
if(static_link)
    if(MSVC)
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    else(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
        set(OpenSSL_USE_STATIC_LIBS ON)
        set(OpenSSL_USE_STATIC_RUNTIME ON)
        set(nlohmann_json_USE_STATIC_LIBS ON)
        set(nlohmann_json_USE_STATIC_RUNTIME ON)
    endif(MSVC)    
endif()