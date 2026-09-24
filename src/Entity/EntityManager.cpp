#include "EntityManager.h"
 

Entity::Animated *EntityManager::CreateEntity(const char* meshPath, const char* shaderPath, std::vector<const char*>& textures)
{
	Entity::Animated* entity = Entity::Create(meshPath, shaderPath, textures, (int)entities.size());

	// @note Look for a better way, 'cause entities can be removed
	//
	entity->id = (U32)entities.size();
	
	entities.emplace_back(entity);

	return entity;
}

void EntityManager::Update()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		Entity::UpdateComponents(entities.at(i));
	}
}