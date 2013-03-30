TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS+=-lGLEW -lassimp -lGL -lglfw -lfreeimage -lGLU

HEADERS += \
    Technique.h \
    Shader.h \
    Pipeline.h \
    Mesh.h \
    LightingTechnique.h \
    glFreeImage.h \
    GameIntro.h \
    game.h \
    Camera.h \
    includes.h \
    Textures.h

SOURCES += \
    Technique.cpp \
    Shader.cpp \
    Pipeline.cpp \
    Mesh.cpp \
    main.cpp \
    LightingTechnique.cpp \
    glFreeImage.cpp \
    GameIntro.cpp \
    game.cpp \
    Camera.cpp \
    Textures.cpp
