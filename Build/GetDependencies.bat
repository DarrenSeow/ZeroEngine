echo OFF
rem ------------------------
rem stb dependencies
rem -----------------------
rmdir "../Bin/stb" /S /Q
git clone https://github.com/nothings/stb "../Bin/stb"

rem ------------------------
rem tinyobjloader dependencies
rem -----------------------
rmdir "../Bin/tinyobjloader" /S /Q
git clone https://github.com/tinyobjloader/tinyobjloader.git "../Bin/tinyobjloader"

rem ------------------------
rem glm dependencies
rem -----------------------

rmdir "../Bin/glm" /S /Q
git clone https://github.com/g-truc/glm "../Bin/glm"