#ifndef Camera_h
#define Camera_h
#include <GL\glew.h>
#include <GL\glfw.h>
#include <math.h>
#include <glm\glm.hpp>
#include <iostream>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>

#define M_PI 3.14159265358979323846
#define toRadian(x) ((x) * M_PI / 180.0f)
#define toDegree(x) ((x) * 180.0f / M_PI)



class Camera
{
	float deltaTime; // delta time for moving
	float lastTime;
	//camera basic details
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::vec3 m_right;

	glm::mat4 lookAtMatrix;

	void Init();
    void Update();

    int m_windowWidth;
    int m_windowHeight;

	// horizontal and vertical angles which are used for moving camera
    float m_AngleH;
    float m_AngleV;

	//boolean variables 
    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

	glm::ivec2 m_mousePos; 

	enum
	{
		MOUSE_RIGHT_BUTTON_RELEASE,
		MOUSE_RIGHT_BUTTON_PRESS
	} m_mousePosState; 	//enum used for set button states

	struct
	{
		glm::ivec2 m_mouseCursorLastPos; 	// mouse last position before set mouse coordinations to screen center
		glm::ivec2 m_mouseCursorCurrentPos; // mouse current position
		bool bMouseLastPos;
		float mouseSpeed;
	};
public:
	Camera();
	Camera(int windowWidth, int windowHeight);
	Camera(int windowWidth, int windowHeight, const glm::vec3 &Pos, const glm::vec3 & Target, const glm::vec3 &Up );

	bool onKeyboard( int key, int action );
	void onMouseButton(int button, int action);
	void onMousePos(int x, int y );
	void onRender();
		
	static void GLFWCALL keyWrapper(int key, int action);
	static void GLFWCALL mouseButtonWrapper(int button, int action);
	static void GLFWCALL mousePosWrapper(int x, int y);

	float getDeltaTime();
	void checkFPS();
	void setLastTime(float lastTime);


	const glm::vec3 & GetPos() const;
	const glm::vec3 & GetTarget() const;
	const glm::vec3 & GetUp() const;
	const glm::mat4 & GetLookAt() const;
	virtual ~Camera();
};

extern Camera *cam;
	
#endif