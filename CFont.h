#include "game.h"
#include "include\FreeType\freetype\freetype.h"

class CFont
{
public:
	bool loadFont(std::string sFile, int iPXSize);
	bool loadSystemFont(std::string sName, int iPXSize);

	int getTextWidth(std::string sText, int iPXSize);

	void print(std::string sText, int x, int y, int iPXSize = -1);

	void releaseFont();

	void setShaderProgram( GLuint * a_shShaderProgram);

	CFont();
private:
	void createChar(int iIndex);

	GLuint tCharTextures[256];
	int iAdvX[256], iAdvY[256];
	int iBearingX[256], iBearingY[256];
	int iCharWidth[256], iCharHeight[256];
	int iLoadedPixelSize, iNewLine;

	bool bLoaded;

	GLuint uiVAO;
	GLuint vboData;

	FT_Library ftLib;
	FT_Face ftFace;
	GLuint * shaderProgram;

};