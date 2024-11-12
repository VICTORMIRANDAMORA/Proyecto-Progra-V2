#pragma once
#include<SFML/Graphics.hpp>
#include<string>

using namespace sf;
using namespace std;

class TextBox
{
private:
	RectangleShape box;
	Text text;
	bool isSelected;
	void centerText();
public:
	TextBox(Font& font, const Vector2f& position, const Vector2f& size);
	void handleInput(Event& event);
	void handleOutput(Event& event, string outputText, int size);
	void draw(RenderWindow& window);
	void setSelected(bool selected);
	string getText() const;
	FloatRect getGlobalBounds() const;
};

