@echo off

SET MyProgram="%~1"

if %MyProgram% == "" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% input1.txt "%TEMP%\output.txt" �� ���� || goto err
fc output1.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ���� ����������
:err
echo Tests failed
exit /B 1