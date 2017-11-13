#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

//need transformation for matrix math
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//hardcode movementspeed later
//const float Camera::MOVEMENTSPEED = 0.001f;

class Camera
{
	public:
		//fov:field of view near and far are endpoints of view
		Camera( const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
		{
			//init of varribles
			m_perspective = glm::perspective(fov, aspect, zNear, zFar);
			m_postion = pos;
			//future: create getter/setter for m_forward and m_up to allow change
			m_forward = glm::vec3(0, 0, 1); //hard coded forward, z axis
			m_up = glm::vec3(0, 1, 0); //hard coded up, y axis
		}

		inline glm::mat4 GetViewProjection() const
		{
			//glm::lookAt used to create camera perspective
			return m_perspective * glm::lookAt(m_postion, m_postion + m_forward, m_up);
		}

		//keyboard controls
		void MoveForward(float amt)
		{
			m_postion += m_forward * amt;
		}

		void MoveRight(float amt)
		{
			m_postion += glm::cross(m_up, m_forward) * amt;
		}

		void MoveLeft(float amt)
		{
			m_postion -= glm::cross(m_up, m_forward) * amt;
		}

		void MoveUp(float amt)
		{
			m_postion += m_up * amt;
		}

		void MoveDown(float amt)
		{
			m_postion -= m_up * amt;
		}

		void Pitch(float angle)
		{
			glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

			m_forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_forward, 0.0)));
			m_up = glm::normalize(glm::cross(m_forward, right));
		}

		void RotateY(float angle)
		{
			static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

			glm::mat4 rotation = glm::rotate(angle, UP);

			m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
			m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
		}

	protected:

	private:
		glm::mat4 m_perspective; //matrix 4
		glm::vec3 m_postion;
		glm::vec3 m_forward;
		glm::vec3 m_up; //what you see as up

};

#endif //CAMERA_H_INCLUDED