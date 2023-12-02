#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "entities/UpgradeBox.h"
#include "entities/DrawableEntity.h"
#include "utils.h"
#include <iostream>


class UpgradeBoxSpawner {
	public :
		UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& upgradeBoxList, int WindowWidth);
		~UpgradeBoxSpawner() = default;
		virtual void SpawnUpgradeBox();
		std::vector<Entities::UpgradeBox*>& GetUpgradeBoxList();
		int windowWidth; 
		
	private:
		std::vector<Entities::UpgradeBox*> upgradeBoxList;

};