add_library(LibraryCPP STATIC bwa.cpp)
target_include_directories(LibraryCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(LibraryCPP PUBLIC cxx_std_11)

add_subdirectory(Tests)
