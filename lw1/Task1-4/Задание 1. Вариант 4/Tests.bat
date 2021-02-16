REM @echo off

SET MyProgram="%~1"

if %MyProgram% == "" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% Empty.txt "%TEMP%\output.txt" two you || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" "" you || goto err
fc ShortText.txt "%TEMP%\output.txt" > null || goto err
echo Test 2 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" two you || goto err
fc ShortText_two_you.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" two "" || goto err
fc ShortText_two_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" two > "%TEMP%\error.txt" || goto err
fc Error.txt "%TEMP%\error.txt" > nul || goto err
echo Test 5 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" > "%TEMP%\error.txt" || goto err
fc Error.txt "%TEMP%\error.txt" > nul || goto err
echo Test 6 passed

%MyProgram% > "%TEMP%\error.txt" || goto err
fc Error.txt "%TEMP%\error.txt" > nul || goto err
echo Test 7 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Тест провалился
:err
echo Tests failed
exit /B 1