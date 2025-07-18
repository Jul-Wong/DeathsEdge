#include "CombatButton.hpp"

CombatButton::CombatButton(const sf::Font& font, const std::string& text, unsigned int charSize = 32, sf::Vector2f size, float slant, 
    sf::Color normalColour, sf::Color hoverColour) : size(size), slantOffset(slant), label(font, "BUTTON", 30) {
	shape.setPointCount(4);
    shape.setPoint(0, { slant, 0 });
    shape.setPoint(1, { 0, size.y });
    shape.setPoint(2, { size.x, size.y });
    shape.setPoint(3, { size.x + slant, 0 });

    normalColour = sf::Color::White;
    hoverColour = sf::Color(200, 200, 255);
    shape.setFillColor(normalColour);

    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(charSize);
    label.setFillColor(sf::Color::Black);
    label.setOutlineColor(sf::Color::White);
    label.setOutlineThickness(1);
}

void CombatButton::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
    label.setScale(sf::Vector2f(2, 2));

    sf::FloatRect bounds = label.getLocalBounds();
    sf::Vector2f centreText = pos + sf::Vector2f(size.x / 2 + slantOffset / 2, size.y / 2);
    label.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f + bounds.position.y));
    label.setPosition(centreText);
}

void CombatButton::setFillColour(sf::Color colour) {
    normalColour = colour;
    shape.setFillColor(colour);

}

void CombatButton::setScale(sf::Vector2f pos) {
    shape.setScale(pos);
}

void CombatButton::setOutline(sf::Color colour, float thickness) {
    shape.setOutlineColor(colour);
    shape.setOutlineThickness(thickness);
}

void CombatButton::setTextColour(sf::Color fill, sf::Color outline, float outlineThickness) {
    label.setFillColor(fill);
    label.setOutlineColor(outline);
    label.setOutlineThickness(outlineThickness);
}

void CombatButton::setText(const std::string& text) {
    label.setString(text);
}

void CombatButton::setHoverColour(sf::Color colour) {
    hoverColour = colour;
}

bool CombatButton::isMouseOver(sf::RenderWindow& window) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return shape.getGlobalBounds().contains(mousePos);
}

bool CombatButton::isClicked(sf::RenderWindow& window) const {
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void CombatButton::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

void CombatButton::hoverFeedback(sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (shape.getGlobalBounds().contains(mousePos)) {
        shape.setFillColor(hoverColour);
    } else {
        shape.setFillColor(normalColour);
    }
}




