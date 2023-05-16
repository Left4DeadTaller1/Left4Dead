cmake_minimum_required(VERSION 3.1) 
project(Left4Dead)  

# Compiler flags
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

# For Google Test, remove -Werror flag
set(CMAKE_C_FLAGS_OLD ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_OLD ${CMAKE_CXX_FLAGS})
string(REPLACE "-Werror" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
string(REPLACE "-Werror" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# Add Google Test here
add_subdirectory(googletest)  

# Reset the flags back to original after Google Test is added
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_OLD})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_OLD})

# Source files
file(GLOB_RECURSE COMMON_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/dipa_classes/*")
file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/client/*")
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/*")

# Executables
add_executable(client ${CLIENT_SRC} ${COMMON_SRC})
add_executable(server ${SERVER_SRC} ${COMMON_SRC})

# Include directories
target_include_directories(client 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/server_root/client_connection
)

target_include_directories(server
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    ${CMAKE_SOURCE_DIR}/server_root/server
    ${CMAKE_SOURCE_DIR}/server_root/client_connection
)

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
