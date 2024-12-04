#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

// incomplete!

inline float radians(float degree)
{
    return degree * M_PI / 180.0f;
}

class LSystem
{
    std::string axiom;
    std::string sentence;
    float length;
    float angle;
    std::vector<sf::Vector2f> points;
    sf::Vector2f startPoint;
    int maxGenerations;
    int currentGeneration;
    std::map<std::string, std::string> rules;

public:
    LSystem(std::string axiom, float length, float angle, sf::Vector2f start, int maxGenerations, std::map<std::string, std::string> rules)
        : axiom(axiom), sentence(axiom), length(length), angle(angle), startPoint(start), rules(rules), maxGenerations(maxGenerations), currentGeneration(0) {}

    void generate()
    {
        if (currentGeneration >= maxGenerations)
        {
            return;
        }
        std::string nextSentence;
        for (char c : sentence)
        {
            std::string currentChar(1, c);
            if (rules.find(currentChar) != rules.end())
            {
                nextSentence += rules[currentChar];
            }
            else
            {
                nextSentence += currentChar;
            }
        }
        sentence = nextSentence;
        length *= 0.5f;
        currentGeneration++;
    }

    void draw(sf::RenderWindow &window)
    {
        std::stack<sf::Vector2f> positionStack;
        std::stack<float> angleStack;

        sf::Vector2f currentPosition = startPoint;
        float currentAngle = -90.0f; // initially upward

        for (char c : sentence)
        {
            if (c == 'F')
            {
                float rad = radians(currentAngle);
                sf::Vector2f nextPosition = currentPosition + sf::Vector2f(length * cos(rad),
                                                                           length * sin(rad));

                sf::Vertex line[] = {
                    sf::Vertex(currentPosition),
                    sf::Vertex(nextPosition)};

                window.draw(line, 2, sf::Lines);
                currentPosition = nextPosition;
            }
            else if (c == '+')
            {
                currentAngle += angle;
            }
            else if (c == '-')
            {
                currentAngle -= angle;
            }
            else if (c == '[')
            {
                positionStack.push(currentPosition);
                angleStack.push(currentAngle);
            }
            else if (c == ']')
            {
                currentPosition = positionStack.top();
                positionStack.pop();
                currentAngle = angleStack.top();
                angleStack.pop();
            }
        }
    }

    int getGeneration() const
    {
        return currentGeneration;
    }

    int getMaxGenerations() const
    {
        return maxGenerations;
    }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "L-System");
    window.setFramerateLimit(60);

    std::map<std::string, std::string> rules;
    rules["F"] = "F+F-F-FF+F+F-F";
    LSystem lsystem("F", 50.0f, 90.0f, sf::Vector2f(400.0f, 500.0f), 10, rules);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (lsystem.getGeneration() < lsystem.getMaxGenerations())
                    lsystem.generate();
            }
        }

        window.clear(sf::Color::Black);
        lsystem.draw(window);
        window.display();
    }

    return 0;
}

// g++ 1.cpp  -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system