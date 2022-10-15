REM https://stackoverflow.com/questions/41934215/batch-file-get-filename-from-directory-and-save-as-variable
@echo off
REM setlocal
set "yourDir=%~dp0"
set "yourExt=*UNO.hex"
rem set filename=''
pushd %yourDir%
for %%a in (%yourExt%) do (
	REM C:\Users\Administrator\Desktop\arduino_board/HEX_UNO.bat %%a
	set "filename=%%a"
	echo !filename!
	echo %%a
	echo %filename%
	
	Goto upload_uno
REM for %%a in (%yourExt%) do echo %%a
)

echo not detect file hex for Uno

set /p DUMMY=Hit ENTER to continue...

:upload_uno
REM for %%a in (%yourExt%) do (
REM REM Do stuff with %%a here
REM Set filename=%%a
REM echo !filename!
REM echo !filename:~0,6!
REM echo !filename:a=b!
REM )

popd
REM endlocal

echo %filename%

D:\arduino_board\avr_tool_upload/HEX_UNO.bat %filename%
set /p DUMMY=Hit ENTER to continue...