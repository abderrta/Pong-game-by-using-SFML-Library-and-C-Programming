#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Paddle {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Paddle(float startX, float startY) {
        shape.setSize(sf::Vector2f(20, 100));
        shape.setPosition(startX, startY);
        shape.setFillColor(sf::Color::White);
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() {
        shape.move(velocity);
    }
};

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Ball(float startX, float startY) {
        shape.setRadius(10);
        shape.setPosition(startX, startY);
        shape.setFillColor(sf::Color::White);
        velocity.x = 5;
        velocity.y = 5;
    }

    void update() {
        shape.move(velocity);

        // Collision with top and bottom
        if (shape.getPosition().y < 0 || shape.getPosition().y + 2 * shape.getRadius() > 600) {
            velocity.y = -velocity.y;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    Paddle paddle1(10, 250);
    Paddle paddle2(770, 250);
    Ball ball(400, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.shape.getPosition().y > 0) {
            paddle2.velocity.y = -5;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                   paddle2.shape.getPosition().y + paddle2.shape.getSize().y < 600) {
            paddle2.velocity.y = 5;
        } else {
            paddle2.velocity.y = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.shape.getPosition().y > 0) {
            paddle1.velocity.y = -5;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                   paddle1.shape.getPosition().y + paddle1.shape.getSize().y < 600) {
            paddle1.velocity.y = 5;
        } else {
            paddle1.velocity.y = 0;
        }

        ball.update();
        paddle1.update();
        paddle2.update();

        // Collision with paddles
        if (ball.shape.getGlobalBounds().intersects(paddle1.shape.getGlobalBounds()) ||
            ball.shape.getGlobalBounds().intersects(paddle2.shape.getGlobalBounds())) {
            ball.velocity.x = -ball.velocity.x;
        }

        window.clear();

        window.draw(paddle1.shape);
        window.draw(paddle2.shape);
        window.draw(ball.shape);

        window.display();
    }

    return 0;
}

