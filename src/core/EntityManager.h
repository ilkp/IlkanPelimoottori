#pragma once
#include <cstdint>
#include <queue>

template<typename T> struct EntityData
{
	bool _reserved = false;
	T _data;
};

template<typename T> class EntityManager
{
public:
	uint32_t _size = 0;
	EntityData<T>* _entities = nullptr;

	virtual void Execute(float dt) = 0;

	void Init(uint32_t size)
	{
		_size = size;
		_entities = new EntityData<T>[size];
	}

	~EntityManager()
	{
		delete[](_entities);
	}

	uint32_t Reserve()
	{
		if (_releasedIndices.size() > 0)
		{
			uint32_t id = _releasedIndices.front();
			_releasedIndices.pop();
			return id;
		}
		else if (_top == _size)
			return 0;

		return _top++;
	}

	void Release(uint32_t id)
	{
		_entities[id]._reserved = false;
		if (id == _top - 1)
			--_top;
		else
			_releasedIndices.push(id);
	}

private:
	std::queue<uint32_t> _releasedIndices;
	uint32_t _top = 0;
};
