@ECHO OFF
SETLOCAL
SET "sourcedir=.\build"
SET "keepfile=1.bat"
SET "keepdir=_deps"


FOR /d %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepdir%" RD /S /Q "%%a"
FOR %%a IN ("%sourcedir%\*") DO IF /i NOT "%%~nxa"=="%keepfile%" DEL "%%a"

GOTO :EOF



@pause