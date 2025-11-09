add_test(NAME TruthMachine COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/truthMachineScript.txt ${CMAKE_CURRENT_SOURCE_DIR}/truthMachineInputData.txt)

set_tests_properties(TruthMachine PROPERTIES 
	PASS_REGULAR_EXPRESSION "0"
)

add_test(NAME AlphabetProgram COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/alphabetProgramScript.txt ${CMAKE_CURRENT_SOURCE_DIR}/alphabetProgramInputData.txt)

set(ALPHABET " !\"#\\$%&'\\(\\)\\*\\+,\\-\\./0123456789:;<=>\\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\\[\\\\\\]\\^_\\`abcdefghijklmnopqrstuvwxyz\\{\\|\\}~")

set_tests_properties(AlphabetProgram PROPERTIES 
	PASS_REGULAR_EXPRESSION "^${ALPHABET}\$"
)

add_test(NAME Rudimentary COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/rudimentaryExampleScript.txt ${CMAKE_CURRENT_SOURCE_DIR}/rudimentaryExampleInputData.txt)

set_tests_properties(Rudimentary PROPERTIES 
	PASS_REGULAR_EXPRESSION "H"
)

add_test(NAME HelloWorld COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/helloWorldScript.txt ${CMAKE_CURRENT_SOURCE_DIR}/helloWorldScript.txt)

set_tests_properties(HelloWorld PROPERTIES 
	PASS_REGULAR_EXPRESSION "Hello, world!"
)