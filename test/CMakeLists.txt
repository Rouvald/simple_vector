find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# set(TEST_ALL_NAME test_all)
set(TEST_MAIN test_main.cpp)

#[[if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_MAIN}")
    message(FATAL_ERROR "${TEST_MAIN} not found")
endif ()]]

list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_MAIN}")

if (TEST_SOURCES)
    foreach (TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

        add_executable(${TEST_NAME} ${TEST_MAIN} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME} ${PROJECT_NAME_LIB} GTest::GTest GTest::Main)

        add_test(NAME "${TEST_NAME}" COMMAND "${TEST_NAME}")
    endforeach ()

    # add_executable(${TEST_ALL_NAME} ${TEST_MAIN} ${TEST_SOURCES})
    # target_link_libraries(${TEST_ALL_NAME} ${PROJECT_NAME_LIB} GTest::GTest GTest::Main)
    # add_test(NAME "${TEST_ALL_NAME}" COMMAND "${TEST_ALL_NAME}")
else ()
    message(WARNING "No test files found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif ()