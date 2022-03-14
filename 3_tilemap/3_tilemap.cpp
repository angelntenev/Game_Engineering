#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
using namespace std;
using namespace sf;


const float screenWidth = 800.f, screenHeight = 600.f;

//Player* player = new Player();
unique_ptr <Player> player = make_unique<Player>();

void Load()
{
    
}

void Reset()
{

}

void Update(RenderWindow& window)
{
    static Clock clock;
    float dt = clock.restart().asSeconds();

    
    player->Update(dt);

}

void Render(RenderWindow& window)
{
    player->Render(window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}