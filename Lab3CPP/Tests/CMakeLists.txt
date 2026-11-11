add_executable(MyTestLab3CPP tests.cpp)

add_test(
        NAME MyTestLab3CPP
        COMMAND MyTestLab3CPP $<TARGET_FILE:Lab3CPP>
)

set_tests_properties( MyTestLab3CPP PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
