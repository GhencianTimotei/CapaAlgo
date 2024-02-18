@echo off
setlocal

pushd %~dp0

SET pathtofolder="..\..\BuildOutput\"
rd /s /q %pathtofolder% 2>nul & popd

echo Build Output Directory Deleted 
