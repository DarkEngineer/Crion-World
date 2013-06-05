#include "Pipeline.h"

Pipeline * pipeline;

Pipeline::Pipeline()
{
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_worldPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotateInfo = glm::vec3(0.0f, 0.0f, 0.0f);
	m_persProj.FOV = 60.0f;
	m_persProj.width = 800.0f;
	m_persProj.height = 600.0f;
	m_persProj.zNear = 0.001f;
	m_persProj.zFar = 100.0f;
}

Pipeline::~Pipeline()
{
	delete m_camera;
}

Camera * Pipeline::getCamera()
{
	return m_camera;
}
void Pipeline::scale(float scaleX, float scaleY, float scaleZ)
{
	m_scale.x = scaleX;
	m_scale.y = scaleY;
	m_scale.z = scaleZ;
}

void Pipeline::worldPos(float x, float y, float z)
{
	m_worldPos.x = x;
	m_worldPos.y = y;
	m_worldPos.z = z;
}

void Pipeline::rotate( float rotateX, float rotateY, float rotateZ)
{
	m_rotateInfo.x = rotateX;
	m_rotateInfo.y = rotateY;
	m_rotateInfo.z = rotateZ;
}

void Pipeline::setPerspectiveProj(float FOV, float width, float height, float zNear, float zFar)
{
	m_persProj.FOV = FOV;
	m_persProj.width = width;
	m_persProj.height = height;
	m_persProj.zNear = zNear;
	m_persProj.zFar = zFar;
}

void Pipeline::init()
{
	m_camera->setLastTime(static_cast<float>(glfwGetTime()));
}

// have to be implemented after setPerspectiveProj
void Pipeline::setCamera(const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up) 
{
	m_camera = new Camera(static_cast<int>(m_persProj.width), static_cast<int>(m_persProj.height), pos, target, up);
}

void Pipeline::setCamera(const int & windowWidth, const int & windowHeight)
{
	m_camera = new Camera(windowWidth, windowHeight);
}

void Pipeline::render()
{
	m_camera->onRender();
}

void Pipeline::initScaleTransform(glm::mat4 &m) const
{
	m = glm::mat4(m_scale.x, 0.0f,		0.0f,		0.0f,
				  0.0f,		 m_scale.y, 0.0f,		0.0f,
				  0.0f,		 0.0f,		m_scale.z,  0.0f,
				  0.0f,		 0.0f,		0.0f,		1.0f);
}

void Pipeline::initRotateTransform(glm::mat4 &m) const
{
	glm::mat4 r1, r2, r3;

	const float x = static_cast<float>((m_rotateInfo.x * M_PI) / 180.0f); 
	const float y = static_cast<float>((m_rotateInfo.y * M_PI) / 180.0f);
	const float z = static_cast<float>((m_rotateInfo.z * M_PI) / 180.0f);

	r1 = glm::mat4(1.0f, 0.0f,	   0.0f,	0.0f,
				   0.0f, cosf(x), -sinf(x), 0.0f,
				   0.0f, sinf(x),  cosf(x), 0.0f,
				   0.0f, 0.0f,	   0.0f,	1.0f);

	r2 = glm::mat4(cosf(y), 0.0f, -sinf(y), 0.0f,
				   0.0f,	1.0f,  0.0f,	0.0f,
				   sinf(y), 0.0f,  cosf(y), 0.0f,
				   0.0f,	0.0f,  0.0f,	1.0f);

	r3 = glm::mat4(cosf(z), -sinf(z), 0.0f, 0.0f,
				   sinf(z),  cosf(z), 0.0f, 0.0f,
				   0.0f,	 0.0f,	  1.0f, 0.0f,
				   0.0f,	 0.0f,	  0.0f, 1.0f);

	m = r3 * r2 * r1;
}

void Pipeline::initTranslateTransform(glm::mat4 &m) const
{
	m = glm::mat4(1.0f, 0.0f, 0.0f, m_worldPos.x,
				  0.0f, 1.0f, 0.0f, m_worldPos.y,
				  0.0f, 0.0f, 1.0f, m_worldPos.z,
				  0.0f, 0.0f, 0.0f, 1.0f);
	// moving around the world
}

void Pipeline::initPerspectiveProj(glm::mat4 &m) const
{
	const float ar = m_persProj.width / m_persProj.height;
	const float zNear = m_persProj.zNear;
	const float zFar = m_persProj.zFar;
	/*
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(((m_persProj.FOV / 2.0f) * M_PI) / 180.0f);
	m = glm::mat4(1/(tanHalfFOV *ar),	0.0f,			0.0f,						0.0f,
				  0.0f,						1.0/tanHalfFOV, 0.0f,						0.0f,
				  0.0f,						0.0f,			(-zNear -zFar) / zRange,	2.0f * zFar *zNear / zRange,
				  0.0f,						0.0f,			1.0f,						0.0f);
	 */
	//perspective matrix custom and GLM version
	m = glm::perspective(m_persProj.FOV, ar, zNear, zFar);
}

void Pipeline::initCameraTransform(const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up, glm::mat4 & m)
{
	m = glm::lookAt(pos, target, up);
}

const glm::mat4 * Pipeline::getTrans()
{
	glm::mat4 scaleTrans, rotateTrans, translationTrans, perspectiveProjTrans, cameraTrans;

	initScaleTransform(scaleTrans);
	initRotateTransform(rotateTrans);
	initTranslateTransform(translationTrans);
	initCameraTransform(m_camera->GetPos(), m_camera->GetPos() + m_camera->GetTarget(), m_camera->GetUp(), cameraTrans);
	initPerspectiveProj(perspectiveProjTrans);

	m_transformation = perspectiveProjTrans * cameraTrans * translationTrans * rotateTrans * scaleTrans;

	return & m_transformation;
}