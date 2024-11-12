#include "TextBox.h"
#include<SFML/Graphics.hpp>

TextBox::TextBox(Font& font, const Vector2f& position, const Vector2f& size) {
	box.setSize(size);
	box.setPosition(position);
	box.setFillColor(Color::White);
	box.setOutlineColor(Color::Black);
	box.setOutlineThickness(5);
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Black);
	text.setPosition(position.x + 5, position.y + 5);

	isSelected = false;
}

void TextBox::handleInput(Event& event) {
	if (event.type == Event::TextEntered && isSelected) {
		if (event.text.unicode == 8 && !text.getString().isEmpty()) {
			string str = text.getString();
			str.pop_back();
			text.setString(str);
		}
		else if (event.text.unicode < 128 && event.text.unicode != 8) {
			text.setString(text.getString() + static_cast<char>(event.text.unicode));
		}
		centerText();
	}
}

void TextBox::handleOutput(Event& event, string outputText, int size) {
		string str = outputText;
		text.setCharacterSize(size);
		text.setString(str);
		centerText();
}

void TextBox::draw(RenderWindow& window) {
	window.draw(box);
	window.draw(text);
}

void TextBox::setSelected(bool selected) {
	isSelected = selected;
	box.setOutlineColor(selected ? Color::Blue : Color::Black);
}

string TextBox::getText() const {
	return text.getString();
}

FloatRect TextBox::getGlobalBounds() const {
	return box.getGlobalBounds();
}

void TextBox::centerText() {
	FloatRect textBounds = text.getLocalBounds();
	FloatRect boxBounds = box.getGlobalBounds();
	float xPos = boxBounds.left + (boxBounds.width - textBounds.width) / 2 - textBounds.left;
	float yPos = boxBounds.top + (boxBounds.height - textBounds.height) / 2 - textBounds.top;

	text.setPosition(xPos, yPos);
}

