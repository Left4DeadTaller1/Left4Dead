cmake_minimum_required(VERSION 3.10)
project(ExampleProject LANGUAGES C CXX)

# Compiler flags
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")

# Source files
file(GLOB_RECURSE COMMON_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/dipa_classes/*")
file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/client/*")
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/*" EXCLUDE "${CMAKE_SOURCE_DIR}/server_root/tests/*")
file(GLOB_RECURSE TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/tests/*")

# Executables
add_executable(client ${CLIENT_SRC} ${COMMON_SRC})
add_executable(server ${SERVER_SRC} ${COMMON_SRC})
add_executable(tests ${TESTS_SRC} ${COMMON_SRC})  # Add the tests executable

# Include directories
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/dipa_classes)
target_include_directories(server
    PRIVATE
    ${CMAKE_SOURCE_DIR}/dipa_classes
    server_root/server
)
target_include_directories(tests  # Include directories for the tests
    PRIVATE
    server_root/server
    server_root/tests
)

find_package(Threads REQUIRED)
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(server PRIVATE Threads::Threads)
target_link_libraries(tests PRIVATE Threads::Threads)  # Link the Threads library for tests

if(math)
  target_link_libraries(client PRIVATE m)
  target_link_libraries(server PRIVATE m)
  target_link_libraries(tests PRIVATE m)  # Link the math library for tests
endif()

if(static)
  set_target_properties(client PROPERTIES LINK_SEARCH_START_STATIC 1)
  set_target_properties(client PROPERTIES LINK_SEARCH_END_STATIC 1)
  set_target_properties(server PROPERTIES LINK_SEARCH_START_STATIC 1)
  set_target_properties(server PROPERTIES LINK_SEARCH_END_STATIC 1)
  set_target_properties(tests PROPERTIES LINK_SEARCH_START_STATIC 1)  # Set target properties for tests
  set_target_properties(tests PROPERTIES LINK_SEARCH_END_STATIC 1)  # Set target properties for tests
endif()

if(wrapsocks)
  target_compile_definitions(client PRIVATE wrapsocks=1)
  target_compile_definitions(server PRIVATE wrapsocks=1)
  target_link_libraries(client PRIVATE "-Wl,--wrap=send -Wl,--wrap=recv")
  target_link_libraries(server PRIVATE "-Wl,--wrap=send -Wl,--wrap=recv")
  target_link_libraries(tests PRIVATE "-Wl,--wrap=send -Wl,--wrap=recv")  # Link the wrapsocks library for tests
endif()

# Includes Google Test as a subdirectory
add_subdirectory(googletest)
