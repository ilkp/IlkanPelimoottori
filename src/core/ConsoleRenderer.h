#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>
#include "IRenderer.h"

class ConsoleRenderer : IRenderer
{
public:
	void Clean() {}
	void Render()
	{
		glm::vec3 p = _tm->_entityData[1]._position;
		std::cout << std::setprecision(2) << std::fixed << "Vector ( " << p.x << " ; " << p.y << " ; " << p.z << " )\n";
	}
	void Init(TransformManager* transformManager)
	{
		_tm = transformManager;
	}

private:
	TransformManager* _tm = nullptr;
};

