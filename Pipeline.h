#ifndef Pipeline_h
#define Pipeline_h
#include <GL/glew.h>
#include <math.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>



class Pipeline
{
  glm::vec3 m_scale;
	glm::vec3 m_worldPos;
	glm::vec3 m_rotateInfo;
	glm::mat4 m_WVPTransformation;
    glm::mat4 m_WorldTransformation;

	struct {
        float FOV;
        float width;
        float height;
        float zNear;
        float zFar;
    } m_persProj;

    struct {
        glm::vec3 pos;
        glm::vec3 target;
        glm::vec3 up;
    } m_camera;


public:
	Pipeline();
	void scale(float ScaleX, float ScaleY, float ScaleZ);
	void worldPos(float x, float y, float z);
	void rotate(float RotateX, float RotateY, float RotateZ );
	void setCamera( const glm::vec3 & pos, const glm::vec3 & target, const glm::vec3 & up );
	void setPerspectiveProj(float FOV, float width, float height, float zNear, float zFar);
	const glm::mat4 &getWVPTrans();
	const glm::mat4 &getWorldTrans();
	void initScaleTransform(glm::mat4 &m) const;
	void initRotateTransform(glm::mat4 &m) const;
	void initTranslationTransform(glm::mat4 &m) const;
	void initTranslationCameraTransform(glm::mat4 &m) const;
	void initCameraTransform(glm::mat4 &m, glm::vec3 &eye, glm::vec3 &target, glm::vec3 & up) const;
	void initPerspectiveProj(glm::mat4 &m) const;
};

#endif
