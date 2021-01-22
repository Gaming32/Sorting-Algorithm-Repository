@REM gcc -o "pdmerge.dll" -shared .\pdmerge.c
@REM gcc -L. -lpdmerge -o main.exe main.c
gcc -L. -o main.exe main.c
