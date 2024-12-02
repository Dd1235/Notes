
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>

const float PI = 3.14159265359f;

float degreesToRadians(float degrees)
{
    return degrees * PI / 180.0f;
}

class Branch
{
public:
    sf::Vector2f start;
    sf::Vector2f end;
    int generation;
    bool finished;
    float length;

    Branch(sf::Vector2f start_, sf::Vector2f end_, int generation)
        : start(start_), end(end_), finished(false), generation(generation)
    {
        length = this->calcLength();
    }

    void show(sf::RenderWindow &window)
    {
        sf::Vertex line[] = {
            sf::Vertex(start, sf::Color::White),
            sf::Vertex(end, sf::Color::White)};
        window.draw(line, 2, sf::Lines);
    }

    float calcLength() const
    {
        float dx = end.x - start.x;
        float dy = end.y - start.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void jitter()
    {
        float jitterAmount = std::max(0.1f, length / 50.0f);
        end.x += static_cast<float>(std::rand() % 3 - 1) * jitterAmount * 0.1;
        end.y += static_cast<float>(std::rand() % 3 - 1) * jitterAmount * 0.1;
    }

    std::pair<Branch *, Branch *> createBranches(float angle)
    {
        if (length < 4.0f)
        {
            return std::make_pair(nullptr, nullptr);
        }

        sf::Vector2f dir = end - start;

        sf::Vector2f rightDir(
            dir.x * std::cos(angle) - dir.y * std::sin(angle),
            dir.x * std::sin(angle) + dir.y * std::cos(angle));
        rightDir *= (length > 10.0f ? 0.67f : 0.9f);
        sf::Vector2f rightEnd = end + rightDir;
        Branch *right = new Branch(end, rightEnd, this->generation + 1);

        sf::Vector2f leftDir(
            dir.x * std::cos(-angle) - dir.y * std::sin(-angle),
            dir.x * std::sin(-angle) + dir.y * std::cos(-angle));

        leftDir *= (length > 10.0f ? 0.67f : 0.9f);
        sf::Vector2f leftEnd = end + leftDir;
        Branch *left = new Branch(end, leftEnd, this->generation + 1);

        return std::make_pair(left, right);
    }
};

class Leaf
{
public:
    sf::Vector2f position;      // Current position of the leaf
    sf::Vector2f prev_position; // Previous position for Verlet integration
    sf::Vector2f acceleration;  // Acceleration vector
    sf::Color color;            // Color of the leaf

    Leaf(sf::Vector2f position_)
        : position(position_), prev_position(position_), acceleration(0.0f, 0.0f)
    {
        // Set the initial random color for the leaf (pinkish-purplish)
        color = sf::Color(
            static_cast<sf::Uint8>(std::rand() % 56 + 200), // Red: High range for pink tones (200-255)
            static_cast<sf::Uint8>(std::rand() % 56 + 100), // Green: Low range for softer pink (100-155)
            static_cast<sf::Uint8>(std::rand() % 56 + 150)  // Blue: Moderate range for purplish tones (150-205)
        );

        acceleration = sf::Vector2f(0.0f, 0.1f);
    }

    void update()
    {

        sf::Vector2f temp_position = position;
        position += position - prev_position + acceleration;
        prev_position = temp_position;
        // some small horizontal shift to mimic wind
        position.x += static_cast<float>(std::rand() % 3 - 1) * 0.1f;
    }

    void show(sf::RenderWindow &window)
    {
        sf::CircleShape circle(2.0f);
        circle.setFillColor(color);
        circle.setPosition(position);
        window.draw(circle);
    }
};

class Tree
{
public:
    std::vector<Branch *> branches;
    std::vector<Leaf *> leaves;
    int maxGenerations;
    int currentGeneration;
    int minLeafGeneration;
    float angle;

    Tree(sf::Vector2f rootPosition, float initialLength, float angle_)
        : maxGenerations(10), minLeafGeneration(5), currentGeneration(0), angle(angle_)
    {
        sf::Vector2f endPosition = rootPosition - sf::Vector2f(0.0f, initialLength);
        Branch *root = new Branch(rootPosition, endPosition, 0);
        branches.push_back(root);
    }

    void generate()
    {
        if (currentGeneration >= maxGenerations)
        {
            return;
        }

        std::vector<Branch *> newBranches;
        for (auto &branch : branches)
        {
            if (!branch->finished)
            {
                auto [left, right] = branch->createBranches(angle);
                if (left)
                {
                    newBranches.push_back(left);
                }
                if (right)
                {
                    newBranches.push_back(right);
                }
                branch->finished = true;
            }
        }
        branches.insert(branches.end(), newBranches.begin(), newBranches.end());
        currentGeneration++;

        if (currentGeneration >= minLeafGeneration)
        {
            for (auto &branch : branches)
            {
                if (!branch->finished)
                {
                    Leaf *leaf = new Leaf(branch->end);
                    leaves.push_back(leaf);
                }
            }
        }
    }

    void update()
    {
        for (auto &branch : branches)
        {
            if (branch->generation >= 5)
            {
                branch->jitter();
            }
        }
        for (auto &leaf : leaves)
        {
            leaf->update();
        }
        cleanUpLeaves(branches[0]->start.y);
    }

    void show(sf::RenderWindow &window)
    {
        for (auto &branch : branches)
        {
            branch->show(window);
        }
        for (auto &leaf : leaves)
        {
            leaf->show(window);
        }
    }

    ~Tree()
    {
        for (auto &branch : branches)
        {
            delete branch;
        }
        for (auto &leaf : leaves)
        {
            delete leaf;
        }
    }

    void cleanUpLeaves(float rootY)
    {
        for (auto it = leaves.begin(); it != leaves.end();)
        {
            if ((*it)->position.y > rootY)
            {
                delete *it;
                it = leaves.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fractal Tree with Falling Leaves");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    float angle = degreesToRadians(25.0f);

    sf::Vector2f rootPosition(window.getSize().x / 2.0f, window.getSize().y - 100);
    float initialLength = 100.0f;
    Tree tree(rootPosition, initialLength, angle);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    angle += degreesToRadians(10.0f);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    angle -= degreesToRadians(10.0f);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    tree.angle = angle;
                    tree.generate();
                }
            }
        }

        tree.update();

        window.clear(sf::Color::Black);
        tree.show(window);
        window.display();
    }

    return 0;
}

// g++ fractalTree.cpp -o fractal_tree -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system