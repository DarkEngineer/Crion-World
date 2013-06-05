#ifndef Pipeline_h
#define Pipeline_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Camera/Camera.h"



class Pipeline
{
	struct {
		float FOV;
		float width;
		float height;
		float zNear;
		float zFar;
	} m_persProj;

	Camera * m_camera;

	glm::vec3 m_scale;
	glm::vec3 m_worldPos;
	glm::vec3 m_rotateInfo;
	glm::mat4 m_transformation;
	

	void initScaleTransform(glm::mat4 & m) const;
	void initRotateTransform(glm::mat4 &m) const;
	void initTranslateTransform(glm::mat4 &m) const;
	void initPerspectiveProj(glm::mat4 &m) const;
	void initCameraTransform(const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up, glm::mat4 & m);

	
public:
	Pipeline();
	void scale(float scaleX, float scaleY, float scaleZ);
	void worldPos(float x, float y, float z);
	void rotate(float rotateX, float rotateY, float rotateZ);
	void setPerspectiveProj(float FOV, float width, float height, float zNear, float zFar);
	void setCamera(const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up);
	void setCamera(const int & windowWidth, const int & windowHeight);
	Camera * getCamera();

	virtual void init();
	virtual void render();

	
	const glm::mat4 * getTrans();
	virtual ~Pipeline();
};

extern Pipeline * pipeline;
#endif