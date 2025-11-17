add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

set(EXPECTED_OUTPUT ".*A.*B.*C.*D.*E.*F.*A.*0.*5.*8.*10.*14.*20.*B.*16.*0.*3.*5.*9.*15.*C.*13.*18.*0.*2.*6.*12.*D.*11.*16.*19.*0.*4.*10.*E.*7.*12.*15.*17.*0.*6.*F.*1.*6.*9.*11.*15.*0.*")

add_test(NAME TestLab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_OUTPUT}")

set(EXPECTED_OUTPUT_1 ".*A.*B.*C.*D.*A.*0.*1.*3.*4.*B.*INF.*0.*2.*5.*C.*INF.*INF.*0.*3.*D.*INF.*INF.*INF.*0.*")

add_test(NAME TestLab4CPP_1 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab4CPP_1 PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_OUTPUT_1}")

set(EXPECTED_OUTPUT_2 ".*P.*Q.*R.*S.*T.*P.*0.*8.*9.*7.*5.*Q.*11.*0.*1.*4.*2.*R.*11.*19.*0.*4.*16.*S.*7.*15.*6.*0.*12.*T.*9.*3.*4.*2.*0.*")

add_test(NAME TestLab4CPP_4 COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab4CPP_4 PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_OUTPUT_2}")
