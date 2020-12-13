#include "ConsoleRenderer.h"
#include <iostream>
#include <iomanip>

void ConsoleRenderer::Clean()
{
}

void ConsoleRenderer::Render()
{
	for (uint32_t i = 0; i < _tm->_size; ++i)
	{
		glm::vec3 p = _tm->_data[0].position;
		std::cout << std::setprecision(2) << std::fixed << "Vector ( " << p.x << " ; " << p.y << " ; " << p.z << " )\n";
	}
}

void ConsoleRenderer::Init(TransformManager* tm)
{
	_tm = tm;
}
