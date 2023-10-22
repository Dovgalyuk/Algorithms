add_executable(Lab2 "lab2.cpp")
target_include_directories(Lab2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab2 LibraryCPP)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
