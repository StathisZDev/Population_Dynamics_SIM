#pragma once

class Entity
{
private:
	int health;
	int energy;
	int maxHealth;
public:
	Entity()
	{
		SetDefaults(); 
	};
	int GetHealth();
	void SetHealth(int value);
	int GetEnergy();
	void SetEnergy(int value);
	void SetDefaults();
};