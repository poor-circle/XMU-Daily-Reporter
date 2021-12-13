cmake_minimum_required(VERSION 3.8.0)

project(daily_reporter VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

set(static_link "ON") # set if enable static link 

set(mailio_lib_type "Release") # set link version of mailio

#config about static link
if(static_link STREQUAL "ON")
    message("-- Link by static!!!")
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-static")
    endif()    
endif()
#config about debug/release library of mailio


#set include path
include_directories(include)
#set cpp file path
aux_source_directory(src SRC_LIST)
add_executable(daily_reporter ${SRC_LIST})

#add third-party library: mailio, OpenSSL, fmt, nlohmann_json and httplib


#bullshit code for mailiolib 
find_path(MAILIO_INCLUDE_DIR "mailio/smtp.hpp")
get_filename_component(MAILIO_LIB_DIR ${MAILIO_INCLUDE_DIR} DIRECTORY)
if (mailio_lib_type STREQUAL "Release")
    set(MAILIO_LIB_DIR ${MAILIO_LIB_DIR}/lib)
else()
    set(MAILIO_LIB_DIR ${MAILIO_LIB_DIR}/debug/lib)
endif()
find_library(MAILIO_LIBRARY mailio)

get_filename_component(MAILIO_FALSE_LIB_DIR ${MAILIO_LIBRARY} DIRECTORY)
string(LENGTH ${MAILIO_LIBRARY} len)
string(LENGTH ${MAILIO_FALSE_LIB_DIR} len_base)
string(SUBSTRING ${MAILIO_LIBRARY} ${len_base} ${len}-${len_base} MAILIO_NAME)
set(MAILIO_LIBRARY ${MAILIO_LIB_DIR}${MAILIO_NAME})

target_include_directories(daily_reporter PRIVATE ${MAILIO_INCLUDE_DIR})
target_link_libraries(daily_reporter PRIVATE ${MAILIO_LIBRARY})
message("-- find mailio library: "${MAILIO_LIBRARY})

find_package(OpenSSL REQUIRED)
    target_link_libraries(daily_reporter PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(fmt CONFIG REQUIRED)
    target_link_libraries(daily_reporter PRIVATE fmt::fmt-header-only)

find_package(nlohmann_json CONFIG REQUIRED)
    target_link_libraries(daily_reporter PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
    target_include_directories(daily_reporter PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})

find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(daily_reporter PRIVATE spdlog::spdlog_header_only)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)