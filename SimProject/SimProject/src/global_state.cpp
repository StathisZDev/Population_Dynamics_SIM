#include <includes/global_state.h>
#include <stdio.h>
#include <includes/settings.h>

namespace GlobalState
{
	int food = 0;
	int temperature = 0;
	ToxityLevel toxicity = ToxityLevel::DISABLED;  
	Fertility fertility = Fertility::DISABLED; 
	std::vector<Entity> livingPopulation;
}

void GlobalState::InitializeGlobalState(int food, int temperature, ToxityLevel toxicity, Fertility fertility,int startingPopulation)
{
	GlobalState::food = food; 
	GlobalState::temperature = temperature;
	GlobalState::toxicity = toxicity;
	GlobalState::fertility = fertility;		
	
	for (int i = 0; i < startingPopulation; i++)
	{
		livingPopulation.emplace_back();   
	}
}

void GlobalState::Update()
{ 

	if ((int)GlobalState::livingPopulation.size() > 0)
	{
		ConsoleHelper();
	}
	if ((int)GlobalState::livingPopulation.size() == 0)
	{
		EndSimulation();
		return;
	}
	ManageStates(); 
}

void GlobalState::ManageEnergy() 
{
	for (auto& entity : GlobalState::livingPopulation)
	{
		if (GlobalState::food == 0)return;
		if (entity.GetEnergy() >= 100)
		{
			ManageDivision(entity);
			continue; 
		}
		entity.SetEnergy(entity.GetEnergy() + GROWTH_RATE);   
		GlobalState::food -= 1;
	}
}

void GlobalState::ManageHealth()
{
	int count = 0; 
	for (auto& entity : GlobalState::livingPopulation)
	{
		//if entity's energy has gone to 0 start losing health
		//else take away a part of its energy
		//if health is 0 it dies.
		if (entity.GetEnergy() <= 0) 
		{
			entity.SetHealth(entity.GetHealth() - 10);   
		}
		else 
		{
			ManageDecay(entity);  
		}
		if (entity.GetHealth() <= 0)
		{
			ManageDeath(count);   
		}
		count++;  
	}
}

void GlobalState::ManageDeath(const int index)
{
	livingPopulation.erase(GlobalState::livingPopulation.begin() + index);
}

void GlobalState::ManageDecay(Entity& entity)
{
	entity.SetEnergy(entity.GetEnergy() - 5); 
}

void GlobalState::ManageStates()
{
	GrowFood();  
	ManageEnergy();
	ManageHealth();
}

void GlobalState::ManageDivision(Entity& entity) 
{
	entity.SetDefaults();
	GlobalState::livingPopulation.emplace_back();   
}

void GlobalState::GrowFood()
{
	GlobalState::food += 100;
}

void GlobalState::EndSimulation()
{
	printf("Society has collapsed. Nothing to Update\n");
}

void GlobalState::ConsoleHelper()
{
	printf("Population: %d\n", GlobalState::GetPopulation());
	printf("Global food: %d\n", GlobalState::food);
	printf("Called to update the state of the Universe\n\n");
}

int GlobalState::GetPopulation() 
{
	return (int)GlobalState::livingPopulation.size(); 
}
