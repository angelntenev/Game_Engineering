//Ship.cpp
#include "Ship.h"
#include "game.h"
#include "bullet.h"
using namespace std;
using namespace sf;



Ship::Ship() {};

Ship::Ship(IntRect ir) : sf::Sprite()
{
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

void Ship::Update(const float& dt) {}

void Ship::Explode() {
	setTextureRect(IntRect(Vector2(128, 32), Vector2(32, 32)));
	_exploded = true;
}

//Define the ship deconstructor
//Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

bool Invader::direction;
float Invader::speed = 50;


Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir)
{
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);

}


void Invader::Update(const float& dt)
{
	Ship::Update(dt);

	move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16))
	{
		direction = !direction;
		for (int i = 0; i < ships.size(); i++)
		{
			ships[i]->move(Vector2f(0.0f, 24.0f));
		}
	}
}


const Keyboard::Key controls[3] =
{
	Keyboard::A, Keyboard::D, Keyboard::Space //Move left/right and shoot
};
const int playerSpeed = 400;

Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32)))
{
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt)
{
	Ship::Update(dt);
	static vector<Bullet*> bullets;

	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}
	Player::move(Vector2f(direction * playerSpeed * dt, 0.f));

	if (Keyboard::isKeyPressed(controls[2]))
	{
		bullets.push_back(new Bullet(getPosition(), false));
	}

	for (const auto s : bullets) {
		bullets.Update(dt);
	}
}