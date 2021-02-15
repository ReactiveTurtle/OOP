@echo off

SET MyProgram="%~1"
SET MaxInt=2147483647
SET MinInt=-2147483648

if %MyProgram% == "" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% 10 16 3Z > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

%MyProgram% "" "" "" > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

%MyProgram% 10 "" "" > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% 10 16 "" > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

REM Проверка граничных значений Integer
%MyProgram% 10 2 (%MaxInt% + 1) > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

%MyProgram% 10 2 (%MinInt% - 1) > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

%MyProgram% 16 10 (%MaxInt% + 1) > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 passed

%MyProgram% 16 10 (%MinInt% - 1) > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 8 passed

%MyProgram% (%MaxInt% + 1) 10 543210 > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 9 passed

%MyProgram% (%MinInt% - 1) 10 543210 > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 10 passed

REM Проверка граничных значений возможных систем счисления
%MyProgram% 37 10 543210 > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 11 passed

%MyProgram% 1 10 543210 > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 12 passed

%MyProgram% 10 36 543239 > "%TEMP%\output.txt" || goto err
fc 10_36_543239.txt "%TEMP%\output.txt" > nul || goto err
echo Test 13 passed

%MyProgram% 36 10 BN5Z > "%TEMP%\output.txt" || goto err
fc 36_10_BN5Z.txt "%TEMP%\output.txt" > nul || goto err
echo Test 14 passed

REM Проверка нехватки аргументов
%MyProgram% 10 16 > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 15 passed

REM Преобразование
%MyProgram% 10 16 3Z > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 16 passed

%MyProgram% 10 16 31 > "%TEMP%\output.txt" || goto err
fc 10_16_31.txt "%TEMP%\output.txt" > nul || goto err
echo Test 17 passed

%MyProgram% 10 16 543210 > "%TEMP%\output.txt" || goto err
fc 10_16_543210.txt "%TEMP%\output.txt" > nul || goto err
echo Test 18 passed

%MyProgram% 16 10 849EA > "%TEMP%\output.txt" || goto err
fc 16_10_849EA.txt "%TEMP%\output.txt" > nul || goto err
echo Test 19 passed

%MyProgram% 16 2 849EA > "%TEMP%\output.txt" || goto err
fc 16_2_849EA.txt "%TEMP%\output.txt" > nul || goto err
echo Test 20 passed

%MyProgram% 10 16 -543210 > "%TEMP%\output.txt" || goto err
fc 10_16_minus543210.txt "%TEMP%\output.txt" > nul || goto err
echo Test 21 passed

%MyProgram% 16 2 -849EA > "%TEMP%\output.txt" || goto err
fc 10_2_minus849EA.txt "%TEMP%\output.txt" > nul || goto err
echo Test 22 passed

%MyProgram% 16 2 0 > "%TEMP%\output.txt" || goto err
fc 16_2_0.txt "%TEMP%\output.txt" > nul || goto err
echo Test 23 passed

%MyProgram% 2 16 110000100100111101010 > "%TEMP%\output.txt" || goto err
fc 2_16_110000100100111101010.txt "%TEMP%\output.txt" > nul || goto err
echo Test 24 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Тест провалился
:err
echo Tests failed
exit /B 1