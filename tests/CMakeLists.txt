# Enable the test suite
enable_testing()

# Find the GTest package, see how to install it in the tool's documentation
find_package(GTest REQUIRED)

# Get all test files
file(GLOB_RECURSE SERVER_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server_tests/*.cpp")

# Add the test executable
add_executable(server_tests ${SERVER_TESTS_SRC})

# Link the server library and GTest libraries and pthread
target_link_libraries(server_tests server_lib GTest::GTest GTest::Main pthread)

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

# Discover tests
include(GoogleTest)
gtest_discover_tests(server_tests)

# Commented out client and cconnection tests
#file(GLOB_RECURSE CLIENT_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_tests/*.cpp")
#file(GLOB_RECURSE CCONNECTION_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cconnection_tests/*.cpp")
#add_executable(client_tests ${CLIENT_TESTS_SRC})
#add_executable(cconnection_tests ${CCONNECTION_TESTS_SRC})
#target_include_directories(client_tests
#    PRIVATE
#    ${CMAKE_SOURCE_DIR}/dipa_classes
#    ${CMAKE_SOURCE_DIR}/client
#)
#target_include_directories(cconnection_tests
#    PRIVATE
#    ${CMAKE_SOURCE_DIR}/dipa_classes
#    ${CMAKE_SOURCE_DIR}/server_root/client_connection
#    ${CMAKE_SOURCE_DIR}/server_root/server
#    ${CMAKE_SOURCE_DIR}/client
#)
#target_link_libraries(client_tests gtest_main gtest pthread)
#target_link_libraries(cconnection_tests gtest_main gtest pthread)
