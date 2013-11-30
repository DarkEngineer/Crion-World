Crion-World
===========

3D adventure game made with c++ and OpenGL

How to make a build
===================

You need to have on your computer Visual Studio 2012 Express or better, either Eclipse will be fine. Also you need assimp, FreeImage, GLFW, GLM. This libraries are included into project to help you better! 

Configurations on Visual Studio 2012 Express
==============
Project Properties -> Configuration Properties -> Include Directories: $(ProjectDir)include;$(IncludePath)

Project Properties -> Configuration Properties -> Library Directories: $(ProjectDir)lib\assimp\release;$(ProjectDir)lib\SOIL;$(ProjectDir)lib\FreeImage;$(ProjectDir)dll;$(ProjectDir)lib\GL;$(ProjectDir)lib\FreeType;$(LibraryPath)

Project Properties -> Configuration Properties -> C/C++ -> Preprocessor: GLFW_BUILD_DLL;SOIL;WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

Project Properties -> Configuration Properties -> Linker -> Input: opengl32.lib;glu32.lib;glut32.lib;glfw3dll.lib;glew32.lib;glew32mx.lib;FreeImage.lib;SOIL.lib;assimp.lib;%(AdditionalDependencies)

DLLs: freeglut.dll, FreeImage.dll, glew32.dll, glew32d.dll, SOIL.dll, glew32mx.dll, GLFW.dll, glut32.dll, 


