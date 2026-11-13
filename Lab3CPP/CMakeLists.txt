add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Test1Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output.txt)
set_property(TEST Test1Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "")
