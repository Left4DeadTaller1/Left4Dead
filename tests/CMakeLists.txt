
file(GLOB_RECURSE SERVER_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server_tests/*.cpp")
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/server/*.cpp")
file(GLOB_RECURSE CLIENT_CONNECTION_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/server_root/client_connection/*.cpp")

add_library(server_lib ${SERVER_SRC} ${CLIENT_CONNECTION_SRC})
target_include_directories(server_lib
PRIVATE
${CMAKE_SOURCE_DIR}/dipa_classes
${CMAKE_SOURCE_DIR}/server_root/server
${CMAKE_SOURCE_DIR}/server_root/client_connection
)

add_executable(server_tests ${SERVER_TESTS_SRC})
target_include_directories(server_tests
PRIVATE
${CMAKE_SOURCE_DIR}/dipa_classes
${CMAKE_SOURCE_DIR}/server_root/server
${CMAKE_SOURCE_DIR}/server_root/client_connection
)

target_link_libraries(server_tests gtest_main gtest pthread server_lib)

# file(GLOB_RECURSE CLIENT_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_tests/*.cpp")
# file(GLOB_RECURSE CCONNECTION_TESTS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cconnection_tests/*.cpp")
# add_executable(client_tests ${CLIENT_TESTS_SRC})
# add_executable(cconnection_tests ${CCONNECTION_TESTS_SRC})
# target_include_directories(client_tests
#     PRIVATE
#     ${CMAKE_SOURCE_DIR}/dipa_classes
#     ${CMAKE_SOURCE_DIR}/client
# )
# target_include_directories(cconnection_tests
#     PRIVATE
#     ${CMAKE_SOURCE_DIR}/dipa_classes
#     ${CMAKE_SOURCE_DIR}/server_root/client_connection
#     ${CMAKE_SOURCE_DIR}/server_root/server
#     ${CMAKE_SOURCE_DIR}/client
# )
# target_link_libraries(client_tests gtest_main gtest pthread)
# target_link_libraries(cconnection_tests gtest_main gtest pthread)
