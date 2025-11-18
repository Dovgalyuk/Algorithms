add_executable(Lab4CPP lab4.cpp)
target_include_directories (Lab4CPP PUBLIC ../LibraryCPPTemplate)


add_test(NAME TestLab4CPP_1 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(TestLab4CPP_1 PROPERTIES PASS_REGULAR_EXPRESSION 
"From Ohona to Pestovo, distance: 20
Path: Ohona -> Pestovo

From Ohona to Novgorod, distance: 320
Path: Ohona -> Pestovo -> Novgorod

From Ohona to Borovichi, distance: 80
Path: Ohona -> Borovichi

From Pestovo to Ohona, distance: 580
Path: Pestovo -> Novgorod -> Ohona

From Pestovo to Novgorod, distance: 300
Path: Pestovo -> Novgorod

From Pestovo to Borovichi, distance: 500
Path: Pestovo -> Novgorod -> Borovichi

From Novgorod to Ohona, distance: 280
Path: Novgorod -> Ohona

From Novgorod to Pestovo, distance: 300
Path: Novgorod -> Ohona -> Pestovo

From Novgorod to Borovichi, distance: 200
Path: Novgorod -> Borovichi

From Borovichi to Ohona, distance: 680
Path: Borovichi -> Pestovo -> Novgorod -> Ohona

From Borovichi to Pestovo, distance: 100
Path: Borovichi -> Pestovo

From Borovichi to Novgorod, distance: 400
Path: Borovichi -> Pestovo -> Novgorod")