add_library(LibraryCPPTemplate INTERFACE)
target_include_directories(LibraryCPPTemplate INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(LibraryCPPTemplate INTERFACE cxx_std_14)
add_subdirectory(Tests)
