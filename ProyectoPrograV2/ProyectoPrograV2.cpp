#include<iostream>
#include<stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "route.h"

//Falta pedir nombre y que funcione
//Ademas de el resto de cosas (linea curva, implementacion de archivos, etc)

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1080, 720), "Proyecto Rutas");

    Texture texture;
    if (!texture.loadFromFile("Chapter_5_Season_4_map_ReDimensioned.jpg")) {
        return -1;
    }

    Sprite sprite(texture);

    List routeList;

    string current = "Ruta de ejemplo";
    routeList.addRoute(current);

    RectangleShape insertion(Vector2f(300, 50));
    insertion.setPosition(750, 330);

    RectangleShape edition(Vector2f(300, 50));
    edition.setPosition(750, 390);

    RectangleShape subInsertion(Vector2f(170, 50));
    subInsertion.setPosition(725, 280);

    RectangleShape subInsertion1(Vector2f(170, 50));
    subInsertion1.setPosition(905, 280);

    RectangleShape sub1Insertion1(Vector2f(300, 100));
    sub1Insertion1.setPosition(750, 330);

    RectangleShape subEdition(Vector2f(300, 50));
    subEdition.setPosition(750, 330);

    RectangleShape subEdition1(Vector2f(300, 50));
    subEdition1.setPosition(750, 390);

    RectangleShape colorPalette(Vector2f(300, 50));
    colorPalette.setPosition(750, 660);

    RectangleShape Back(Vector2f(50, 20));;
    Back.setPosition(725, 5);

    RectangleShape Back1(Vector2f(50, 20));;
    Back1.setPosition(1025, 695);

    bool buttonMenu = true;
    bool buttonInsertion = false;
    bool buttonEdition = false;
    bool subMenuInsertion = false;
    bool subMenuInsertion1 = false;

    Font font;
    if (!font.loadFromFile("MONSTER OF FANTASY.otf")) {
        return -1;
    }
   
    Text InsertionText("Insercion", font, 20);
    InsertionText.setFillColor(Color::Black);
    InsertionText.setPosition(insertion.getPosition().x + 100, insertion.getPosition().y + 10);

    Text EditionText("Edicion", font, 20);
    EditionText.setFillColor(Color::Black);
    EditionText.setPosition(edition.getPosition().x + 110, edition.getPosition().y + 10);

    Text subInsertionText("Crear Ruta", font, 20);
    subInsertionText.setFillColor(Color::Black);
    subInsertionText.setPosition(subInsertion.getPosition().x + 20, subInsertion.getPosition().y + 10);

    Text subInsertionText1("Crear Punto", font, 20);
    subInsertionText1.setFillColor(Color::Black);
    subInsertionText1.setPosition(subInsertion1.getPosition().x + 20, subInsertion1.getPosition().y + 10);

    Text sub1InsertionText("Por Favor, introduce el \nnombre de tu ruta en la \nconsola\n", font, 20);
    sub1InsertionText.setFillColor(Color::Black);
    sub1InsertionText.setPosition(sub1Insertion1.getPosition().x + 10, sub1Insertion1.getPosition().y + 5);

    Text sub1InsertionText1("Por favor, presiona con el \nel mouse el punto que \ndeseas marcar", font, 20);
    sub1InsertionText1.setFillColor(Color::Black);
    sub1InsertionText1.setPosition(sub1Insertion1.getPosition().x + 10, sub1Insertion1.getPosition().y + 5);

    Text subEditionText("Selecciona una ruta", font, 20);
    subEditionText.setFillColor(Color::Black);
    subEditionText.setPosition(subEdition.getPosition().x + 45, subEdition.getPosition().y + 10);

    Text BackText("Regresar", font, 9);
    BackText.setFillColor(Color::Black);
    BackText.setPosition(Back.getPosition().x + 2, Back.getPosition().y + 5);

    Text Back1Text("Salir", font, 10);
    Back1Text.setFillColor(Color::Black);
    Back1Text.setPosition(Back1.getPosition().x + 13, Back1.getPosition().y + 3);

    Music music;
    if (!music.openFromFile("20240226_Fortnite Lobby Classic Lobby Music.ogg")) {
        return -1;
    }

    music.setVolume(40);
    music.setLoop(true);
    music.play();

    SoundBuffer buttonBuffer;
    if (!buttonBuffer.loadFromFile("Fortnite.ogg")) {
        return -1;
    }
    Sound button;
    button.setBuffer(buttonBuffer);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && insertion.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = false;
                        buttonInsertion = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && edition.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = false;
                        buttonEdition = true;
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if ((buttonInsertion || buttonEdition || subMenuInsertion || subMenuInsertion1) && Back.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = true;
                        buttonEdition = false;
                        buttonInsertion = false;
                        subMenuInsertion = false;
                        subMenuInsertion1 = false;
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && Back1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        window.close();
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonInsertion && subInsertion.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        subMenuInsertion = true;
                        buttonInsertion = false;        
                        cout << "Por favor, introduce un nombre para la nueva ruta:\n";
                    }
                   
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left && event.mouseButton.x < 720 && event.mouseButton.y < 720) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    string pointName = "Punto " + to_string(x) + ", " + to_string(y);
                    routeList.addPoint(current, pointName, x, y, "Rojo");
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    routeList.deleteNearPoint(x, y);
                }
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
                routeList.deleteRoute(current);
            }
           

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonInsertion && subInsertion1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        subMenuInsertion1 = true;
                        buttonInsertion = false;
                    }

                }
            }
        }
        
        window.clear();
        window.draw(sprite);

        if (buttonMenu) {
            window.draw(insertion);
            window.draw(InsertionText);
            window.draw(edition);
            window.draw(EditionText);
            window.draw(Back1);
            window.draw(Back1Text);
        }
       
        if (buttonInsertion) {
            window.draw(subInsertion);
            window.draw(subInsertion1);
            window.draw(subInsertionText);
            window.draw(subInsertionText1);
            window.draw(Back);
            window.draw(BackText);
        }
        if (buttonEdition) {
            window.draw(subEdition);
            window.draw(subEditionText);
            window.draw(Back);
            window.draw(BackText);
        }
        if (subMenuInsertion) {
            window.draw(Back);
            window.draw(BackText);
            window.draw(sub1Insertion1);
            window.draw(sub1InsertionText);
           

        }
        if (subMenuInsertion1) {
            window.draw(Back);
            window.draw(BackText);
            window.draw(sub1Insertion1);
            window.draw(sub1InsertionText1);

        }

        routeList.drawRoutes(window);
        window.display();

    }

    return 0;
}