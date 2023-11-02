add_executable(LaboratoryC "Source.cpp")
target_include_directories(LaboratoryC PUBLIC ../LibraryCPP)
target_link_libraries(LaboratoryC LibraryCPP)
