#include "camera.h"

using namespace Phantom::maths;
void Phantom::CameraNode::initViewMatrix()
{
	/*GfxConfiguration& conf = g_pApp->GetConfiguration();
	float screenAspect = (float)conf.screenWidth / (float)conf.screenHeight;*/
	if (m_Transforms.size() == 0) {
		//m_projectionMatrix.orthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
		//摄像机位置；  LookAt位置， Up方向  
		m_viewMatrix.LookAtMatrixBuild(vec3(m_positionX, 0, m_positionZ),
			vec3(0, 0, 0),
			vec3(0, 1, 0));
	}
	else {
		mat4x4 cMat = (*(m_Transforms.begin()))->GetMatrix();
		cMat.InverseMatrix4X4f();
		m_viewMatrix = cMat;
	}
	m_projectionMatrix.perspective(90.0f, 16.0f / 9.0f, 0.01f, 10000.0f);
}
void Phantom::CameraNode::CalculateVPMatrix()
{
	mat4x4 cMat = (*(m_Transforms.begin()))->GetMatrix();//todo 默认无相机没有考虑
	cMat.elements[12] += m_positionX;
	cMat.elements[13] += m_positionY;
	cMat.elements[14] += m_positionZ;
	cMat.InverseMatrix4X4f();
	m_viewMatrix = cMat;
}
