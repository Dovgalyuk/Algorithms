add_executable(LabFloydCPPTemplate task.cpp)
target_include_directories(LabFloydCPPTemplate PUBLIC ../LibraryCPPTemplate)
#target_link_libraries(LabFloydCPPTemplate LibraryCPPTemplate)

add_test(NAME TestFloyd1 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/example.txt)
set_property(TEST TestFloyd1 PROPERTY PASS_REGULAR_EXPRESSION "A -> C: 5")

add_test(NAME TestFloyd2 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input1.txt)
set_property(TEST TestFloyd2 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A
A -> B: 3. A -> B
A -> C: 5. A -> B -> C
A -> D: 6. A -> B -> C -> D
B -> A: 7. B -> C -> D -> A
B -> B: 0. B
B -> C: 2. B -> C
B -> D: 3. B -> C -> D
C -> A: 5. C -> D -> A
C -> B: 8. C -> D -> A -> B
C -> C: 0. C
C -> D: 1. C -> D
D -> A: 4. D -> A
D -> B: 7. D -> A -> B
D -> C: 9. D -> A -> B -> C
D -> D: 0. D")

add_test(NAME TestFloyd3 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input2.txt)
set_property(TEST TestFloyd3 PROPERTY PASS_REGULAR_EXPRESSION "X -> X: 0. X
X -> Y: 2. X -> Y
X -> Z: INF
Y -> X: INF
Y -> Y: 0. Y
Y -> Z: INF
Z -> X: INF
Z -> Y: INF
Z -> Z: 0. Z")

add_test(NAME TestFloyd4 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input3.txt)
set_property(TEST TestFloyd4 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A
A -> B: 5. A -> B
A -> C: 3. A -> B -> C
B -> A: INF
B -> B: 0. B
B -> C: -2. B -> C
C -> A: INF
C -> B: INF
C -> C: 0. C")

add_test(NAME TestFloyd5 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input4.txt)
set_property(TEST TestFloyd5 PROPERTY PASS_REGULAR_EXPRESSION "Negative cycle detected")

add_test(NAME TestFloyd6 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input5.txt)
set_property(TEST TestFloyd6 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A")

add_test(NAME TestFloyd7 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input6.txt)
set_property(TEST TestFloyd7 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A
A -> B: INF
A -> C: INF
B -> A: INF
B -> B: 0. B
B -> C: INF
C -> A: INF
C -> B: INF
C -> C: 0. C")

add_test(NAME TestFloyd8 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input7.txt)
set_property(TEST TestFloyd8 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A
A -> B: 3. A -> B
B -> A: INF
B -> B: 0. B")

add_test(NAME TestFloyd9 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input8.txt)
set_property(TEST TestFloyd9 PROPERTY PASS_REGULAR_EXPRESSION "A -> A: 0. A
A -> B: 2. A -> B
B -> A: INF
B -> B: 0. B")

add_test(NAME TestFloyd10 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input9.txt)
set_property(TEST TestFloyd10 PROPERTY PASS_REGULAR_EXPRESSION "Moscow -> Moscow: 0. Moscow
Moscow -> Kazan: 3. Moscow -> Kazan
Moscow -> Samara: 7. Moscow -> Kazan -> Samara
Moscow -> Ufa: 9. Moscow -> Kazan -> Samara -> Ufa
Moscow -> Omsk: 14. Moscow -> Kazan -> Samara -> Ufa -> Omsk
Moscow -> Perm: 8. Moscow -> Perm
Kazan -> Moscow: INF
Kazan -> Kazan: 0. Kazan
Kazan -> Samara: 4. Kazan -> Samara
Kazan -> Ufa: 6. Kazan -> Samara -> Ufa
Kazan -> Omsk: 11. Kazan -> Samara -> Ufa -> Omsk
Kazan -> Perm: INF
Samara -> Moscow: INF
Samara -> Kazan: INF
Samara -> Samara: 0. Samara
Samara -> Ufa: 2. Samara -> Ufa
Samara -> Omsk: 7. Samara -> Ufa -> Omsk
Samara -> Perm: INF
Ufa -> Moscow: INF
Ufa -> Kazan: INF
Ufa -> Samara: INF
Ufa -> Ufa: 0. Ufa
Ufa -> Omsk: 5. Ufa -> Omsk
Ufa -> Perm: INF
Omsk -> Moscow: INF
Omsk -> Kazan: INF
Omsk -> Samara: INF
Omsk -> Ufa: INF
Omsk -> Omsk: 0. Omsk
Omsk -> Perm: INF
Perm -> Moscow: INF
Perm -> Kazan: INF
Perm -> Samara: INF
Perm -> Ufa: INF
Perm -> Omsk: 15. Perm -> Omsk
Perm -> Perm: 0. Perm")

add_test(NAME TestFloyd11 COMMAND LabFloydCPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_input10.txt)
set_property(TEST TestFloyd11 PROPERTY PASS_REGULAR_EXPRESSION "Invalid graph description")