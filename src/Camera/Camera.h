#ifndef Camera_h
#define Camera_h
#include <GL\glew.h>
#include <GL\glfw.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\glm.hpp>
#include <iostream>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\quaternion.hpp>




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
		RELEASE,
		PRESS
	} rmb_state; 	//enum used for set button states

	struct
	{
		glm::ivec2 lastPos; 	// mouse last position before set mouse coordinations to screen center
		glm::ivec2 currentPos; // mouse current position
		bool updatePos;
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