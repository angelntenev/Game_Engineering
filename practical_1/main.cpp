#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    float screenSize = 500.f;
    float radius = 100.f;
  sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "SFML works!");
  sf::CircleShape circleShape(radius);
  sf::RectangleShape boxShape(sf::Vector2f(radius * sqrt(2), radius * sqrt(2)));
  circleShape.setFillColor(sf::Color::Magenta);
  boxShape.setFillColor(sf::Color::White);
  circleShape.setOrigin(sf::Vector2f(radius, radius));
  circleShape.setPosition(sf::Vector2f(screenSize/2, screenSize/2));
  boxShape.setPosition(sf::Vector2f(screenSize/2, screenSize/2));
  boxShape.setOrigin(sf::Vector2f((radius * sqrt(2)) / 2, (radius * sqrt(2)) / 2));
  //boxShape.setRotation(5.f);

  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    
    window.draw(circleShape);
    window.draw(boxShape);
    boxShape.rotate(0.1f);
    window.display();
  }
  return 0;
}