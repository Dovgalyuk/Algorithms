add_executable(LaboratoryOne lab_1.cpp)
target_include_directories(LaboratoryOne PUBLIC ../LibraryCPP)
target_link_libraries(Solution_of_lab PUBLIC LibraryCPP)

add_executable(LaboratoryTwo lab_2.cpp)
target_include_directories(LaboratoryTwo PUBLIC ../LibraryCPPTemplate)

add_executable(LaboratoryThree lab_3.cpp)
target_include_directories(LaboratoryThree PUBLIC ../LibraryCPPTemplate)