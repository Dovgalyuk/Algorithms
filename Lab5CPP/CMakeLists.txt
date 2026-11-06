add_executable(GenerateData generator.cpp)
target_compile_features(GenerateData PRIVATE cxx_std_11)

add_executable(Lab5CPP lab5.cpp)
target_link_libraries(Lab5CPP LibraryCPP)

add_executable(StressBwa stress.cpp)
target_link_libraries(StressBwa LibraryCPP)

add_test(NAME TestLab5CPP COMMAND Lab5CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab5CPP PROPERTIES TIMEOUT 30)

add_test(NAME GenerateMillion COMMAND GenerateData
    ${CMAKE_CURRENT_BINARY_DIR}/million.txt 1000000)
set_tests_properties(GenerateMillion PROPERTIES FIXTURES_SETUP MillionData TIMEOUT 10)

add_test(NAME LoadMillion COMMAND Lab5CPP
    ${CMAKE_CURRENT_BINARY_DIR}/million.txt)
set_tests_properties(LoadMillion PROPERTIES FIXTURES_REQUIRED MillionData TIMEOUT 10)

add_test(NAME StressMillion COMMAND StressBwa
    ${CMAKE_CURRENT_BINARY_DIR}/million.txt 1000000)
set_tests_properties(StressMillion PROPERTIES FIXTURES_REQUIRED MillionData TIMEOUT 10)
