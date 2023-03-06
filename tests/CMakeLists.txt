
set(UNITE_TEST_NAME "yazi_test")
add_executable(${UNITE_TEST_NAME} test.cc main.cc ${PROJECT_ROOT}/utility/IniFile.cpp)
add_definitions(-DINI_FILE="${PROJECT_ROOT}/config/main.ini")

target_include_directories(${UNITE_TEST_NAME}
    PUBLIC ${PROJECT_ROOT}/utility
)
target_link_libraries(${UNITE_TEST_NAME} gtest gmock pthread)

set_target_properties(${UNITE_TEST_NAME}
    PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/unit_test
)