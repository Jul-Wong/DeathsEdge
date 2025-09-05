#ifndef INVENTORYSLOT_HPP
#define INVENTORYSLOT_HPP

#include <SFML/Graphics.hpp>

template <typename T>
class InventorySlot {
public:
	InventorySlot(sf::Vector2f pos, sf::Vector2f size);

	void set(T* object);
	T* get() const;
	void clear();
	bool isTaken() const;
	bool contains(sf::Vector2f point) const;
	void render(sf::RenderWindow& window);
	void setHovered(bool hovered);
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;




private:

	std::vector<InventorySlot<Item>> itemSlots;
	std::vector<InventorySlot<Skill>> skillSlots;

	sf::RectangleShape box;
	T* object = nullptr;
	bool hovered = false;
};

template <typename T>
InventorySlot<T>::InventorySlot(sf::Vector2f pos, sf::Vector2f size) {
	box.setPosition(pos);
	box.setSize(size);
	box.setOutlineThickness(2.f);
	box.setOutlineColor(sf::Color::White);
	box.setFillColor(sf::Color(60, 60, 60));
}


template <typename T>
void InventorySlot<T>::set(T* object) {
	this->object = object;
}

template <typename T>
T* InventorySlot<T>::get() const {
	return object;
}

template <typename T>
void InventorySlot<T>::clear() {
	object = nullptr;
}

template<typename T>
bool InventorySlot<T>::isTaken() const {
	return object != nullptr;
}

template<typename T>
bool InventorySlot<T>::contains(sf::Vector2f point) const {
	return box.getGlobalBounds().contains(point);
}

template <typename T>
void InventorySlot<T>::setHovered(bool hovered) {
	this->hovered = hovered;
}

template <typename T>
sf::Vector2f InventorySlot<T>::getPosition() const {
	return box.getPosition();
}

template <typename T>
sf::Vector2f InventorySlot<T>::getSize() const {
	return box.getSize();
}


template <typename T>
void InventorySlot<T>::render(sf::RenderWindow& window) {
	window.draw(box);

	if (object) {
		// Draw a colored overlay or a small rectangle as placeholder
		sf::RectangleShape icon;
		icon.setSize({ box.getSize().x - 8, box.getSize().y - 8 });	
		icon.setPosition(box.getPosition() + sf::Vector2f(4, 4));
		icon.setFillColor(sf::Color::Blue); // Color can represent type (blue for item, green for skill)
		window.draw(icon);
	}
}

#endif 
