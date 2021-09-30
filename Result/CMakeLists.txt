add_executable(Circuit circuit.cpp)
target_link_libraries(Circuit PUBLIC LibraryCPP)

add_executable(LaboratoryTwo laboratorytwo.cpp)
target_include_directories(LaboratoryTwo PUBLIC ../LibraryCPPTemplate)

add_executable(LaboratoryThree laboratorythree.cpp)
target_include_directories(LaboratoryThree PUBLIC ../LibraryCPPTemplate)