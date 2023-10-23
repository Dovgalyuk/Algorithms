add_executable(Labs "lab1.cpp")
target_include_directories(Labs PUBLIC ../LibraryCPP)
target_link_libraries(Labs LibraryCPP)

add_executable(Labs2 "lab2.cpp")
target_include_directories(Labs2 PUBLIC ../LibraryCPP)
target_link_libraries(Labs2 LibraryCPP)

add_executable(Labs3 "lab3.cpp")
target_include_directories(Labs3 PUBLIC ../LibraryCPP)
target_link_libraries(Labs3 LibraryCPP)

add_executable(Labs4 "lab4.cpp")
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)