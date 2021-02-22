@echo off

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

%MyProgram% ShortText.txt "%TEMP%\output.txt" two twotwo || goto err
fc ShortText_two_twotwo.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" two "" || goto err
fc ShortText_two_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" two > nul && goto err
echo Test 5 passed

%MyProgram% ShortText.txt "%TEMP%\output.txt" > nul && goto err
echo Test 6 passed

%MyProgram% > nul && goto err
echo Test 7 passed

%MyProgram% LongText_I_You.txt "%TEMP%\output.txt" I You || goto err
fc LongText_I_You_Result.txt "%TEMP%\output.txt" > nul || goto err
echo Test 8 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Тест провалился
:err
echo Tests failed
exit /B 1