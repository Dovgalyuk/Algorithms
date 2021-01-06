add_executable(MyFiles Lab3.cpp)
target_include_directories(MyFiles PUBLIC ../LibraryCPP)
target_link_libraries(MyFiles LibraryCPP)