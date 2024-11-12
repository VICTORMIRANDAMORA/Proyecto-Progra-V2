#include<iostream>
#include<stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "route.h"
#include"TextBox.h"

//Los nombres funionan, solo se debem guardar como los nombres de las listas o los puntos respectivamente
//Ademas de el resto de cosas (linea curva, implementacion de archivos, etc)
//Se intento implementar archivos, todavia le falta proceso

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

    string routeName;
    string pointName;

    RectangleShape colorPalette(Vector2f(300, 50));
    colorPalette.setPosition(750, 660);

    bool buttonMenu = true;
    bool buttonInsertion = false;
    bool buttonEdition = false;

    Font font;
    if (!font.loadFromFile("MONSTER OF FANTASY.otf")) {
        return -1;
    }

    TextBox routeNameInput(font, Vector2f(750, 160), Vector2f(300, 50));
    TextBox pointNameInput(font, Vector2f(750, 220), Vector2f(300, 50));

    TextBox Insertion(font, Vector2f(750, 330), Vector2f(300, 50));
    TextBox Edition(font, Vector2f(750, 390), Vector2f(300, 50));
    TextBox Route(font, Vector2f(750, 40), Vector2f(300, 100));;
    TextBox Back(font, Vector2f(725, 5), Vector2f(50, 20));
    TextBox Exit(font, Vector2f(1025, 5), Vector2f(50, 20));
    TextBox Edit(font, Vector2f(750, 330), Vector2f(300, 50));


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

            routeNameInput.handleInput(event);
            pointNameInput.handleInput(event);
            Insertion.handleOutput(event, "Insercion", 20);
            Edition.handleOutput(event, "Edicion", 20);
            Route.handleOutput(event, "Por favor, ingresa \nel nombre de la ruta", 20);
            Back.handleOutput(event, "Regresar", 9);
            Exit.handleOutput(event, "Salir", 10);
            Edit.handleOutput(event, "Selecciona una ruta", 20);
            


            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (routeNameInput.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        routeNameInput.setSelected(true);
                    }
                    else {
                        routeNameInput.setSelected(false);
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (pointNameInput.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        pointNameInput.setSelected(true);
                    }
                    else {
                        pointNameInput.setSelected(false);
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && Insertion.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = false;
                        buttonInsertion = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && Edition.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = false;
                        buttonEdition = true;
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if ((buttonInsertion || buttonEdition) && Back.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        buttonMenu = true;
                        buttonEdition = false;
                        buttonInsertion = false;
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonMenu && Exit.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        window.close();
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (buttonInsertion && event.mouseButton.button == Mouse::Left && event.mouseButton.x < 720 && event.mouseButton.y < 720) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    pointName = pointNameInput.getText();
                    routeList.addPoint(routeName, pointName, x, y, "Rojo");
                    cout << "Se anadio el punto " << pointName << " a la ruta " << routeName << "\n";
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    routeList.deleteNearPoint(x, y);
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
                routeList.deleteRoute(routeName);
            }
        }
        
        window.clear();
        window.draw(sprite);

        if (buttonMenu) {
            Insertion.draw(window);
            Edition.draw(window);
            Exit.draw(window);
        }
       
        if (buttonInsertion) {
            Route.draw(window);
            routeNameInput.draw(window);
            routeName = routeNameInput.getText();
            routeList.addRoute(routeName);
            pointNameInput.draw(window);
            Back.draw(window);
        }
        if (buttonEdition) {
            Edit.draw(window);
            Back.draw(window);
        }

        routeList.drawRoutes(window);
        window.display();

    }

    return 0;
}