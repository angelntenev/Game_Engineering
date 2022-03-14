//player.cpp
#include "player.h"
using namespace sf;
using namespace std;


const Keyboard::Key controls[4] =
{
    Keyboard::Up, Keyboard::Down,
    Keyboard::Left, Keyboard::Right
};


void Player::Update(double dt) {
    //Move in four directions based on keys
    float direction_x= 0.0f, direction_y = 0.0f;
    if (Keyboard::isKeyPressed(controls[0]))
    {
        direction_y--;
    }
    if (Keyboard::isKeyPressed(controls[1]))
    {
        direction_y++;
    }
    if (Keyboard::isKeyPressed(controls[2]))
    {
        direction_x--;
    }
    if (Keyboard::isKeyPressed(controls[3]))
    {
        direction_x++;
    }
    move(Vector2f(direction_x * dt * _speed, direction_y * _speed * dt));
        Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}