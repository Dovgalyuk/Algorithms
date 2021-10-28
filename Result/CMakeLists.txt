add_executable(Circuit circuit.cpp)
target_include_directories(Circuit PUBLIC ../LibraryCPP)
target_link_libraries(Circuit PUBLIC LibraryCPP)

add_executable(LaboratoryTwo laboratorytwo.cpp)
target_include_directories(LaboratoryTwo PUBLIC ../LibraryCPPTemplate)

add_executable(LaboratoryThree laboratorythree.cpp)
target_include_directories(LaboratoryThree PUBLIC ../LibraryCPPTemplate)

add_executable(LaboratoryFour laboratoryfour.cpp)
target_include_directories(LaboratoryFour PUBLIC ../LibraryCPPTemplate)

add_executable(LaboratoryFive laboratoryfive.cpp)
target_include_directories(LaboratoryFive PUBLIC ../LibraryCPP)
target_link_libraries(LaboratoryFive PUBLIC LibraryCPP)