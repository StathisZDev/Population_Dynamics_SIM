#include <includes/entity.h>


int Entity::GetHealth()
{
	return health;
}

void Entity::SetHealth(int value)
{
	health = value;
}

int Entity::GetEnergy()  
{
	return energy; 
}

void Entity::SetEnergy(int value) 
{
	energy = value; 
}

void Entity::SetDefaults()
{
	health = 100;
	maxHealth = 100;
	energy = 0;
}
