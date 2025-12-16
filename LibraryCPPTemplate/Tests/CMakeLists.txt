[file name]: LibraryCPPTemplate/CMakeLists.txt
[file content begin]
# Библиотека шаблонов
project(LibraryCPPTemplate)

add_library(LibraryCPPTemplate INTERFACE)

target_include_directories(LibraryCPPTemplate INTERFACE .)

set(LIBRARY_HEADERS
    vector.h
    graph.h
)

if(BUILD_TESTING)
    enable_testing()
    
    add_executable(TestVector vector.cpp)
    target_link_libraries(TestVector LibraryCPPTemplate)
    add_test(NAME TestVector COMMAND TestVector)
    
    add_executable(TestGraph graph.cpp)
    target_link_libraries(TestGraph LibraryCPPTemplate)
    add_test(NAME TestGraph COMMAND TestGraph)
endif()
[file content end]