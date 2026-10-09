add_executable(BeatnikCPP main.cpp)
target_include_directories(BeatnikCPP PRIVATE ../LibraryCPP)
target_link_libraries(BeatnikCPP PRIVATE LibraryCPP)

# Each case runs the interpreter and compares the complete output with the expected result.
function(add_beatnik_test test_name script input expected)
    set(script_file "${CMAKE_CURRENT_BINARY_DIR}/${test_name}.beatnik")
    set(input_file "${CMAKE_CURRENT_BINARY_DIR}/${test_name}.in")
    file(WRITE "${script_file}" "${script}\n")
    file(WRITE "${input_file}" "${input}")
    add_test(NAME "${test_name}"
        COMMAND "${CMAKE_COMMAND}"
            "-DPROGRAM=$<TARGET_FILE:BeatnikCPP>"
            "-DSCRIPT=${script_file}"
            "-DINPUT=${input_file}"
            "-DEXPECTED=${expected}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/verify_output.cmake")
endfunction()

string(REPEAT "a" 30 SCORE_30)
string(REPEAT "a" 37 SCORE_37)
string(REPEAT "a" 66 SCORE_66)
string(REPEAT "a" 67 SCORE_67)
string(REPEAT "a" 72 SCORE_72)

# The supplied example: input A becomes H.
add_beatnik_test(TestBeatnikExample
    "Hello, aunts! Around, around, swim!" "A\n" "H")

# Commands 5 through 12: stack operations, input/output, arithmetic and duplication.
add_beatnik_test(TestBeatnikCommand5 "aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand6 "aunts K FD aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand7 "aunts ${SCORE_30} aunts ${SCORE_37} BDAA swim" "" "C")
add_beatnik_test(TestBeatnikCommand8 "Hello swim" "Z" "Z")
add_beatnik_test(TestBeatnikCommand9 "aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand10 "aunts ${SCORE_72} aunts K Q swim" "" "C")
add_beatnik_test(TestBeatnikCommand11 "aunts ${SCORE_67} aunts ${SCORE_72} Qe swim" "" "C")
add_beatnik_test(TestBeatnikCommand12 "aunts ${SCORE_67} QD swim swim" "" "CC")

# Forward conditional branches: each opcode is tested on both its taken and untaken path.
add_beatnik_test(TestBeatnikCommand13Zero
    "aunts K aunts K Q QDA a swim swim aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand13Nonzero
    "aunts K QDA a aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand14Nonzero
    "aunts K QF a swim swim aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand14Zero
    "aunts K aunts K Q QF a aunts ${SCORE_67} swim" "" "C")

# Backward branches loop over arithmetic until the tested stack value changes.
# Command 15 loops once while the counter is zero; command 16 counts down from two.
add_beatnik_test(TestBeatnikCommand15Backward
    "aunts !!! aunts A Q QD aunts !!! aunts A Q Q Qe FD QD QK QD FD aunts ${SCORE_67} swim" "" "C")
add_beatnik_test(TestBeatnikCommand16Backward
    "aunts D QD aunts A Q Qe FD QD QHD swim aunts ${SCORE_67} BDAA swim" "" "C")

# Command 17 must stop before the trailing code can print D.
add_beatnik_test(TestBeatnikCommand17
    "aunts ${SCORE_67} swim QFC aunts ${SCORE_66} swim" "" "C")

# Scores that do not map to commands are no-ops.
add_beatnik_test(TestBeatnikNoop "aunts ${SCORE_67} a swim" "" "C")