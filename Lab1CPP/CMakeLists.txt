# Создаем исполняемый файл
add_executable(Lab1CPP lab1.cpp)
target_link_libraries(Lab1CPP LibraryCPP)
target_include_directories(Lab1CPP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP)

# Включаем поддержку тестов
enable_testing()

add_test(NAME Lab1CPP_Test
        COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input result)
