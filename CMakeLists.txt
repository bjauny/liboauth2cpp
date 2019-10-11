cmake_minimum_required (VERSION 3.12.0)

include(GNUInstallDirs)

project (oauth2cpp VERSION 0.1.0 DESCRIPTION "OAuth2 library for C++")

add_library (oauth2cpp SHARED src/OAuth2.cpp)

set_target_properties(oauth2cpp PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(oauth2cpp PROPERTIES SOVERSION 1)
set_target_properties(oauth2cpp PROPERTIES PUBLIC_HEADER include/OAuth2.h)

target_include_directories(oauth2cpp PRIVATE .)

install(TARGETS oauth2cpp
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(demo_sources demo/swcombine.cpp)
add_executable(swcombine_demo ${demo_sources})
target_link_libraries(swcombine_demo oauth2cpp)
