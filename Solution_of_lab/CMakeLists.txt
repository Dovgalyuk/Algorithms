add_executable(Solution_of_lab lab_1.cpp)
target_include_directories(Solution_of_lab PUBLIC ../LibraryCPP)
target_link_libraries(Solution_of_lab PUBLIC LibraryCPP)


add_executable(LaboratoryTwo lab_2.cpp)
target_include_directories(LaboratoryTwo PUBLIC ../LibraryCPP)
target_include_directories(LaboratoryTwo PUBLIC ../LibraryCPPTemplate)