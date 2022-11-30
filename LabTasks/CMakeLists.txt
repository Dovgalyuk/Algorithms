add_executable(TaskFirstCPP Lab1/main.cpp)
target_include_directories(TaskFirstCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskFirstCPP LibraryCPP)

add_executable(TaskSecondCPP Lab2/main.cpp Lab2/Interpreter.hpp)
target_include_directories(TaskSecondCPP PUBLIC ${PROJECT_SOURCE_DIR}/LibraryCPP)
target_link_libraries(TaskSecondCPP LibraryCPP)

add_executable(TaskThirdCPP Lab3/main.cpp)
add_library(lib_1 SHARED Lab3/Labyrinth.cpp ${PROJECT_SOURCE_DIR}/LibraryCPP/queue.cpp ${PROJECT_SOURCE_DIR}/LibraryCPP/vector.cpp)
target_link_libraries(TaskThirdCPP lib_1)

add_executable(TaskFourthCPP Lab4/main.cpp)
add_library(lib_2 SHARED Lab4/KruskalsAlgorithm.cpp ${PROJECT_SOURCE_DIR}/LibraryCPPTemplate/graph.h ${PROJECT_SOURCE_DIR}/LibraryCPPTemplate/vector.h)
target_link_libraries(TaskFourthCPP lib_2)