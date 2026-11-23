add_library(Lab3Containers STATIC
    ${CMAKE_SOURCE_DIR}/LibraryCPP/vector.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPP/queue.cpp
)

target_include_directories(Lab3Containers PUBLIC
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

add_executable(Lab3CPP main.cpp)

target_link_libraries(Lab3CPP PRIVATE Lab3Containers)