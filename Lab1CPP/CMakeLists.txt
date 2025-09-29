add_executable(Lab1CPP main.cpp)

target_include_directories(Lab1CPP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPClass
)

target_link_libraries(Lab1CPP PRIVATE LibraryCPPClass)

enable_testing()

add_test(NAME TestLab1CPP_Input1
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)
set_property(TEST TestLab1CPP_Input1 PROPERTY PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*None.*Unique elements:[ \\t]*2[ \\t]+3[ \\t]+20"
)

add_test(NAME TestLab1CPP_Input2
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)
set_property(TEST TestLab1CPP_Input2 PROPERTY PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*None.*Unique elements:[ \\t]*8[ \\t]+9"
)

add_test(NAME TestLab1CPP_Input3
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)
set_property(TEST TestLab1CPP_Input3 PROPERTY PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*0.*Unique elements:"
)

add_test(NAME TestLab1CPP_Input4
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)
set_tests_properties(TestLab1CPP_Input4 PROPERTIES PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\([-+]?[0-9]+\\):[ \\t]*1.*Unique elements:[ \\t]*10"
)

add_test(NAME TestLab1CPP_Input5
    COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt
)
set_property(TEST TestLab1CPP_Input5 PROPERTY PASS_REGULAR_EXPRESSION
    "Indices of elements greater than total sum \\(10\\):[ \\t]*None.*Unique elements:[ \\t]*None"
)