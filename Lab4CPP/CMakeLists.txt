file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Lab4CPP lab4.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)


add_test(NAME Test1Lab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
