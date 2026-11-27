add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

if (MSVC)
    target_compile_definitions(Lab1C PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
