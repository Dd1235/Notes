#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <stack>
#include <string>
#include <cmath>

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
    float lineWidth;
    float lengthScaleFactor;
    float turningAngleIncrement;
    sf::Vector2f startPoint;
    int maxGenerations;
    int currentGeneration;
    std::map<std::string, std::string> rules;
    sf::Color fillColor;

public:
    // Constructor
    LSystem(std::string axiom, float length, float angle, sf::Vector2f start, int maxGenerations, std::map<std::string, std::string> rules)
        : axiom(axiom), sentence(axiom), length(length), angle(angle), startPoint(start), rules(rules), maxGenerations(maxGenerations), currentGeneration(0),
          lineWidth(2.0f), lengthScaleFactor(0.5f), turningAngleIncrement(10.0f), fillColor(sf::Color::White) {}

    // Generate the next generation of the L-System
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
        length *= lengthScaleFactor; // Reduce line length for each generation
        currentGeneration++;
    }

    // Draw the L-System
    void draw(sf::RenderWindow &window)
    {
        std::stack<sf::Vector2f> positionStack;
        std::stack<float> angleStack;
        std::stack<float> lineWidthStack;

        sf::Vector2f currentPosition = startPoint;
        float currentAngle = -90.0f; // Initially upward

        std::vector<sf::Vector2f> polygonPoints;

        for (char c : sentence)
        {
            if (c == 'F')
            {
                // Move forward and draw a line
                float rad = radians(currentAngle);
                sf::Vector2f nextPosition = currentPosition + sf::Vector2f(length * cos(rad), length * sin(rad));

                sf::Vertex line[] = {
                    sf::Vertex(currentPosition, sf::Color::White),
                    sf::Vertex(nextPosition, sf::Color::White)};
                window.draw(line, 2, sf::Lines);

                currentPosition = nextPosition;
            }
            else if (c == 'f')
            {
                // Move forward without drawing a line
                float rad = radians(currentAngle);
                currentPosition += sf::Vector2f(length * cos(rad), length * sin(rad));
            }
            else if (c == '+')
            {
                // Turn left
                currentAngle -= angle;
            }
            else if (c == '-')
            {
                // Turn right
                currentAngle += angle;
            }
            else if (c == '|')
            {
                // Reverse direction (turn by 180 degrees)
                currentAngle += 180.0f;
            }
            else if (c == '[')
            {
                // Push the current state onto the stack
                positionStack.push(currentPosition);
                angleStack.push(currentAngle);
                lineWidthStack.push(lineWidth);
            }
            else if (c == ']')
            {
                // Pop the current state from the stack
                currentPosition = positionStack.top();
                positionStack.pop();
                currentAngle = angleStack.top();
                angleStack.pop();
                lineWidth = lineWidthStack.top();
                lineWidthStack.pop();
            }
            else if (c == '#')
            {
                // Increment the line width
                lineWidth += 1.0f;
            }
            else if (c == '!')
            {
                // Decrement the line width
                lineWidth = std::max(1.0f, lineWidth - 1.0f);
            }
            else if (c == '@')
            {
                // Draw a dot
                sf::CircleShape dot(lineWidth);
                dot.setPosition(currentPosition - sf::Vector2f(lineWidth, lineWidth));
                dot.setFillColor(sf::Color::White);
                window.draw(dot);
            }
            else if (c == '{')
            {
                // Open a polygon
                polygonPoints.clear();
                polygonPoints.push_back(currentPosition);
            }
            else if (c == '}')
            {
                // Close a polygon and fill it
                sf::ConvexShape polygon;
                polygon.setPointCount(polygonPoints.size());
                for (size_t i = 0; i < polygonPoints.size(); ++i)
                {
                    polygon.setPoint(i, polygonPoints[i]);
                }
                polygon.setFillColor(fillColor);
                window.draw(polygon);
                polygonPoints.clear();
            }
            else if (c == '>')
            {
                // Multiply the line length
                length *= 1.1f;
            }
            else if (c == '<')
            {
                // Divide the line length
                length *= 0.9f;
            }
            else if (c == '&')
            {
                // Swap the meaning of '+' and '-'
                std::swap(angle, turningAngleIncrement);
            }
            else if (c == '(')
            {
                // Decrement turning angle
                angle -= 5.0f;
            }
            else if (c == ')')
            {
                // Increment turning angle
                angle += 5.0f;
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
    // rules["F"] = "F[+FF][-FF]F[-F][+F]F";
    // std::string axiom = "F";

    // axiom = F
    // F -> FF-[XY]+[XY]
    // X -> +FY
    // Y -> -FX
    // angle = 22.5

    //     axiom = F+F+F
    // F -> F-F+F
    // angle = 120
    std::string axiom = "F+F+F";
    rules["F"] = "F-F+F";

    LSystem lsystem(axiom, 500.0f, 120.0f, sf::Vector2f(400.0f, 550.0f), 40, rules);

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