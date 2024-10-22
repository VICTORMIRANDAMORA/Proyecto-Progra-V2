#include<iostream>
#include<stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//dos botones menu principal: insercion (insertar una ruta) y edicion (editar una ruta)
//cuatro botones menu insercion: crear ruta, crear punto, paleta de colores y tal vez uno para regresar al menu anterior
//para botones de edición se ocuparían rutas ya hechas, una vez hayan rutas hechas, dos botones, para ruta y para punto (mayormente para borrar, al seleccionar se subraya de otro color)
//no sean sapos xd  jodase

int main()
{
    RenderWindow window(VideoMode(1080, 720), "SFML Image Example");

    Texture texture;
    if (!texture.loadFromFile("Chapter_5_Season_4_map_ReDimensioned.jpg")) {
        return -1;
    }

    Sprite sprite(texture);
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

    Text InsertionText;
    InsertionText.setFont(font);
    InsertionText.setString("Insercion");
    InsertionText.setCharacterSize(20);
    InsertionText.setFillColor(Color::Black);
    InsertionText.setPosition(insertion.getPosition().x + 100, insertion.getPosition().y + 10);

    Text EditionText;
    EditionText.setFont(font);
    EditionText.setString("Edicion");
    EditionText.setCharacterSize(20);
    EditionText.setFillColor(Color::Black);
    EditionText.setPosition(edition.getPosition().x + 110, edition.getPosition().y + 10);

    Text subInsertionText;
    subInsertionText.setFont(font);
    subInsertionText.setString("Crear Ruta");
    subInsertionText.setCharacterSize(20);
    subInsertionText.setFillColor(Color::Black);
    subInsertionText.setPosition(subInsertion.getPosition().x + 20, subInsertion.getPosition().y + 10);

    Text subInsertionText1;
    subInsertionText1.setFont(font);
    subInsertionText1.setString("Crear Punto");
    subInsertionText1.setCharacterSize(20);
    subInsertionText1.setFillColor(Color::Black);
    subInsertionText1.setPosition(subInsertion1.getPosition().x + 20, subInsertion1.getPosition().y + 10);

    Text sub1InsertionText;
    sub1InsertionText.setFont(font);
    sub1InsertionText.setString("Por favor, introduce el \nnombre de tu ruta en la \nconsola\n");
    sub1InsertionText.setCharacterSize(20);
    sub1InsertionText.setFillColor(Color::Black);
    sub1InsertionText.setPosition(sub1Insertion1.getPosition().x + 10, sub1Insertion1.getPosition().y + 5);

    Text sub1InsertionText1;
    sub1InsertionText1.setFont(font);
    sub1InsertionText1.setString("Por favor, presiona con \nel mouse el punto que \ndeseas marcar");
    sub1InsertionText1.setCharacterSize(20);
    sub1InsertionText1.setFillColor(Color::Black);
    sub1InsertionText1.setPosition(sub1Insertion1.getPosition().x + 10, sub1Insertion1.getPosition().y + 5);

    Text subEditionText;
    subEditionText.setFont(font);
    subEditionText.setString("Selecciona una ruta");
    subEditionText.setCharacterSize(20);
    subEditionText.setFillColor(Color::Black);
    subEditionText.setPosition(subEdition.getPosition().x + 45, subEdition.getPosition().y + 10);

    Text BackText;
    BackText.setFont(font);
    BackText.setString("Regresar");
    BackText.setCharacterSize(9);
    BackText.setFillColor(Color::Black);
    BackText.setPosition(Back.getPosition().x + 2, Back.getPosition().y + 5);

    Text Back1Text;
    Back1Text.setFont(font);
    Back1Text.setString("Salir");
    Back1Text.setCharacterSize(10);
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
                        window.close();
                    }
                }

            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonInsertion && subInsertion.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        printf("Por favor, introduce un nombre para la nueva ruta:\n");
                        subMenuInsertion = true;
                        buttonInsertion = false;
                    }

                }
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (buttonInsertion && subInsertion1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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

        window.display();
    }

    return 0;
}