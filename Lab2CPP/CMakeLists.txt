add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME Lab2_Test_HelloWorld COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script1.fish ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Lab2_Test_HelloWorld PROPERTY PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(NAME Lab2_Test_2D_Math COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script2.fish ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Lab2_Test_2D_Math PROPERTY PASS_REGULAR_EXPRESSION "35")

add_test(NAME Lab2_Test_Stack_LIFO COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script3.fish ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Lab2_Test_Stack_LIFO PROPERTY PASS_REGULAR_EXPRESSION "HSIF")

add_test(NAME Lab2_Test_Sequence_Countdown COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script4.fish ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Lab2_Test_Sequence_Countdown PROPERTY PASS_REGULAR_EXPRESSION "54321")