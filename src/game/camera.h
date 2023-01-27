#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <glm/glm.hpp>

#include "enginecore/entity/component.h"

namespace solunar
{

class CameraComponent : public Component
{
public:
	TYPEINFO_DECLARATION(CameraComponent, Component);

public:
	CameraComponent();
	~CameraComponent();

	void onEntitySet(Entity* entity) override;
	void onEntityRemove() override;

	void setLookAt(const glm::vec3& targetLocation);

	glm::mat4 getViewMatrix();

// Properties
public:
	// Camera look settings
	glm::vec3 m_eye;
	glm::vec3 m_center;
	glm::vec3 m_up;

};

}

#endif // !GAME_CAMERA_H
