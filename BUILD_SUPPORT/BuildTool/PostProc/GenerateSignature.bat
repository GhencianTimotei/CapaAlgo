@echo off
attrib -r %~dp0\out\*.*
echo python vag_swdl_files_create.py -i %~dp0\..\..\BuildOutput\S32K_NoPDL.hex -b 0x50 -f3
python vag_swdl_files_create.py -i %~dp0\..\..\BuildOutput\S32K_NoPDL.hex -b 0x50 -f3