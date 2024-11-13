#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "route.h"
#include"TextBox.h"


using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1080, 720), "Proyecto Rutas");

    Texture texture;
    if (!texture.loadFromFile("Chapter_5_Season_4_map_ReDimensioned.jpg")) {
        return -1;
    }

    Font font;
    if (!font.loadFromFile("MONSTER OF FANTASY.otf")) {
        return -1;
    }

    Music music;
    if (!music.openFromFile("20240226_Fortnite Lobby Classic Lobby Music.ogg")) {
        return -1;
    }

    SoundBuffer buttonBuffer;
    if (!buttonBuffer.loadFromFile("Fortnite.ogg")) {
        return -1;
    }

    Sprite sprite(texture);

    List routeList;

    int tmpX = 0, tmpY = 0;
    string routeName, pointName;
    int routeY = 150;

    RectangleShape colorPalette(Vector2f(300, 50));
    colorPalette.setPosition(750, 660);

    bool mainMenu = true;
    bool insertion = false;
    bool edition = false;
    bool askPoint = false;
    bool insertPoint = false;
    bool waitingForName = false;

    TextBox routeNameInput(font, Vector2f(750, 160), Vector2f(300, 50));
    TextBox pointNameInput(font, Vector2f(750, 160), Vector2f(300, 50));
    TextBox Insertion(font, Vector2f(750, 330), Vector2f(300, 50));
    TextBox Edition(font, Vector2f(750, 390), Vector2f(300, 50));
    TextBox Route(font, Vector2f(750, 40), Vector2f(300, 100));;
    TextBox Back(font, Vector2f(725, 5), Vector2f(50, 20));
    TextBox Exit(font, Vector2f(1025, 5), Vector2f(50, 20));
    TextBox Edit(font, Vector2f(750, 330), Vector2f(300, 100));
    TextBox Continue(font, Vector2f(800, 220), Vector2f(200, 30));
    TextBox Point(font, Vector2f(750, 40), Vector2f(300, 100));
    TextBox Ask(font, Vector2f(775, 40), Vector2f(250, 100));
    TextBox Save(font, Vector2f(780, 5), Vector2f(50, 20));
    TextBox Load(font, Vector2f(835, 5), Vector2f(50, 20));


    music.setVolume(20);
    music.setLoop(true);
    music.play();

    Sound button;
    button.setBuffer(buttonBuffer);
    button.setVolume(50);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            Insertion.handleOutput(event, "Insertar Ruta", 20);
            Edition.handleOutput(event, "Editar Ruta", 20);
            Route.handleOutput(event, "Por favor, ingresa \nel nombre de la ruta", 20);
            Back.handleOutput(event, "Regresar", 9);
            Exit.handleOutput(event, "Salir", 10);
            Edit.handleOutput(event, "Click derecho para borrar \npunto. Tecla Delete para \nborrar ruta", 20);
            Continue.handleOutput(event, "Continuar", 15);
            Point.handleOutput(event, "Por favor, ingresa \nel nombre del punto", 20);
            Ask.handleOutput(event, "Por favor, selecciona \nun punto en el mapa", 20);
            Save.handleOutput(event, "Guardar", 10);

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (mainMenu && Insertion.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        mainMenu = false;
                        insertion = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (mainMenu && Edition.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        mainMenu = false;
                        edition = true;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if ((insertion || edition || askPoint || insertPoint) && Back.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        mainMenu = true;
                        edition = false;
                        insertion = false;
                        askPoint = false;
                        insertPoint = false;
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (mainMenu && Exit.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        window.close();
                    }
                }

            }

            if (insertion) {
                button.play();
                Route.draw(window);
                TextBox routeDisplay(font, Vector2f(775, routeY), Vector2f(100, 50));
                cout << "Por favor, ingresa un nombre para la ruta\n";
                cin >> routeName;
                routeList.addRoute(routeName);
                routeDisplay.handleOutput(event, routeName, 20);
                routeDisplay.draw(window);
                insertion = false;
                askPoint = true;
                routeY += 55;
            }

            if (event.type == Event::MouseButtonPressed) {
                if (askPoint && event.mouseButton.button == Mouse::Left && event.mouseButton.x < 720 && event.mouseButton.y < 720) {
                    tmpX = event.mouseButton.x;
                    tmpY = event.mouseButton.y;
                    askPoint = false;
                    waitingForName = true;
                    insertPoint = true;
                    cout << "Se selecciono el punto: (" << tmpX << ", " << tmpY << "). Esperando nombre...\n";
                }
            }

            if (waitingForName) {
                cout << "Ingrese el nombre del punto\n";
                cin >> pointName;
                if (!pointName.empty()) {
                    routeList.addPoint(routeName, pointName, tmpX, tmpY, "Rojo");
                    cout << "Se anadio el punto " << pointName << " a la ruta " << routeName << "\n";
                    waitingForName = false;
                    insertPoint = false;
                    askPoint = true;
                }
                else {
                    cout << "El nombre no puede estar vacio. Introduzca un nombre valido\n";
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (Save.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.play();
                        routeList.saveRoutesToFiles(routeName);
                    }
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (edition && event.mouseButton.button == Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    routeList.deleteNearPoint(x, y);
                }
            }

            if (edition && event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
                routeList.deleteRoute(routeName);
            }


            window.clear();
            window.draw(sprite);

            if (mainMenu) {
                Insertion.draw(window);
                Edition.draw(window);
                Exit.draw(window);
            }

            if (insertion) {
                Back.draw(window);
            }
            if (askPoint) {
                Ask.draw(window);
                Save.draw(window);
                Back.draw(window);

            }
            if (insertPoint) {
                Point.draw(window);
                Back.draw(window);

            }
            if (edition) {
                Edit.draw(window);
                Save.draw(window);
                Back.draw(window);
            }

            routeList.drawRoutes(window);
            window.display();

        }
    }
    return 0;
}