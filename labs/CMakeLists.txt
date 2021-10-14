add_executable(MyFiles Test.cpp)
target_include_directories(MyFiles PUBLIC ../LibraryCPP)
target_link_libraries(MyFiles LibraryCPP)