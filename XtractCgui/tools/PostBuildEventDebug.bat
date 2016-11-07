rem Copie et renomme les fichiers lib et pdb. 
rem
rem Le nom inclue le suffixe _d pour debug.

echo.
echo Copying debug library files ...
echo.

copy "..\x64\Debug\XtractCgui.exe" "..\bin\XtractCgui_x64d.exe"
rem copy "..\x64\Debug\XtractCgui.pdb" "..\bin\XtractCgui_x64d.pdb"
