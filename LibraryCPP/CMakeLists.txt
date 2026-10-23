add_library(LibraryCPP STATIC list.cpp queue.cpp stack.cpp vector.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(LibraryCPP PUBLIC cxx_std_17)

add_executable(library_cpp_main main.cpp)
target_link_libraries(library_cpp_main PRIVATE LibraryCPP)

add_subdirectory(Tests)
