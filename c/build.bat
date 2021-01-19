gcc -o "pdmerge.dll" -shared .\pdmerge.c
gcc -L. -lpdmerge -o main.exe main.c
