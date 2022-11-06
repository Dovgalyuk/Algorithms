add_executable(TaskFirstCPP Lab1/main.cpp)
target_include_directories(TaskFirstCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskFirstCPP LibraryCPP)

add_executable(TaskSecondCPP Lab2/main.cpp Lab2/Interpreter.hpp)
target_include_directories(TaskSecondCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskSecondCPP LibraryCPP)

add_executable(TaskThirdCPP Lab3/main.cpp)
add_library(lib SHARED Lab3/Labyrinth.cpp ${PROJECT_SOURCE_DIR}/LibraryCPP/queue.cpp ${PROJECT_SOURCE_DIR}/LibraryCPP/vector.cpp)
target_link_libraries(TaskThirdCPP lib)