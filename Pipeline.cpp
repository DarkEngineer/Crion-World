#include "Pipeline.h"

Pipeline::Pipeline()
{
		m_scale      = glm::vec3(1.0f, 1.0f, 1.0f);
        m_worldPos   = glm::vec3(0.0f, 0.0f, 0.0f);
        m_rotateInfo = glm::vec3(0.0f, 0.0f, 0.0f);
}
void Pipeline::scale(float ScaleX, float ScaleY, float ScaleZ )
{
	m_scale.x = ScaleX;
	m_scale.y = ScaleY;
	m_scale.z = ScaleZ;

	return;
}

void Pipeline::worldPos(float x, float y, float z)
{
	m_worldPos.x = x;
	m_worldPos.y = y;
	m_worldPos.z = z;
}

void Pipeline::rotate(float x, float y, float z)
{
	m_rotateInfo.x = x;
	m_rotateInfo.y = y;
	m_rotateInfo.z = z;
}

void Pipeline::setPerspectiveProj(float FOV, float width, float height, float zNear, float zFar)
{
	m_persProj.FOV = FOV;
	m_persProj.width = width;
	m_persProj.height = height;
	m_persProj.zNear = zNear;
	m_persProj.zFar = zFar;
}

void Pipeline::setCamera(const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up)
{
	m_camera.pos = pos;
	m_camera.target = target;
	m_camera.up = up;
}

const glm::mat4 & Pipeline::getWorldTrans()
{
	glm::mat4 scaleTrans, rotateTrans, translationTrans;
	initScaleTransform(scaleTrans);
	initRotateTransform(rotateTrans);
	initTranslationTransform(translationTrans);

	m_WorldTransformation = translationTrans * rotateTrans * scaleTrans;
	return m_WorldTransformation;
}

const glm::mat4 & Pipeline::getWVPTrans()
{
	getWorldTrans();

	glm::mat4 cameraTranslationTrans, cameraRotateTrans, persProjTrans;
	initTranslationTransform(cameraTranslationTrans);
	initCameraTransform(cameraRotateTrans, m_camera.pos, m_camera.target, m_camera.up);
	initPerspectiveProj(persProjTrans);

	m_WVPTransformation = persProjTrans * cameraRotateTrans * cameraTranslationTrans * m_WorldTransformation;

	return m_WVPTransformation;
}

void Pipeline::initScaleTransform(glm::mat4 &m) const
{
	m = glm::scale(m, m_scale);
}

void Pipeline::initRotateTransform(glm::mat4 &m) const
{
	m = glm::rotate( m, 0.0f , m_rotateInfo);

}

void Pipeline::initTranslationTransform(glm::mat4 &m) const
{
	m = glm::translate(m, m_worldPos);
}

void Pipeline::initTranslationCameraTransform(glm::mat4 &m) const
{
	glm::vec3 v = glm::vec3(-m_camera.pos.x, -m_camera.pos.y, -m_camera.pos.z);
	m = glm::translate(m, v);
}

void Pipeline::initCameraTransform(glm::mat4 &m, glm::vec3 &eye, glm::vec3 &target, glm::vec3 & up) const
{
	m = glm::lookAt(eye, target, up);
}

void Pipeline::initPerspectiveProj(glm::mat4 &m) const
{
	m = glm::perspectiveFov(m_persProj.FOV, m_persProj.width, m_persProj.height, m_persProj.zNear, m_persProj.zFar);
}