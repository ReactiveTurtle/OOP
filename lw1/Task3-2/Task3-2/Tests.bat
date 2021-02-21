@echo off

SET MyProgram="%~1"

if %MyProgram% == "" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% > "%TEMP%\output.txt" || goto err
fc InvalidInputFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

%MyProgram% FewLinesMatrix.txt > "%TEMP%\output.txt" || goto err
fc InvalidInputFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

%MyProgram% InvalidLineMatrix.txt > "%TEMP%\output.txt" || goto err
fc InvalidInputFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% WordMatrix.txt > "%TEMP%\output.txt" || goto err
fc InvalidInputFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 passed

%MyProgram% DegenerateMatrix.txt> "%TEMP%\output.txt" || goto err
fc ErrorDegenerate.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 passed

%MyProgram% ValidMatrix.txt> "%TEMP%\output.txt" || goto err
fc InverseValidMatrix.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Тест провалился
:err
echo Tests failed
exit /B 1