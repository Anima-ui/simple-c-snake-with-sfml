#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int windowWidth = 500;
const int windowHeight = 500;
const int cellSize = 20;

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake Game");
    window.setFramerateLimit(10);

    std::vector<sf::Vector2i> snake = { {10, 10} };
    sf::Vector2i direction(1, 0); 
    bool grow = false;

    sf::Vector2i food(random(0, windowWidth / cellSize - 1), random(0, windowHeight / cellSize - 1));

    sf::RectangleShape snakeRect(sf::Vector2f(cellSize - 2, cellSize - 2)); 
    sf::RectangleShape foodRect(sf::Vector2f(cellSize - 2, cellSize - 2));
    foodRect.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction != sf::Vector2i(0, 1)) {
            direction = { 0, -1 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction != sf::Vector2i(0, -1)) {
            direction = { 0, 1 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction != sf::Vector2i(1, 0)) {
            direction = { -1, 0 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction != sf::Vector2i(-1, 0)) {
            direction = { 1, 0 };
        }

        sf::Vector2i newHead = snake.front() + direction;

        if (newHead.x < 0 || newHead.x >= windowWidth / cellSize ||
            newHead.y < 0 || newHead.y >= windowHeight / cellSize) {
            window.close(); 
        }

        for (const auto& segment : snake) {
            if (newHead == segment) {
                window.close();
            }
        }

        snake.insert(snake.begin(), newHead);

        if (newHead == food) {
            grow = true;
            food = { random(0, windowWidth / cellSize - 1), random(0, windowHeight / cellSize - 1) };
        }

        if (!grow) {
            snake.pop_back();
        }
        else {
            grow = false;
        }

        window.clear(sf::Color::Black);

        for (const auto& segment : snake) {
            snakeRect.setPosition(segment.x * cellSize, segment.y * cellSize);
            snakeRect.setFillColor(sf::Color::Green);
            window.draw(snakeRect);
        }

        foodRect.setPosition(food.x * cellSize, food.y * cellSize);
        window.draw(foodRect);

        window.display();
    }
    return 0;
}



