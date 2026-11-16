add_executable(task task.cpp)

# Заголовки list.h / queue.h из библиотеки
target_include_directories(task PUBLIC ${CMAKE_SOURCE_DIR}/LibraryCPP)

target_link_libraries(task LibraryCPP)

add_subdirectory(Tests)