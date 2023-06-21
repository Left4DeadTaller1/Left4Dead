# Enable the test suite
enable_testing()

find_package(GTest REQUIRED)


# Set the paths to Google Test and Google Mock libraries (relative to CMakeLists.txt)
set(GOOGLE_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest")
set(GOOGLE_MOCK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest/googlemock")

# Include the directories for Google Test and Google Mock
include_directories(${GOOGLE_TEST_PATH}/include)
include_directories(${GOOGLE_MOCK_PATH}/include)


# Get all test files
file(GLOB_RECURSE SERVER_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server_tests/*.cpp")
file(GLOB_RECURSE CLIENT_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_tests/*.cpp")

# Add the test executable
add_executable(server_tests ${SERVER_TESTS_SRC})
add_executable(client_tests ${CLIENT_TESTS_SRC})

# Link the server library, Google Test, and Google Mock libraries
target_link_libraries(server_tests server_lib GTest::GTest GTest::Main pthread)
target_link_libraries(client_tests gtest gtest_main gmock gmock_main)


# Include directories for the test executable
target_include_directories(server_tests
   PRIVATE 
   ${CMAKE_SOURCE_DIR}/dipa_classes
   ${CMAKE_SOURCE_DIR}/server_root/client_connection
   ${CMAKE_SOURCE_DIR}/server_root/entities
   ${CMAKE_SOURCE_DIR}/server_root/entities/zombies
   ${CMAKE_SOURCE_DIR}/server_root/game/configuration
   ${CMAKE_SOURCE_DIR}/server_root/game
   ${CMAKE_SOURCE_DIR}/server_root/server
)

target_include_directories(client_tests
   PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest/googlemock/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../dipa_classes
   ${CMAKE_CURRENT_SOURCE_DIR}/../client/client_connection
   ${CMAKE_CURRENT_SOURCE_DIR}/../client/render
   ${CMAKE_CURRENT_SOURCE_DIR}/../client/actions
)

# Agregar los archivos de implementación
file(GLOB CLIENT_PROTOCOL_SRC "${CMAKE_SOURCE_DIR}/client/client_connection/client_protocol.cpp")
file(GLOB SOCKET_SRC "${CMAKE_SOURCE_DIR}/dipa_classes/socket.cpp")
target_sources(client_tests PRIVATE "${CMAKE_SOURCE_DIR}/dipa_classes/resolver.cpp")
target_sources(client_tests PRIVATE "${CMAKE_SOURCE_DIR}/dipa_classes/liberror.cpp")
target_sources(client_tests PRIVATE "${CMAKE_SOURCE_DIR}/dipa_classes/resolvererror.cpp")


# Agregar los archivos fuente a los ejecutables de prueba
target_sources(client_tests PRIVATE ${CLIENT_PROTOCOL_SRC} ${SOCKET_SRC})

# Discover tests
include(GoogleTest)
gtest_discover_tests(server_tests)
gtest_discover_tests(client_tests)









