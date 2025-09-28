cd c:\Users\admin\Algorithms\StepanovLab1\Test\build
cmake ..
REM сборка Debug
REM cmake --build . --config Debug
REM ctest -C Debug -V
REM Или сборка Release
REM
cmake --build . --config Release  
ctest -C Release -V