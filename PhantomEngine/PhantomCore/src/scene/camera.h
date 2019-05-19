#pragma once
#include "vector.h"
#include "mat4.h"
#include "SceneBaseNode.h"

namespace Phantom {
	enum CameraDirection {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};


	class CameraNode : public SceneBaseNode
	{
	public:
		// Default camera values
		const float YAW = -90.0f;
		const float PITCH = 0.0f;
		const float SPEED = 2.5f;
		const float SENSITIVITY = 0.1f;
		const float ZOOM = 45.0f;
        
        static const Phantom::maths::vec3 DEFAULT_POS;
        
    public:
        Phantom::maths::vec3 UP ;
        Phantom::maths::vec3 Position ;
        Phantom::maths::vec3 Front;
        Phantom::maths::vec3 WorldUp ;
        Phantom::maths::vec3 Right ;
        
        float Zoom;//可响应鼠标滚轮事件 #todo
        float Yaw = -90.0f;
        float Pitch = 0.0f;
		
	public:
		CameraNode() :	UP(0, 1, 0), 
						Position(DEFAULT_POS), 
						Front(0, 0, 1),
						WorldUp(0,1,0),
						Right(-1,0,0), Zoom(ZOOM),Yaw(YAW),Pitch(PITCH)
						{};
		CameraNode(const char* name) : UP(0, 1, 0),
			Position(DEFAULT_POS),
			Front(0, 0, 1),
			WorldUp(0, 1, 0),
			Right(-1, 0, 0), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
		{
			m_Name = name;
		};
		CameraNode(const std::string& name) : UP(0, 1, 0),
			Position(DEFAULT_POS),
			Front(0, 0, 1),
			WorldUp(0, 1, 0),
			Right(-1, 0, 0), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
		{
			m_Name = name;
		};
		CameraNode(const std::string&& name) : UP(0, 1, 0),
			Position(DEFAULT_POS),
			Front(0, 0, 1),
			WorldUp(0, 1, 0),
			Right(-1, 0, 0), Zoom(ZOOM) , Yaw(YAW), Pitch(PITCH)
		{
			m_Name = std::move(name);
		};
		Phantom::maths::mat4x4 m_viewMatrix;
		Phantom::maths::mat4x4 m_projectionMatrix;

		void initViewMatrix();
		void CalculateVPMatrix();
	
		void ProcessKeyboard(CameraDirection direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset);

	private:
		void updateCameraVectors();
	};

}
