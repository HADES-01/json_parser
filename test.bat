@REM @ECHO OFF
cmake  -G "MinGW Makefiles" -S . -B build
cmake --build build
ctest --test-dir build/tests
