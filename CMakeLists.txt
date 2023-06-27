cmake_minimum_required(VERSION 3.16)
project(Left4Dead LANGUAGES CXX)

# Compiler flags
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

# Define BASE_PATH macro
add_compile_definitions(BASE_PATH="${CMAKE_SOURCE_DIR}")

# For Google Test, remove -Werror flag
set(CMAKE_C_FLAGS_OLD ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_OLD ${CMAKE_CXX_FLAGS})
string(REPLACE "-Werror" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
string(REPLACE "-Werror" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# Add Google Test here
add_subdirectory(lib/googletest)

# Reset the flags back to original after Google Test is added
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_OLD})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_OLD})

# Source files
file(GLOB_RECURSE COMMON_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/dipa_classes/*")
file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/client/*")
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/*")

# Create a library for the server source files
add_library(server_lib STATIC ${SERVER_SRC} ${COMMON_SRC})

# Executables
add_executable(client ${CLIENT_SRC} ${COMMON_SRC})
add_executable(server ${SERVER_SRC} ${COMMON_SRC})

# Link the library to your executables
target_link_libraries(client PRIVATE server_lib)
target_link_libraries(server PRIVATE server_lib)

# Include directories
target_include_directories(client
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/client/actions
    ${CMAKE_SOURCE_DIR}/client/render
    ${CMAKE_SOURCE_DIR}/client/render/game
    ${CMAKE_SOURCE_DIR}/client/render/sound
    ${CMAKE_SOURCE_DIR}/client/render/texture
    ${CMAKE_SOURCE_DIR}/client/client_connection
    ${CMAKE_SOURCE_DIR}/client/configuration
    ${CMAKE_SOURCE_DIR}/client/menuQT
    ${SDL2PP_INCLUDE_DIRS}
)

target_include_directories(server_lib
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/server_root/server
    ${CMAKE_SOURCE_DIR}/server_root/entities
    ${CMAKE_SOURCE_DIR}/server_root/entities/zombies
    ${CMAKE_SOURCE_DIR}/server_root/client_connection
    ${CMAKE_SOURCE_DIR}/server_root/game
    ${CMAKE_SOURCE_DIR}/server_root/game/configuration
)

target_include_directories(server
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/server_root/server
    ${CMAKE_SOURCE_DIR}/server_root/entities
    ${CMAKE_SOURCE_DIR}/server_root/entities/zombies
    ${CMAKE_SOURCE_DIR}/server_root/client_connection
    ${CMAKE_SOURCE_DIR}/server_root/game
    ${CMAKE_SOURCE_DIR}/server_root/game/configuration
)

target_link_libraries(server_lib PRIVATE yaml-cpp)
target_link_libraries(server PRIVATE yaml-cpp)

find_package(Threads REQUIRED)
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(server PRIVATE Threads::Threads)

if(math)
    target_link_libraries(client PRIVATE m)
    target_link_libraries(server PRIVATE m)
endif()

if(static)
    set_target_properties(client PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(client PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(server PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(server PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()

if(wrapsocks)
    target_compile_definitions(client PRIVATE wrapsocks=1)
    target_compile_definitions(server PRIVATE wrapsocks=1)
    target_link_libraries(client PRIVATE "-Wl,--wrap=send -Wl,--wrap=recv")
    target_link_libraries(server PRIVATE "-Wl,--wrap=send -Wl,--wrap=recv")
endif()

# Include the tests directory
add_subdirectory(tests)

# SDL
find_package(SDL2pp REQUIRED)

# Add compilation flags
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}")
include_directories(${SDL2PP_INCLUDE_DIRS})

# Define targets
target_link_libraries(client PUBLIC SDL2pp::SDL2pp)

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)

target_include_directories(client PRIVATE ${CMAKE_BINARY_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Multimedia)

qt5_wrap_ui(UIS_HEADERS
    client/menuQT/mainwindow.ui
    client/menuQT/create.ui
    client/menuQT/join.ui
)

add_library(menuQT
    client/menuQT/mainwindow.cpp
    client/menuQT/mainwindow.h
    client/menuQT/create.cpp
    client/menuQT/create.h
    client/menuQT/join.cpp
    client/menuQT/join.h
    client/menuQT/hiloMensajes.cpp
    client/menuQT/hiloMensajes.h
    ${UIS_HEADERS}
)

# Include directories
target_include_directories(menuQT
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/client/actions
    ${CMAKE_SOURCE_DIR}/client
    ${CMAKE_SOURCE_DIR}/client/render/game
    ${CMAKE_SOURCE_DIR}/client/render
    ${CMAKE_SOURCE_DIR}/client/render/sound
    ${CMAKE_SOURCE_DIR}/client/render/texture
    ${CMAKE_SOURCE_DIR}/client/client_connection
    ${CMAKE_SOURCE_DIR}/client/menuQT
    ${SDL2PP_INCLUDE_DIRS}
)

message("Generating UI headers: ${UIS_HEADERS}")

set(SOUND_FONDO_QT "${CMAKE_SOURCE_DIR}/client/render/resources/sounds/fondo3.mp3")
target_compile_definitions(menuQT PRIVATE SOUND_FONDO_QT="${SOUND_FONDO_QT}")

set(IMAGEN_FONDO_QT "${CMAKE_SOURCE_DIR}/client/render/resources/fondoqt2.jpeg")
target_compile_definitions(menuQT PRIVATE IMAGEN_FONDO_QT="${IMAGEN_FONDO_QT}")

set(ICONO_SONIDO_QT "${CMAKE_SOURCE_DIR}/client/render/resources/icono_sonido.png")
target_compile_definitions(menuQT PRIVATE ICONO_SONIDO_QT="${ICONO_SONIDO_QT}")

target_link_libraries(menuQT PRIVATE Qt5::Widgets Qt5::Multimedia)

target_link_libraries(client PRIVATE menuQT)
target_link_libraries(client PRIVATE Qt5::Widgets Qt5::Multimedia)






