add_executable(TestArrayCPPTemplate array.cpp)

target_include_directories(
    TestArrayCPPTemplate
    PUBLIC
    ..
)

add_test(
    NAME TestArrayCPPTemplate
    COMMAND TestArrayCPPTemplate
)
