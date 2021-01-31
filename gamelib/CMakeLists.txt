## local variable for managing the gamelib target
project(GameLib)
set(GAMELIB "GameLib")

## glob is useful but not reliant in compilation so just use it for headers ##
file(GLOB_RECURSE HEADER_LIST
        LIST_DIRECTORIES FALSE
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h )

set(GAMELIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/game_component.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Lexington.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Mongol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Grid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Sector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Quadrant.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Star.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/StarBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Torpedo.cpp)

add_library(${GAMELIB} STATIC ${GAMELIB_SOURCES} "${HEADER_LIST}")
add_library(libs::${GAMELIB} ALIAS ${GAMELIB})
configure_target(${GAMELIB} ${CMAKE_CURRENT_SOURCE_DIR}/include "${HEADER_LIST}" "")
target_include_directories(${GAMELIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_asge_dependency(${GAMELIB})
