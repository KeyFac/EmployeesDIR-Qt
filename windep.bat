@echo off
if not exist WinReleaseBins mkdir WinReleaseBins
copy /Y EmployeesDIR\build\Desktop_Qt_6_11_1_MinGW_64_bit_Release\EmployeesDIR.exe WinReleaseBins\EmployeesDIR.exe
copy /Y EmployeesDIR\config.ini WinReleaseBins\
if not exist WinReleaseBins\i18n mkdir WinReleaseBins\i18n
copy /Y EmployeesDIR\EmployeesDIR_en_US.qm WinReleaseBins\i18n\
copy /Y EmployeesDIR\EmployeesDIR_zh_CN.qm WinReleaseBins\i18n\
windeployqt WinReleaseBins\EmployeesDIR.exe
echo Done.