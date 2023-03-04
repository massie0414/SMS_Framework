@echo off

rem ------- 置換前・置換後の文字列を設定 -------
set TARGET=.vgm
set REPLACE_WITH=.psg
rem -----------------------------------------

for %%a in ( *.vgm ) do call :sub "%%a"

move *.psg ../data

exit /b

:sub
set FILE_NAME=%1
call set FILE_NAME=%%FILE_NAME:%TARGET%=%REPLACE_WITH%%%

echo %1 %FILE_NAME%

java -jar PSGTool.jar %1 %FILE_NAME%

goto :EOF

