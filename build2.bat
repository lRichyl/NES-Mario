@echo off
IF NOT EXIST build mkdir build
pushd build

cl /EHsc -w -wo4244 -Zi /I..\SDL\include -MP -O2 ..\*.cpp /Fe"..\main.exe" /INCREMENTAL:NO /link -subsystem:console ..\SDL\lib\SDL2.lib ..\SDL\lib\SDL2main.lib ..\SDL\lib\SDL2_image.lib ..\SDL\lib\SDL2_mixer.lib shell32.lib
popd
