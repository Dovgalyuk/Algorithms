add_executable(Lab1CPP lab1.cpp)


target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
#target_include_directories(Lab1C PUBLIC /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.0.sdk/usr/include)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
