#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Player.hpp"
#include "Item.hpp"
#include "Skill.hpp"
#include "InventorySlot.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>



class InventoryManager {
public:
	InventoryManager(Player* player);
	bool inventoryStatus(sf::RenderWindow& window);

private:
	Player* player;

	bool inventoryClosed = false;

	bool selectingItems = true;
	int itemIndex = 0;

	std::vector<Item*> itemList;
	std::vector<Skill*> skillList;

	std::vector<Item*> equippedItems;
	std::vector<Skill*> equippedSkills;

	bool isSelectingItem;
	bool isSelectingSkill;
	sf::Vector2f dragOffset;

	std::vector<InventorySlot<Item>> itemSlots;
	std::vector<InventorySlot<Skill>> skillSlots;

	Item* draggedItem = nullptr;
	Skill* draggedSkill = nullptr;
	sf::Vector2f draggedItemOffset;
	sf::Vector2f draggedSkillOffset;
	bool isDraggingItem = false;
	bool isDraggingSkill = false;

	void handleInventoryInput(sf::RenderWindow& window);
	void renderInventory(sf::RenderWindow& window);

	void equipItem(int index);
	void unequipItem(int index);

	void equipSkill(int index);
	void unequipSkill(int index);

	void drawText(sf::RenderWindow& window, const std::string& text, sf::Vector2f pos, int size = 20);
};

#endif