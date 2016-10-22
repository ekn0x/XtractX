rem Copie et renomme les fichiers lib et pdb. 
rem
rem Le nom inclue le suffixe _d pour debug.

echo.
echo Copying debug library files ...
echo.

copy "..\x64\Debug\XtractCcmd.exe" "..\bin\XtractCcmd_x64d.exe"
copy "..\x64\Debug\XtractCcmd.pdb" "..\bin\XtractCcmd_x64d.pdb"
