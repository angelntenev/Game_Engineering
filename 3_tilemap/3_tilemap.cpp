#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "../lib_tile_level_loader/LevelSystem.h"
using namespace std;
using namespace sf;


const float screenWidth = 800.f, screenHeight = 600.f;

//Player* player = new Player();
unique_ptr <Player> player = make_unique<Player>();

void Load()
{
    ls::loadLevelFile("res/levels/maze.txt");
    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
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
    ls::Render(window);
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
        Load();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}