add_executable(Lab1CPP 1Rabota.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

set(OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/output.txt)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${OUTPUT_FILE})