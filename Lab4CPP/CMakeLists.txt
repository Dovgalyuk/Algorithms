add_executable(Lab4CPP lab4.cpp)
target_include_directories (Lab4CPP PUBLIC ../LibraryCPPTemplate)


add_test(NAME TestLab4CPP_1 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab4CPP_1 PROPERTIES PASS_REGULAR_EXPRESSION 
"Ohona to Ohona: 0
Ohona to Pestovo: 20
Ohona to Novgorod: 320
Ohona to Borovichi: 80
Pestovo to Ohona: 580
Pestovo to Pestovo: 0
Pestovo to Novgorod: 300
Pestovo to Borovichi: 500
Novgorod to Ohona: 280
Novgorod to Pestovo: 300
Novgorod to Novgorod: 0
Novgorod to Borovichi: 200
Borovichi to Ohona: 680
Borovichi to Pestovo: 100
Borovichi to Novgorod: 400
Borovichi to Borovichi: 0")