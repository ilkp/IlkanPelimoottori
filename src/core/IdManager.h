#pragma once
#include <cstdint>
class IdManager
{
public:
	uint32_t Next() { return top++; }

private:
	uint32_t top = 0;

};

