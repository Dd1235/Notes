#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

// Helper function to convert polar coordinates to Cartesian (for circular layout)
pair<float, float> polarToCartesian(float radius, float angleDegrees)
{
    float angleRadians = angleDegrees * M_PI / 180.0f;
    return {radius * cos(angleRadians), radius * sin(angleRadians)};
}

void drawArrow(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end, float arrowSize = 10, float circleRadius = 15)
{
    // Compute direction vector
    sf::Vector2f direction = end - start;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normalize

    // Stop line at the edge of the target circle
    sf::Vector2f adjustedEnd = end - direction * circleRadius;

    // Draw the line
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(adjustedEnd, sf::Color::White)};
    window.draw(line, 2, sf::Lines);

    // Compute perpendicular vector for arrowhead
    sf::Vector2f perpendicular(-direction.y, direction.x);

    // Arrowhead points
    sf::Vector2f arrowPoint1 = adjustedEnd - direction * arrowSize + perpendicular * (arrowSize / 2.0f);
    sf::Vector2f arrowPoint2 = adjustedEnd - direction * arrowSize - perpendicular * (arrowSize / 2.0f);

    sf::ConvexShape arrowHead;
    arrowHead.setPointCount(3);
    arrowHead.setPoint(0, adjustedEnd);
    arrowHead.setPoint(1, arrowPoint1);
    arrowHead.setPoint(2, arrowPoint2);
    arrowHead.setFillColor(sf::Color::Red); // Use a distinct color for visibility

    // Draw the arrowhead
    window.draw(arrowHead);
}

// Function to visualize a graph using SFML
void drawGraph(const vector<vector<int>> &adjList, int windowWidth = 800, int windowHeight = 800)
{
    int numNodes = adjList.size();
    if (numNodes == 0)
    {
        cerr << "Graph is empty, nothing to display." << endl;
        return;
    }

    // Dynamically adjust radius based on the number of nodes to ensure it fits on screen
    float radius = min(windowWidth, windowHeight) * 0.4f / (1.0f + numNodes / 10.0f); // Adjust radius as nodes grow
    sf::Vector2f center(windowWidth / 2.0f, windowHeight / 2.0f);                     // Center of the window

    // Map to store positions of each node
    map<int, sf::Vector2f> nodePositions;

    // Calculate positions for each node
    for (int i = 0; i < numNodes; i++)
    {
        float angle = 360.0f / numNodes * i;
        auto [x, y] = polarToCartesian(radius, angle);
        nodePositions[i] = sf::Vector2f(center.x + x, center.y + y);
    }

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Graph Visualization");

    // Main rendering loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw edges (with arrows)
        for (int i = 0; i < numNodes; i++)
        {
            for (int neighbor : adjList[i])
            {
                drawArrow(window, nodePositions[i], nodePositions[neighbor]);
            }
        }

        // Draw nodes
        for (int i = 0; i < numNodes; i++)
        {
            sf::CircleShape circle(15); // Each node is a circle with radius 15
            circle.setFillColor(sf::Color::Blue);
            circle.setPosition(nodePositions[i].x - 15, nodePositions[i].y - 15); // Center the circle
            window.draw(circle);

            // Label the nodes with their index
            sf::Font font;
            if (!font.loadFromFile("Arial.ttf"))
            {
                cerr << "Error loading font!" << endl;
                return;
            }
            sf::Text text;
            text.setFont(font);
            text.setString(to_string(i));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            text.setPosition(nodePositions[i].x - 10, nodePositions[i].y - 10);
            window.draw(text);
        }

        window.display();
    }
}
