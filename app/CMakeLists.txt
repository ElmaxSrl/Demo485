cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/include)

file(GLOB native_srcs "src/main/cpp/*.cpp")
add_library(
            demo485
            SHARED
            ${native_srcs})

target_link_libraries(demo485 ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/libs/libmisc.a)
target_link_libraries(demo485 ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/libs/libtinyxml.a)
target_link_libraries(demo485 android log)
