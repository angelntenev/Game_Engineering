#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include "Ship.h"
#include "game.h"
std::vector<Ship*> ships;
using namespace std;
using namespace sf;


const float screenWidth = 800.f, screenHeight = 600.f;
const Vector2f screenVec = Vector2f(screenWidth, screenHeight);

sf::Texture spritesheet;
sf::Sprite invader;
sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");
sf::RectangleShape playerRec(Vector2f(20, 5));
Player* player = new Player();

Vector2f posInvaders(100.f, 100.f);

const Keyboard::Key controls[4] =
{
    Keyboard::A, Keyboard::Z, //Player 1 up down
    Keyboard::Space
};

void Load()
{
    spritesheet.loadFromFile("res/invaders_sheet.png");
    for (int i = 0; i < invaders_rows; i++)
    {
        for (int j = 0; j < invaders_columns; j++)
        {
            Invader* inv = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { posInvaders });
            posInvaders.x += 40;
            ships.push_back(inv);
        }
        posInvaders.x = 100;
        posInvaders.y += 50;
    }
    
        
}

void Reset()
{
    
}

void Update(RenderWindow& window)
{
    static Clock clock;
    float dt = clock.restart().asSeconds();

    for (auto& s : ships)
    {
        s->Update(dt);
    }

    player->Update(dt);
    
}

void Render(RenderWindow& window)
{
    for (const auto& s : ships)
    {
        window.draw(*s);
    }
    window.draw(*player);
}

int main()
{
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Space Invaders");
    Load();
    while (window.isOpen())
    {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;

}
