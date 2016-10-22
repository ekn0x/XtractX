rem Copie le fichier lib. 
rem
rem Il ne devrait pas y avoir de collistion avec le fichier debug puisque ce 
rem dernier a été renomé avec le suffixe _d pour debug.

echo.
echo Copying release library file ...
echo.

copy "..\x64\Release\XtractCgui.exe" "..\bin\XtractCgui_x64.exe"
copy "..\x64\Release\XtractCgui.pdb" "..\bin\XtractCgui_x64.pdb"
