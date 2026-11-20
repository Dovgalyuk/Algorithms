execute_process(COMMAND ${Labirint} ${INPUT} ${OUTPUT} RESULT_VARIABLE run_result)

if(NOT run_result EQUAL 0) 
    message(FATAL_ERROR "Ошибка: ${run_result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files ${OUTPUT} ${EXPECTED}
    RESULT_VARIABLE cmp_result)

if(NOT cmp_result EQUAL 0)
    message(FATAL_ERROR "Вывод не совпадает с ожидаемым результатом")
endif()

message(STATUS "Тест пройден")
    