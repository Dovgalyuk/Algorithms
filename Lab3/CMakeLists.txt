add_executable(Lab3 main.cpp)
target_include_directories(Lab3 PRIVATE ../LibraryCPPClass)
target_link_libraries(Lab3 PRIVATE LibraryCPPClass)
add_test(NAME TestLab3 COMMAND "${CMAKE_COMMAND}"
    "-DPROGRAM=$<TARGET_FILE:Lab3>" -P "${CMAKE_CURRENT_SOURCE_DIR}/test.cmake")
