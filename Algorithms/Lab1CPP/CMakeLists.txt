add_executable(Lab1CPPMonthly monthly_precipitation.cpp)
add_executable(Lab1CPPCompress compress_array.cpp)
foreach(target Lab1CPPMonthly Lab1CPPCompress)
    target_include_directories(${target} PRIVATE ../LibraryCPPTemplate)
    target_compile_features(${target} PRIVATE cxx_std_11)
endforeach()

function(add_output_test name target)
    add_test(NAME TestLab1CPP_${name}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:${target}>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/examples/${name}.txt"
            "-DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/examples/${name}.expected"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake")
endfunction()

foreach(name monthly_constant monthly_leap monthly_sequence monthly_fractional monthly_zero)
    add_output_test(${name} Lab1CPPMonthly)
endforeach()
foreach(name compress_mixed compress_all compress_none compress_equal compress_empty compress_fractional compress_single)
    add_output_test(${name} Lab1CPPCompress)
endforeach()

function(add_error_test name target)
    add_test(NAME TestLab1CPP_${name}
        COMMAND ${target} "${CMAKE_CURRENT_SOURCE_DIR}/examples/${name}.txt")
    set_tests_properties(TestLab1CPP_${name} PROPERTIES WILL_FAIL TRUE TIMEOUT 10)
endfunction()

foreach(name monthly_bad_size monthly_short monthly_negative monthly_overflow monthly_bad_value monthly_missing)
    add_error_test(${name} Lab1CPPMonthly)
endforeach()
foreach(name compress_bad_size compress_short compress_reversed compress_no_bounds compress_bad_value compress_missing)
    add_error_test(${name} Lab1CPPCompress)
endforeach()

add_test(NAME TestLab1CPP_monthly_no_args COMMAND Lab1CPPMonthly)
add_test(NAME TestLab1CPP_compress_no_args COMMAND Lab1CPPCompress)
set_tests_properties(TestLab1CPP_monthly_no_args TestLab1CPP_compress_no_args
    PROPERTIES WILL_FAIL TRUE TIMEOUT 10)
