add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)


add_test(NAME TestLab2CPP_Expr2
    COMMAND ${CMAKE_COMMAND} -E cmd /c "Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt > ${CMAKE_CURRENT_BINARY_DIR}/temp_output.txt && ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_BINARY_DIR}/temp_output.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt"
)