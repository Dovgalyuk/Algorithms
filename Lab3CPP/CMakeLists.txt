
add_executable(Lab3CPP task.cpp)

target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

# Ожидаемые ответы для 10 лабиринтов
set(EXPECTED_RESULTS
    4
    7
    2
    6
    8
    5
    1
    2
    "NOT FOUND"
    5
    5
    7
)

# Регистрация тестов Maze01 - Maze10
foreach(i RANGE 1 12)
    math(EXPR index "${i} - 1")
    list(GET EXPECTED_RESULTS ${index} expected)

    if(i LESS 10)
        set(number "0${i}")
    else()
        set(number "${i}")
    endif()

    add_test(
        NAME Maze${number}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Lab3CPP>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${number}.txt"
            "-DEXPECTED=${expected}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake"
    )
endforeach()
