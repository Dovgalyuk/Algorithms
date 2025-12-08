add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab4CPP LibraryCPP)

add_test(NAME TestLab4CPP1 COMMAND $<TARGET_FILE:Lab4CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4CPP1 PROPERTY PASS_REGULAR_EXPRESSION  "Shortest path: A -> B -> D -> E")
