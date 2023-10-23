add_executable(Lab1C "lab1.cpp")
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

add_executable(Labs2 "lab2.cpp")
target_include_directories(Labs2 PUBLIC ../LibraryCPP)
target_link_libraries(Labs2 LibraryCPP)
