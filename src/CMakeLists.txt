ADD_EXECUTABLE( hellocmake main.cpp)
target_include_directories(hellocmake PUBLIC ../LibraryC)
target_link_libraries(hellocmake LibraryC)
