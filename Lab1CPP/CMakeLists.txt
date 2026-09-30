add_executable(Lab1CPPMonthly monthly_precipitation.cpp)
target_include_directories(Lab1CPPMonthly PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPPMonthly LibraryCPP)

add_executable(Lab1CPPCompress compress_array.cpp)
target_include_directories(Lab1CPPCompress PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPPCompress LibraryCPP)

add_test(NAME TestLab1CPPMonthly365
         COMMAND Lab1CPPMonthly ${CMAKE_CURRENT_SOURCE_DIR}/monthly_365.txt)
set_property(TEST TestLab1CPPMonthly365 PROPERTY
             PASS_REGULAR_EXPRESSION "31 28 31 30 31 30 31 31 30 31 30 31")

add_test(NAME TestLab1CPPMonthly366
         COMMAND Lab1CPPMonthly ${CMAKE_CURRENT_SOURCE_DIR}/monthly_366.txt)
set_property(TEST TestLab1CPPMonthly366 PROPERTY
             PASS_REGULAR_EXPRESSION "62 58 62 60 62 60 62 62 60 62 60 62")

add_test(NAME TestLab1CPPCompressMixed
         COMMAND Lab1CPPCompress ${CMAKE_CURRENT_SOURCE_DIR}/compress_mixed.txt)
set_property(TEST TestLab1CPPCompressMixed PROPERTY
             PASS_REGULAR_EXPRESSION "1 2 7 8 0 0 0 0")

add_test(NAME TestLab1CPPCompressAll
         COMMAND Lab1CPPCompress ${CMAKE_CURRENT_SOURCE_DIR}/compress_all.txt)
set_property(TEST TestLab1CPPCompressAll PROPERTY
             PASS_REGULAR_EXPRESSION "0 0 0 0 0")
