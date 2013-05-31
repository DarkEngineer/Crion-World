#include "Camera.h"

const static float STEP_SCALE = 0.1f;
const static int MARGIN = 10;

glm::vec3 cPos(1.0f, 1.0f, 1.0f);
glm::vec3 cTarget(0.0f, 0.0f, -3.5f);
glm::vec3 cUp(0.0f, 1.0f, 0.0f);

Camera *cam;

Camera::Camera()
{
}
void GLFWCALL Camera::keyWrapper(int key, int action)
{
	cam->onKeyboard(key, action);
}

void GLFWCALL Camera::mouseButtonWrapper(int button, int action)
{
	cam->onMouseButton(button, action);
}

void GLFWCALL Camera::mousePosWrapper(int x, int y)
{
	cam->onMousePos(x, y);
}
Camera::Camera(int windowWidth, int windowHeight)
{
    m_windowWidth  = windowWidth;
    m_windowHeight = windowHeight;
    m_pos          = glm::vec3(0.0f, 0.0f, 0.0f);
    m_target       = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::normalize(m_target);
    m_up           = glm::vec3(0.0f, 1.0f, 0.0f);
	deltaTime = 0.0f;
	lastTime = 0.0f;

    Init();
}
Camera::Camera(int windowWidth, int windowHeight, const glm::vec3 &Pos, const glm::vec3 & Target, const glm::vec3 &Up )
{

	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	m_pos = Pos;
	m_target = Target;
	m_target = glm::normalize(m_target);
	m_up = Up;
	m_up = glm::normalize(m_up);
	mouseSpeed = 100.0f;
	m_AngleH = 3.14f;
	m_AngleV = 0.0f;
	deltaTime = 0.0f;
	lastTime = 0.0f;

	Init();
}

void Camera::Init()
{

	m_OnUpperEdge = false;
	m_OnLowerEdge = false;
	m_OnLeftEdge = false;
	m_OnRightEdge = false;
	m_mousePos.x = m_windowWidth / 2;
	m_mousePos.y = m_windowHeight / 2;


}

const glm::vec3 & Camera::GetPos() const
{
	return m_pos;
}

const glm::vec3 & Camera::GetTarget() const
{
	return m_target;
}

const glm::vec3 & Camera::GetUp() const
{
	return m_up;
}

const glm::mat4 & Camera::GetLookAt() const
{
	return lookAtMatrix;
}

void Camera::onMouseButton(int button, int action)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			m_mousePosState = MOUSE_RIGHT_BUTTON_PRESS;
	}
	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		m_mousePosState = MOUSE_RIGHT_BUTTON_RELEASE;

}

void Camera::onMousePos(int x, int y )
{
	if(m_mousePosState == MOUSE_RIGHT_BUTTON_PRESS)
	{

		m_mouseCursorLastPos = glm::ivec2(x, y);
		glfwDisable(GLFW_MOUSE_CURSOR);
		glfwSetMousePos(m_windowWidth/2, m_windowHeight/2);
		m_AngleH += mouseSpeed * deltaTime * static_cast<float>((m_windowWidth/2 - x));
		m_AngleV += mouseSpeed * deltaTime * static_cast<float>((m_windowHeight/2 - y));
		if(m_AngleV > 90.0f)
			m_AngleV = 90.0f;
		if(m_AngleV < -90.0f)
			m_AngleV = -90.0f;
		glm::vec3 direction(cos(m_AngleV) * sin(m_AngleH), sin(m_AngleV), cos(m_AngleV) * cos(m_AngleH));
		m_target = direction;
		glm::vec3 right(sin(m_AngleH - 3.14f/2.0f), 0, cos(m_AngleH - 3.14f/2.0f));
		m_up = glm::cross(right, direction);
		bMouseLastPos = false;
	}

	if(m_mousePosState == MOUSE_RIGHT_BUTTON_RELEASE && bMouseLastPos == false)
	{
		bMouseLastPos = true;
		glfwEnable(GLFW_MOUSE_CURSOR);
		glfwSetMousePos(m_mouseCursorLastPos.x, m_mouseCursorLastPos.y);
	}  

	Update();
}

void Camera::checkFPS()
{
	double currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void Camera::setLastTime(float lastTime)
{
	this->lastTime = lastTime;
}
void Camera::onRender()
{
		Update();
}
bool Camera::onKeyboard( int Key, int action)
{
	bool Ret = false;
	if(action == GLFW_PRESS)
		switch (Key)
		{
		case GLFW_KEY_UP:
			{
				m_pos += (m_target) * deltaTime * (10 * mouseSpeed);
				Ret = true;
			} break;
		case GLFW_KEY_DOWN:
			{
				m_pos -= (m_target) * deltaTime * (10 * mouseSpeed);
				Ret = true;
			} break;
		case GLFW_KEY_LEFT:
			{
				m_pos += glm::cross(m_pos + m_target, m_up) * deltaTime * mouseSpeed;
				Ret = true;
			} break;
		case GLFW_KEY_RIGHT:
			{
				m_pos += glm::cross(m_up, m_pos + m_target) * deltaTime * mouseSpeed;
				Ret = true;
			} break;
		case 'q':
			{
				m_pos += glm::vec3(0, 1, 0) * deltaTime * mouseSpeed;
				Ret = true;
			} break;
		case 'e':
			{
				m_pos += glm::vec3(0, -1, 0) * deltaTime * mouseSpeed;
				Ret = true;
			} break;
		}
	return Ret;
}

float Camera::getDeltaTime()
{
	return deltaTime;
}

void Camera::Update()
{
	const glm::vec3 vAxis(0.0f, 1.0f, 0.0f);

	glm::vec3 view(1.0f, 0.0f, 0.0f);
	glm::quat rotationQ;
	rotationQ = glm::rotate(rotationQ, m_AngleH, vAxis);
	glm::quat conjugateQ;
	conjugateQ = glm::conjugate(rotationQ);
	view = rotationQ * view * conjugateQ;
	view = glm::normalize( view );

	glm::quat rotationQhAxis;
	glm::vec3 hAxis = glm::cross(vAxis, view);
	hAxis = glm::normalize(hAxis);
	rotationQhAxis = glm::rotate(rotationQhAxis, m_AngleV, hAxis);
	glm::quat conjugateQhAxis;
	conjugateQhAxis = glm::conjugate(rotationQhAxis);
	view = rotationQhAxis * view * conjugateQhAxis;
	m_target = view;
	m_target = glm::normalize(m_target);
	m_up = glm::cross(m_target, hAxis);
	m_up = glm::normalize(m_up);
}

Camera::~Camera()
{
	delete & m_pos;
	delete & m_target;
	delete & m_up;
    delete & m_windowWidth;
    delete & m_windowHeight;

    delete & m_AngleH;
    delete & m_AngleV;

    delete & m_OnUpperEdge;
    delete & m_OnLowerEdge;
    delete & m_OnLeftEdge;
    delete & m_OnRightEdge;

	delete & m_mousePos;
}