@echo off
echo ========================================
echo COMPILATION DE TOUS LES ALGORITHMES
echo ========================================
echo.

echo [1/6] Compilation de tri_bulles.c...
gcc -o tri_bulles.exe algos/tri_bulles.c
if %errorlevel% neq 0 goto error

echo [2/6] Compilation de tri_bulles_opt.c...
gcc -o tri_bulles_opt.exe algos/tri_bulles_opt.c
if %errorlevel% neq 0 goto error

echo [3/6] Compilation de tri_gnome.c...
gcc -o tri_gnome.exe algos/tri_gnome.c
if %errorlevel% neq 0 goto error

echo [4/6] Compilation de tri_distribution.c...
gcc -o tri_distribution.exe algos/tri_distribution.c
if %errorlevel% neq 0 goto error

echo [5/6] Compilation de tri_rapide.c...
gcc -o tri_rapide.exe algos/tri_rapide.c
if %errorlevel% neq 0 goto error

echo [6/6] Compilation de tri_tas.c...
gcc -o tri_tas.exe algos/tri_tas.c
if %errorlevel% neq 0 goto error

echo.
echo ========================================
echo COMPILATION TERMINEE AVEC SUCCES !
echo ========================================
echo.
goto end

:error
echo.
echo ERREUR lors de la compilation !
pause
exit /b 1

:end
