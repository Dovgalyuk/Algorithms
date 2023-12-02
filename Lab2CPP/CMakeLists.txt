add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})