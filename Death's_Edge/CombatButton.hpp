#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class CombatButton {
public:
	CombatButton(const sf::Font& font, const std::string& text, unsigned int charSize, sf::Vector2f size = { 300, 100 }, float slant = 50.f, 
		sf::Color normalColour = sf::Color::White, sf::Color hoverColour = sf::Color::Black);
	
	void setPosition(sf::Vector2f pos);
	void setFillColour(sf::Color colour);
	void setScale(sf::Vector2f pos);
	void setOutline(sf::Color colour, float thickness);
	void setTextColour(sf::Color fill, sf::Color outline, float outlineThickness);
	void setText(const std::string& text);
	void setHoverColour(sf::Color colour);

	bool isMouseOver(sf::RenderWindow& window) const;
	bool isClicked(sf::RenderWindow& window) const;

	void draw(sf::RenderWindow& window) const;
	void hoverFeedback(sf::RenderWindow& window);

private:
	sf::ConvexShape shape;
	sf::Text label;
	sf::Vector2f size;
	float slantOffset;

	sf::Color normalColour;
	sf::Color hoverColour;
};





#endif