@echo off
setlocal
SET MODULE=%1
SET PATH=%PATH%;C:\Program Files\7-Zip\;c:\Program Files (x86)\7-Zip\;c:\python27\

SET COMPILER_PATH=c:\Program Files (x86)\IAR Systems\Embedded Workbench 8.1\arm\bin\;c:\Program Files (x86)\IAR Systems\Embedded Workbench 8.2 ARM 8.32.4\;%COMPILER_PATH%;

pushd %~dp0

rem ========================= Checking\Unziping Build Tool ================================

IF NOT EXIST %cd%\scons ( GOTO :Unzip ) ELSE (GOTO :Build)
:Unzip
echo Scons folder not present - Unziping now: 
7z.exe x scons.zip

:Build

echo .&echo.==========================Building Output======================================

python scons/scons.py -Q --site-dir scons/site_scons %cd%/../../../%MODULE%

echo Exit code of SCons is: %errorlevel%
SET jenkinsErrorLevel=%errorlevel%

popd


echo Jenkins error level: %jenkinsErrorLevel%
if %jenkinsErrorLevel% == 0 (
	SET errorlevel=0)
if %jenkinsErrorLevel% NEQ "0" (
	SET errorlevel=%jenkinsErrorLevel%)

echo Done with build.bat 

echo Exit erorr level: %errorlevel%
exit /b %errorlevel%

endlocal