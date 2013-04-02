#ifndef Camera_h
#define Camera_h
#include <GL\glew.h>
#include <GL\glfw.h>
#include <math.h>
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

const double M_PI = 3.14159265359;
#define toRadian(x) ((x) * M_PI / 180.0f)
#define toDegree(x) ((x) * 180.0f / M_PI)

class Camera
{
	
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_up;

	void Init();
    void Update();

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

	glm::ivec2 m_mousePos;

public:
	Camera();
	Camera(int windowWidth, int windowHeight);
	Camera(int windowWidth, int windowHeight, const glm::vec3 &Pos, const glm::vec3 & Target, const glm::vec3 &Up );
	bool onKeyboard( int Key );
	void onMouse( int x, int y );
	void onRender();
	const glm::vec3 & GetPos() const;
	const glm::vec3 & GetTarget() const;
	const glm::vec3 & GetUp() const;
	~Camera();
};

#endif