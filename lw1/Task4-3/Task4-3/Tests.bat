@echo off

SET MyProgram="%~1"
if %MyProgram% == "" (
	echo Please specify path to program
	exit /B 1
)

%MyProgram% > "%TEMP%\output.txt" || goto err
fc Error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

%MyProgram% crypt SrcFile.txt "%TEMP%\output.txt" 1 || goto err
fc CryptedSrcFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

%MyProgram% decrypt CryptedSrcFile.txt "%TEMP%\output.txt" 1 || goto err
fc SrcFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 passed

%MyProgram% crypt LongSrcFile.txt "%TEMP%\crypted.txt" 1 || goto err
%MyProgram% decrypt "%TEMP%\crypted.txt" "%TEMP%\decrypted.txt" 1 || goto err
fc LongSrcFile.txt "%TEMP%\decrypted.txt" > nul || goto err
echo Test 4 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Тест провалился
:err
echo Tests failed
exit /B 1