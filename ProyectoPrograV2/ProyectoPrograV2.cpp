#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Image Example");

    // Cargando la imagen desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("1f928.png")) {
        return -1; // Error al cargar la imagen
    }

    // Creando un sprite para mostrar la imagen
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}