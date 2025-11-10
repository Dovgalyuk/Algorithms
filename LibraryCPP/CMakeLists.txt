add_library(LibraryCPP array.cpp vector.cpp stack.cpp list.cpp queue.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Подключаем тесты
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
    add_subdirectory(Tests)
endif()