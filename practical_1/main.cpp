#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
using namespace sf;


const float screenWidth = 800.f, screenHeight = 600.f;
const Vector2f screenVec = Vector2f(screenWidth, screenHeight);

int p1Score = 0, p2Score = 0;

const Vector2f paddleSize(25.f, 100.f);
Vector2f ballVelocity;
const float ballRadius = 10.f;
bool server = false;
const float paddleSpeed = 400.f;

sf::CircleShape ball;
sf::RectangleShape player1;
sf::RectangleShape player2;
sf::Text text;

sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Pong");

const Keyboard::Key controls[4] =
{
    Keyboard::A, Keyboard::Z, //Player 1 up down
    Keyboard::Up, Keyboard::Down  //Player 2 up down
};

void Load()
{
    player1.setSize(paddleSize);
    player2.setSize(paddleSize);
    player1.setFillColor(sf::Color::White);
    player1.setPosition(sf::Vector2f(5.f + (paddleSize.x/2), (screenVec.y / 2.f)));
    player2.setFillColor(sf::Color::White);
    player2.setPosition(sf::Vector2(screenWidth - (paddleSize.x/2) - 5.f, (screenVec.y / 2)));
    player1.setOrigin(paddleSize / 2.f);
    player2.setOrigin(paddleSize / 2.f);
    ball.setRadius(ballRadius);
    ball.setOrigin(Vector2f(ballRadius,ballRadius));
    ball.setPosition(screenVec / 2.f);
    ballVelocity = {(server ? 100.0f : -100.0f), 60.0f};
    sf::Font font;
    font.loadFromFile("\SupermercadoOneRegular.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString(std::to_string(p1Score) + " : " + std::to_string(p2Score));
    text.setPosition(Vector2f((screenWidth / 2) - (text.getLocalBounds().width / 2), 0));
}

void Reset()
{
    ball.setPosition(screenVec / 2.f);
    player1.setPosition(sf::Vector2f(5.f + (paddleSize.x / 2), (screenVec.y / 2.f)));
    player2.setPosition(sf::Vector2(screenWidth - (paddleSize.x / 2) - 5.f, (screenVec.y / 2)));
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
    text.setString(std::to_string(p1Score) + " : " + std::to_string(p2Score));
}

void Update(RenderWindow &window)
{
    static Clock clock;
    float dt = clock.restart().asSeconds();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) 
        {
            window.close();
            return;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    float direction1 = 0.0f, direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0]))
    {
        direction1--;
    }
    if (Keyboard::isKeyPressed(controls[1]))
    {
        direction1++;
    }
    if (Keyboard::isKeyPressed(controls[2]))
    {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3]))
    {
        direction2++;
    }
    player1.move(Vector2f(0.f, direction1 * paddleSpeed * dt));
    player2.move(Vector2f(0.f, direction2 * paddleSpeed * dt));

    ball.move(ballVelocity * dt);
    const float ballx = ball.getPosition().x;
    const float bally = ball.getPosition().y;
    if (bally > screenHeight)
    {
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2f(0, -10));
    }
    else if (bally < 0)
    {
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2f(0, 10));
    }
    else if (ballx > screenWidth)
    {
        Reset();
    }
    else if (ballx < 0)
    {
        Reset();
    }
    else if (ballx < paddleSize.x &&
        bally > player1.getPosition().y - (paddleSize.y * 0.5f) &&
        bally < player1.getPosition().y + (paddleSize.y * 0.5f))
    {
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2f(10, 0));
    }
    else if (ballx > (screenWidth - paddleSize.x) &&
        bally > player2.getPosition().y - (paddleSize.y * 0.5f) &&
        bally < player2.getPosition().y + (paddleSize.y * 0.5f))
    {
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2f(-10, 0));
    }
}

void Render(RenderWindow& window)
{
    window.draw(player1);
    window.draw(player2);
    window.draw(ball);
}

int main()
{
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Pong");
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
