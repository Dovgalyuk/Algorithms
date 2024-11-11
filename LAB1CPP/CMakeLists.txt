add_executable(LAB1CPP LAB1.cpp)
target_include_directories(LAB1CPP PUBLIC ../LibraryCPP)
target_link_libraries(LAB1CPP LibraryCPP)

#add_test(NAME TestLAB1CPP COMMAND LAB1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/output/output.txt")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_test(NAME TestLAB1CPP
    COMMAND LAB1CPP ${INPUT_FILE} ${OUTPUT_FILE}
)