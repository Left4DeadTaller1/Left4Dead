add_test( ClientProtocolTest.ReceiveCreateOrJoinTest /home/usaurio/Left4Dead/build/tests/client_test [==[--gtest_filter=ClientProtocolTest.ReceiveCreateOrJoinTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientProtocolTest.ReceiveCreateOrJoinTest PROPERTIES WORKING_DIRECTORY /home/usaurio/Left4Dead/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( client_test_TESTS ClientProtocolTest.ReceiveCreateOrJoinTest)
