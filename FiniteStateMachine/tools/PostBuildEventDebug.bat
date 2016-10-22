rem Copie et renomme les fichiers lib et pdb. 
rem
rem Le nom inclue le suffixe _d pour debug.

echo.
echo Copying debug library files ...
echo.

copy "..\x64\Debug\FiniteStateMachine.lib" "..\lib\FiniteStateMachine_x64d.lib"
copy "..\x64\Debug\FiniteStateMachine.pdb" "..\lib\FiniteStateMachine_x64d.pdb"