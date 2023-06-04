@echo off

set TARGET=.vgm
set REPLACE_WITH=.psg

for %%a in ( *.vgm ) do call :sub "%%a"

rem echo ok.vgm ok.psg 2
rem vgm2psg.exe ok.vgm ok.psg 2
java -jar PSGTool.jar ok.vgm ok.psg 2

move *.psg ../data

exit /b

:sub
set FILE_NAME=%1
call set FILE_NAME=%%FILE_NAME:%TARGET%=%REPLACE_WITH%%%

echo %1 %FILE_NAME%

java -jar PSGTool.jar %1 %FILE_NAME%
rem vgm2psg.exe %1 %FILE_NAME%

goto :EOF

