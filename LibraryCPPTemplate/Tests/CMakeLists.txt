add_executable(TestStringCPPTemplate str.cpp)
target_include_directories(TestStringCPPTemplate PUBLIC ..)
add_test(TestStringCPPTemplate TestStringCPPTemplate)

