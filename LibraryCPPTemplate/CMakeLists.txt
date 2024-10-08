add_library(LibraryCPPTemplate INTERFACE vector.h)
set_target_properties(LibraryCPPTemplate PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(Tests)
