#include <iostream>
#include "camera.h"
#include "maths/AngleUtils.h"
#include <math.h>
#include "maths/mat4.h"

#ifdef OS_WINDOWS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp> 
#endif // OS_WINDOWS

using namespace Phantom::maths;
const Phantom::maths::vec3 Phantom::CameraNode::DEFAULT_POS (0,500,500);
const Phantom::maths::vec3 Phantom::CameraNode::DEFAULT_FRONT (1,-1,0);
const Phantom::maths::vec3 Phantom::CameraNode::DEFAULT_UP (1,1,0);
void Phantom::CameraNode::initViewMatrix()
{
	Yaw += 0.1f;//todo  有个bug，启动第一帧天空盒不渲
	updateCameraVectors();
	if (true||m_Transforms.size() == 0) {
		m_viewMatrix.LookAtMatrixBuild(Position, Position + Front, UP);

	}
	else {
		mat4x4 cMat = (*(m_Transforms.begin()))->GetMatrix();
		cMat.InverseMatrix4X4f();
		m_viewMatrix = cMat;
	}

}
void Phantom::CameraNode::CalculateVPMatrix(float aspect)
{
	if (true||m_Transforms.size() == 0) {
		vec3 focus = Position + Front;
		m_viewMatrix.LookAtMatrixBuild(Position, focus,  UP);
		/*glm::mat4 vProjection  = glm::lookAt( glm::vec3( Position.x,Position.y , Position.z),
			glm::vec3(focus.x, focus.y, focus.z),
			glm::vec3(UP.x, UP.y, UP.z));
		m_viewMatrix = &vProjection[0][0];*/

	}
	else {
		mat4x4 cMat = (*(m_Transforms.begin()))->GetMatrix();//todo Ä¬ÈÏÎÞÏà»úÃ»ÓÐ¿¼ÂÇ
		cMat.InverseMatrix4X4f();
		m_viewMatrix = cMat;
	}
	
	//m_projectionMatrix.orthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 10000.0f);

	/*glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 10000.0f);
	m_projectionMatrix = &Projection[0][0];*/

	m_projectionMatrix.perspective(toRadians(Zoom), aspect , 1.0f, 10000.0f);
	/*glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, aspect, 0.01f, 10000.0f);
	m_projectionMatrix = &Projection[0][0];*/
}

void Phantom::CameraNode::ProcessKeyboard(CameraDirection direction, float deltaTime)
{
	float velocity =  deltaTime*3;
	vec3 movation;
	if (direction == FORWARD) {
		movation = Front * velocity;
		Position += movation;
	}
	if (direction == BACKWARD) {
		movation = Front * velocity;
        Position -= movation;
	}
	if (direction == LEFT) {
		movation = Right * velocity;
		Position -= movation;
	}
	if (direction == RIGHT) {
		movation = Right * velocity;
		Position += movation;
	}
          
}

void Phantom::CameraNode::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset*=0.1f;
	yoffset*=0.1f;
	Yaw += xoffset;
	Pitch -= yoffset;
#ifdef _DEBUG
	std::cerr << "[camera] camera angle::! ("
		<< xoffset << ","
		<< yoffset << ")"
		<< std::endl;
#endif

	/*if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;*/
	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Phantom::CameraNode::updateCameraVectors()
{
	vec3 front;
	front.x = cos(toRadians(Yaw)) * cos(toRadians(Pitch));
	front.y = sin(toRadians(Pitch));
	front.z = sin(toRadians(Yaw))* cos(toRadians(Pitch));
	Front = front.normalize();
	Right = Front.crossProduct(WorldUp).normalize();  //ÎªÁËËãUP£¬Up¿ÉÄÜÊÇ´¹Ö±ÓÚÓÒ·½ÏòµÄÈÎÒâ·½Ïò¡£
	UP = Right.crossProduct(Front).normalize();
}
