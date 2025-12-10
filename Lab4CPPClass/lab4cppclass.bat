REM сборка Debug
REM cmake --build . --config Debug
REM ctest -C Debug -V
REM Или сборка Release
REM cmake --build . --config Release
REM ctest -C Release -V  
REM ctest -C RelWithDebInfo -V
REM
REM
REM
cd C:\Users\admin\Algorithms\build
cmake ..
cmake --build . --config RelWithDebInfo
ctest -C RelWithDebInfo --output-on-failure
