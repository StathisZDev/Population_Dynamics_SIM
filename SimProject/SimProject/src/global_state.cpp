#include <includes/global_state.h>
#include <stdio.h>
#include <includes/settings.h>
#include <includes/timer_manager.h>

namespace GlobalState
{
	int maturedPopulation = 0;
	uint8_t prematuredDeaths = 0;  
	uint32_t  food = 0; 
	int8_t temperature = 0; 
	ToxityLevel toxicity = ToxityLevel::DISABLED;  
	Fertility fertility = Fertility::DISABLED;
	std::vector<Entity> initialPopulation;
	std::vector<Entity> livingPopulation;
}

void GlobalState::InitializeGlobalState(uint32_t food, int8_t temperature, ToxityLevel toxicity, Fertility fertility,uint32_t  startingPopulation) 
{
	GlobalState::food = food; 
	GlobalState::temperature = temperature;
	GlobalState::toxicity = toxicity;
	GlobalState::fertility = fertility;		
	
	for (size_t i = 0; i < startingPopulation; i++) 
	{
		initialPopulation.emplace_back();
		initialPopulation[i].SetIsMature(false);
	}
}
void TempCheckMaturity()
{
	for (int i = 0; i < GlobalState::initialPopulation.size(); i++)
	{
		if (GlobalState::initialPopulation[i].GetIsMature() && !GlobalState::initialPopulation[i].bWascounted)
		{
			GlobalState::maturedPopulation++;
			GlobalState::initialPopulation[i].bWascounted = true;
		}
	}
}


void GlobalState::Update()
{ 

	if ((int)GlobalState::livingPopulation.size() > 0)
	{
		ConsoleHelper();
	}
	if ((int)GlobalState::livingPopulation.size() == 0 && TimerManager::elapsedTime > LAG_TIMER + 5)
	{
		printf("Ending simulation...\n");
		EndSimulation();
		return;
	}
	ManageStates(); 
	TempCheckMaturity();     
}

void GlobalState::ManageEnergy() 
{
	if (GlobalState::livingPopulation.size() <= 0)return;
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
	if (GlobalState::livingPopulation.size() <= 0)return;
	uint32_t  count = 0;    
	for (auto& entity : GlobalState::livingPopulation)
	{
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
			count--;
		}
		count++;  
	}
}

void GlobalState::ManageGraduation()
{
	if (TimerManager::elapsedTime < LAG_TIMER || TimerManager::elapsedTime > 50)return;
	for (int i = 0; i < GlobalState::initialPopulation.size(); i++)
	{
		if (GlobalState::initialPopulation[i].GetIsMature())
		{
			GlobalState::livingPopulation.push_back(std::move(GlobalState::initialPopulation[i]));
			GlobalState::initialPopulation.erase(initialPopulation.begin() + i); 
			i--;
		}
	}
}

void GlobalState::ManageDeath(const uint32_t index)
{
	if (GlobalState::livingPopulation.size() <= 0)return; 
	livingPopulation.erase(GlobalState::livingPopulation.begin() + index);
}

void GlobalState::ManageDecay(Entity& entity)
{
	entity.SetEnergy(entity.GetEnergy() - 5); 
}

void GlobalState::ManageStates()
{ 
	GrowFood();
	ManageGraduation();
	ManageEnergy();
	ManageHealth();
}

void GlobalState::ManageDivision(Entity& entity) 
{
	entity.SetDefaults();
	GlobalState::livingPopulation.emplace_back();   
}

int GlobalState::GetPrematureDeaths()
{
	if (TimerManager::elapsedTime < LAG_TIMER)
	{
		return 0;
	}
	else
	{
		return  STARTING_POPULATION - GlobalState::maturedPopulation; 
	}
	return 0;
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
	//printf("Population: %d\n", GlobalState::GetPopulation());
	//printf("Global food: %d\n", GlobalState::food);
	//printf("Called to update the state of the Universe\n\n");
}

int GlobalState::GetPopulation() 
{
	return (uint32_t)GlobalState::livingPopulation.size() + (uint32_t)GlobalState::initialPopulation.size();    
}
