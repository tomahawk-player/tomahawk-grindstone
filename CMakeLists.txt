PROJECT( grindstone )
cmake_minimum_required(VERSION 2.8)

find_package(Tomahawk REQUIRED)
include( ${TOMAHAWK_USE_FILE} )

include_directories(
    ${TOMAHAWK_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}
)

set(CMAKE_AUTOMOC ON)

if( NOT TOMAHAWK_QT5 )
    add_definitions( "-DQ_DECL_FINAL=" )
    add_definitions( "-DQ_DECL_OVERRIDE=" )
endif()

add_executable( grindstone
    main.cpp
    Grindstone.cpp
    ResolverDialog.cpp
)

target_link_libraries( grindstone
    ${TOMAHAWK_LIBRARIES}
)


include(GNUInstallDirs)
INSTALL( TARGETS grindstone
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
