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

	glm::mat4 getViewMatrix();

// Properties
public:
	// Camera look settings
	glm::fvec3 m_eye;
	glm::fvec3 m_center;
	glm::fvec3 m_up;

};

}

#endif // !GAME_CAMERA_H
