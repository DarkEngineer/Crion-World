#include "Camera.h"

const static float STEP_SCALE = 0.1f;
const static int MARGIN = 10;

Camera::Camera(int windowWidth, int windowHeight)
{
    m_windowWidth  = windowWidth;
    m_windowHeight = windowHeight;
    m_pos          = glm::vec3(0.0f, 0.0f, 0.0f);
    m_target       = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::normalize(m_target);
    m_up           = glm::vec3(0.0f, 1.0f, 0.0f);

    Init();
}
Camera::Camera(int windowWidth, int windowHeight, const glm::vec3 &Pos, const glm::vec3 & Target, const glm::vec3 &Up )
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	m_pos = Pos;
	m_target = Target;
	glm::normalize(m_target);
	m_up = Up;
	glm::normalize(m_up);

	Init();
}

void Camera::Init()
{
	glm::vec3 hTarget(m_target.x, 0.0f, m_target.z);
	glm::normalize(hTarget);

	if( hTarget.z >= 0.0f)
	{
		if(hTarget.x >= 0.0f)
			m_AngleH = 360.0f - toDegree( glm::asin(hTarget.z) );
		else
			m_AngleH = 180.0f + toDegree( glm::asin(hTarget.z) );
	}
	else
	{
		if(hTarget.x >= 0.0f)
			m_AngleH = toDegree(glm::asin(-hTarget.z));
		else
			m_AngleH = 90.0f + toDegree(glm::asin(-hTarget.z) );
	}

	m_AngleV = -toDegree(glm::asin(m_target.y));

	m_OnUpperEdge = false;
	m_OnLowerEdge = false;
	m_OnLeftEdge = false;
	m_OnRightEdge = false;
	m_mousePos.x = m_windowWidth / 2;
	m_mousePos.y = m_windowHeight / 2;

	glfwSetMousePos(m_mousePos.x, m_mousePos.y);
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

void Camera::onMouse( int x, int y )
{
	const int deltaX = x - m_mousePos.x;
	const int deltaY = y - m_mousePos.y;

	m_mousePos.x = x;
	m_mousePos.y = y;

	m_AngleH += static_cast<float>(deltaX) / 20.0f;
	m_AngleH += static_cast<float>(deltaY) / 20.0f;

	if( deltaX == 0 )
	{
		if( x <= MARGIN )
			m_OnLeftEdge = true;
		else if( x >= (m_windowWidth - MARGIN) )
			m_OnRightEdge = true;
	}
	else
	{
		m_OnLeftEdge = false;
		m_OnRightEdge = false;
	}

	if( deltaY == 0)
	{
		if( y <= MARGIN )
			m_OnUpperEdge = true;
		else if( y >= (m_windowHeight -	MARGIN) )
			m_OnLowerEdge = true;
	}
	else
	{
		m_OnUpperEdge = false;
		m_OnLowerEdge = false;
	}

	Update();
}

void Camera::onRender()
{
	bool shouldUpdate = false;

	if(m_OnLeftEdge = true)
	{
		m_AngleH -= 0.1f;
		shouldUpdate = true;
	}
	else if(m_OnRightEdge) 
	{
		m_AngleH += 0.1f;
		shouldUpdate = true;
	}

	if(m_OnUpperEdge)
	{
		if(m_AngleV > - 90.0f)
		{
			m_AngleV -= 0.1f;
			shouldUpdate = true;
		}
	}
	else if(m_OnLowerEdge)
	{
		if(m_AngleV < 90.0f)
		{
			m_AngleV += 0.1f;
			shouldUpdate = true;
		}
	}

	if(shouldUpdate)
		Update();
}
bool Camera::onKeyboard( int Key )
{
	bool Ret = false;

	switch (Key)
	{
	case GLFW_KEY_UP:
		{
			m_pos += (m_target * STEP_SCALE );
			Ret = true;
		} break;
	case GLFW_KEY_DOWN:
		{
			m_pos -= (m_target * STEP_SCALE );
			Ret = true;
		} break;
	case GLFW_KEY_LEFT:
		{
			glm::vec3 left = glm::cross(m_target, m_up );
			glm::normalize(left);
			left *= STEP_SCALE;
			m_pos += left;
			Ret = true;
		} break;
	case GLFW_KEY_RIGHT:
		{
			glm::vec3 right = glm::cross(m_up, m_target);
			glm::normalize(right);
			right *= STEP_SCALE;
			m_pos += right;
			Ret = true;
		} break;
	}
	return Ret;
}

void Camera::Update()
{
	const glm::vec3 vAxis(0.0f, 1.0f, 0.0f);

	glm::vec3 view(1.0f, 0.0f, 0.0f);
	glm::rotate(m_AngleH, vAxis);
	glm::normalize( view );

	glm::vec3 hAxis = glm::cross(vAxis, view);
	glm::normalize(hAxis);

	m_target = view;
	glm::normalize(m_target);

	m_up = glm::cross(m_target, hAxis);
	glm::normalize(m_up);
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
