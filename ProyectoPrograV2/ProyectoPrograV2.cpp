#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//dos botones menu principal: insercion (insertar una ruta) y edicion (editar una ruta)
//cuatro botones menu insercion: crear ruta, crear punto, paleta de colores y tal vez uno para regresar al menu anterior
//para botones de edición se ocuparían rutas ya hechas, una vez hayan rutas hechas, dos botones, para ruta y para punto (mayormente para borrar, al seleccionar se subraya de otro color)

int main()
{
    RenderWindow window(VideoMode(1080, 720), "SFML Image Example");

    // Cargando la imagen desde un archivo
    Texture texture;
    if (!texture.loadFromFile("Chapter_5_Season_4_map_ReDimensioned.jpg")) {
        return -1; // Error al cargar la imagen
    }

    // Creando un sprite para mostrar la imagen
    Sprite sprite(texture);
    RectangleShape button(Vector2f(300, 50));
    button.setPosition(750, 330);

    RectangleShape button1(Vector2f(300, 50));
    button1.setPosition(750, 390);

    Font font;
    if (!font.loadFromFile("MONSTER OF FANTASY.otf")) {
        return -1;
    }

    Text ButtonText;
    ButtonText.setFont(font);
    ButtonText.setString("Insercion");
    ButtonText.setCharacterSize(20);
    ButtonText.setFillColor(Color::Black);
    ButtonText.setPosition(button.getPosition().x + 100, button.getPosition().y + 10);

    Text ButtonText1;
    ButtonText1.setFont(font);
    ButtonText1.setString("Edicion");
    ButtonText1.setCharacterSize(20);
    ButtonText1.setFillColor(Color::Black);
    ButtonText1.setPosition(button1.getPosition().x + 110, button1.getPosition().y + 10);

    Music music;

    if (!music.openFromFile("20240226_Fortnite Lobby Classic Lobby Music.ogg")) {
        return -1;
    }

    music.setLoop(true);
    music.play();


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(button);
        window.draw(button1);
        window.draw(ButtonText);
        window.draw(ButtonText1);
        window.draw(sprite);
        window.display();
    }

    return 0;
}