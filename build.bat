call worktime.bat START

del *.sms > nul
del main.rel > nul
del banked_code_1rel > nul
del banked_code_2.rel > nul
del banked_code_3.rel > nul
del banked_code_4.rel > nul
del banked_code_5.rel > nul
del banked_code_6.rel > nul
del banked_code_7.rel > nul
del banked_code_8.rel > nul
del banked_code_9.rel > nul
del banked_code_10.rel > nul
del bank11.rel > nul

sdcc -c -mz80 --codeseg BANK1 banked_code_1.c
sdcc -c -mz80 --codeseg BANK2 banked_code_2.c
sdcc -c -mz80 --codeseg BANK3 banked_code_3.c
sdcc -c -mz80 --codeseg BANK4 banked_code_4.c
sdcc -c -mz80 --codeseg BANK5 banked_code_5.c
sdcc -c -mz80 --codeseg BANK6 banked_code_6.c
sdcc -c -mz80 --codeseg BANK7 banked_code_7.c
sdcc -c -mz80 --codeseg BANK8 banked_code_8.c
sdcc -c -mz80 --codeseg BANK9 banked_code_9.c
sdcc -c -mz80 --codeseg BANK10 banked_code_10.c
sdcc -c -mz80 --constseg DATABANK11 bank11.c

sdcc -c -mz80 --peep-file peep-rules.txt main.c

sdcc ^
 -o project.ihx ^
 -mz80 ^
 --no-std-crt0 ^
 --data-loc 0xC000 ^
 -Wl-b_BANK1=0x14000  ^
 -Wl-b_BANK2=0x24000  ^
 -Wl-b_BANK3=0x34000  ^
 -Wl-b_BANK4=0x44000  ^
 -Wl-b_BANK5=0x54000  ^
 -Wl-b_BANK6=0x64000  ^
 -Wl-b_BANK7=0x74000  ^
 -Wl-b_BANK8=0x84000  ^
 -Wl-b_BANK9=0x94000  ^
 -Wl-b_BANK10=0xA4000  ^
 -Wl-b_DATABANK11=0xB8000  ^
 crt0_sms.rel ^
 SMSlib.lib ^
 PSGlib.rel ^
 main.rel ^
 banked_code_1.rel ^
 banked_code_2.rel ^
 banked_code_3.rel ^
 banked_code_4.rel ^
 banked_code_5.rel ^
 banked_code_6.rel ^
 banked_code_7.rel ^
 banked_code_8.rel ^
 banked_code_9.rel ^
 banked_code_10.rel ^
 bank11.rel

makesms project.ihx project.sms

del *.asm > nul
del *.ihx > nul
del *.lk > nul
del *.lst > nul
del *.map > nul
del *.noi > nul
del *.sym > nul
rem del *.rel > nul ←消してはいけないファイルが含まれてしまう
del main.rel > nul
del banked_code_1.rel > nul
del banked_code_2.rel > nul
del banked_code_3.rel > nul
del banked_code_4.rel > nul
del banked_code_5.rel > nul
del banked_code_6.rel > nul
del banked_code_7.rel > nul
del banked_code_8.rel > nul
del banked_code_9.rel > nul
del banked_code_10.rel > nul
del bank11.rel > nul

rem 計測終了
call worktime.bat STOP

rem 表示
call worktime.bat PRINT