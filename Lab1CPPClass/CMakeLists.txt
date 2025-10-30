add_executable(Rainfall rainfall.cpp)
add_executable(MostFrequent mostFrequent.cpp)

target_include_directories(Rainfall PUBLIC ../LibraryCPPClass)
target_link_libraries(Rainfall LibraryCPPClass)

target_include_directories(MostFrequent PUBLIC ../LibraryCPPClass)
target_link_libraries(MostFrequent LibraryCPPClass)

add_test(NAME TestRainfall COMMAND Rainfall ${CMAKE_CURRENT_SOURCE_DIR}/dataRainfall.txt)
set_property(TEST TestRainfall PROPERTY
    PASS_REGULAR_EXPRESSION "Средние осадки \\(мм\\):.*1-я декада: 1\\.8.*2-я декада: 2\\.8.*3-я декада: 1\\.3")

add_test(NAME TestMostFrequent COMMAND MostFrequent ${CMAKE_CURRENT_SOURCE_DIR}/dataMostFrequent.txt)
set_property(TEST TestMostFrequent PROPERTY
    PASS_REGULAR_EXPRESSION "Самое частое число: 1\\(встречается 8 раз\\)")

add_test(NAME TestRainfallFail COMMAND Rainfall ${CMAKE_CURRENT_SOURCE_DIR}/dataRainfallFail.txt)
set_property(TEST TestRainfallFail PROPERTY
    PASS_REGULAR_EXPRESSION "Ошибка: в месяце не может быть меньше 28 дней")

