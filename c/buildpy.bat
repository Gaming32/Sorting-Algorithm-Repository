@REM gcc -o "pdmerge.dll" -shared .\pdmerge.c
@REM gcc -L. -lpdmerge -o main.exe main.c
gcc -L. -lpython39 -shared -o pysorting.pyd pysorting.c
