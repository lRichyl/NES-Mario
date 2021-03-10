@echo off
IF NOT EXIST build mkdir build
pushd build

cl /EHsc -W4 -wo4244 -Zi /I..\SDL\include -MP -Od ..\*.cpp /Fe"..\main.exe" /INCREMENTAL:NO /link -subsystem:windows ..\SDL\lib\SDL2.lib ..\SDL\lib\SDL2main.lib ..\SDL\lib\SDL2_image.lib shell32.lib
popd