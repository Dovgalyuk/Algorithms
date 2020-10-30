project(Main)

add_executable(LibraryArseny main.cpp)

target_include_directories(LibraryArseny PUBLIC ../LibraryCPP)

target_link_libraries(LibraryArseny LibraryCPP)