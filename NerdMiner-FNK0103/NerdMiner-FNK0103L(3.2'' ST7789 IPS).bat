@echo off

:start

echo.

esptool.exe --chip esp32 --baud 921600 --before default-reset --after hard-reset --no-stub write-flash -z --flash-mode dio --flash-freq 40m --flash-size detect 0x0000 ./Bin/FNK0103L/merged_output.bin

echo.
echo press enter to continue burned!
echo.
pause

goto start