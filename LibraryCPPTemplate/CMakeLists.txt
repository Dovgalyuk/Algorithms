add_library(LibraryCPPTemplate STATIC ..)
set_target_properties(LibraryCPPTemplate PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(Tests)
