call worktime.bat START

cd PSGTool
call psg.bat
cd ../

cd Tile
call convert.bat
cd ../

del bank11.c > nul
del bank11.rel > nul
del bank11.asm > nul
del bank12.c > nul
del bank12.rel > nul
del bank12.asm > nul

assets2banks data --firstbank=11 --singleheader=assets.h --compile
assets2banks data --firstbank=11 --singleheader=assets.h

rem 計測終了
call worktime.bat STOP

rem 表示
call worktime.bat PRINT