#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite
{
public:
	static void Update(const float& dt);
	static void Render(sf::RenderWindow& window);
	static void Fire(const sf::Vector2f& pos, const bool mode);
	static void Init();
	~Bullet() = default;
protected:
	Bullet();
	//false = player bullet, true = enemy bullet
	bool _mode;
	sf::IntRect _sprite;
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	void _Update(const float& dt);
};