#pragma once
#include <includes/population_control_enums.h>
#include <includes/entity.h>
#include <vector>

namespace GlobalState
{
	extern int food;
	extern int temperature;
	extern ToxityLevel toxicity; 
	extern Fertility fertility;  
	extern std::vector<Entity> livingPopulation;  
	/// <summary>
	/// Initializes the starting conditions of the simulation 
	/// </summary>
	/// <param name="food:">Main resource that all entities depend on</param>
	/// <param name="temperature:">Enviromental factors that affect the entities on a global Scale</param>
	/// <param name="toxicity"></param>
	/// <param name="fertility"></param>
	void InitializeGlobalState(int food,int temperature,ToxityLevel toxicity,Fertility fertility,int startingPopulation); 
	/// <summary>
	/// Main function to update all variables
	/// </summary>
	int GetPopulation();  
	void Update();
	void ManageEnergy(); 
	void ManageHealth();
	void ManageDeath(const int index);
	void ManageDecay(Entity& entity);   
	void ManageStates();
	void ManageDivision(Entity& entity);
	void GrowFood();
	void EndSimulation();
	void ConsoleHelper();
}
