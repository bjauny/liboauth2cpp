cmake_minimum_required (VERSION 3.12.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 " )

set(demo_sources swcombine.cpp)
link_directories(/usr/local/lib)

add_executable(swcombine_demo ${demo_sources})
target_link_libraries(swcombine_demo oauth2cpp curl)
