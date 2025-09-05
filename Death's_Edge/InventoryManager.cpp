#include "InventoryManager.hpp"

InventoryManager::InventoryManager(Player* player) : player(player) {


}

bool InventoryManager::inventoryStatus(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Tab)) {
		inventoryClosed = true;
	}
	else {
		handleInventoryInput(window);
		renderInventory(window);
	}
	return inventoryClosed;
}


void InventoryManager::handleInventoryInput(sf::RenderWindow& window) {
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	for (auto& slot : itemSlots) {
		slot.setHovered(slot.contains(mousePos));
	}
	for (auto& slot : skillSlots) {
		slot.setHovered(slot.contains(mousePos));
	}



	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!isDraggingItem) {
			for (auto& slot : itemSlots) {
				if (slot.contains(mousePos) && slot.isTaken()) {
					draggedItem = slot.get();
					draggedItemOffset = mousePos - slot.getPosition();
					slot.clear();
					isDraggingItem = true;
					break;
				}
			}
		}
		else if (!isDraggingSkill) {
			for (auto& slot : skillSlots) {
				if (slot.contains(mousePos) && slot.isTaken()) {
					draggedSkill = slot.get();
					draggedSkillOffset = mousePos - slot.getPosition();
					slot.clear();
					isDraggingSkill = true;
					break;
				}
			}

		}
	}
	else {
		if (isDraggingItem) {
			for (auto& slot : itemSlots) {
				if (slot.contains(mousePos) && !slot.isTaken()) {
					slot.set(draggedItem);
					break;
				}
			}
			draggedItem = nullptr;
			isDraggingItem = false;
		}

		if (isDraggingSkill) {
			for (auto& slot : skillSlots) {
				if (slot.contains(mousePos) && !slot.isTaken()) {
					slot.set(draggedSkill);
					break;
				}
			}
			draggedSkill = nullptr;
			isDraggingSkill = false;
		}
	}
	
}

void InventoryManager::renderInventory(sf::RenderWindow& window) {
	 


	for (auto& slot : itemSlots) {
		slot.render(window);
	}

	for (auto& slot : skillSlots) {
		slot.render(window);
	}

	if (draggedItem) {
		sf::RectangleShape icon;
		icon.setSize(sf::Vector2f(32, 32));
		icon.setFillColor(sf::Color::Blue);
		icon.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - draggedItemOffset);
		window.draw(icon);
	}
	else if (draggedSkill) {
		sf::RectangleShape icon;
		icon.setSize(sf::Vector2f(32, 32));
		icon.setFillColor(sf::Color::Green);
		icon.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - draggedSkillOffset);
		window.draw(icon);
	}
	// Set up the Inventory Page

	sf::Texture inventoryTexture;
	std::string path2 = "Sprites/Inventory.png";

	if (!inventoryTexture.loadFromFile(path2)) {
		std::cerr << "Error loading inventory texture: " << path2 << std::endl;
		return;
	}

	sf::Sprite inventory(inventoryTexture);
	inventory.setScale(sf::Vector2f(2, 2));
	inventory.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
	window.draw(inventory);

}

void InventoryManager::equipItem(int index) {

}

void InventoryManager::unequipItem(int index) {

}

void InventoryManager::equipSkill(int index) {

}

void InventoryManager::unequipSkill(int index) {

}

