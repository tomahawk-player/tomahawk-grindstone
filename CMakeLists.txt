cmake_minimum_required(VERSION 2.8)

find_package(Tomahawk REQUIRED)
include( ${TOMAHAWK_USE_FILE} )

include_directories(
    ${TOMAHAWK_INCLUDE_DIRS}
)

add_executable( grindstone
    main.cpp
)

target_link_libraries( grindstone
    ${TOMAHAWK_LIBRARIES}
)