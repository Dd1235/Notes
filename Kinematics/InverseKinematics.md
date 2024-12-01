# Inverse Kinematics

The idea of forward kinematics was to determine the position of the end effector given the joint angles. Inverse, well does the "inverse". It determines the joint angles given the position of the end effector.

## Pseudo Code
```
class Segment {
    // a->b b is the head, pointing towards the target
    PVector a;
    PVector b = new PVector();
    float angle;
    float length;

    Segment parent = null;
    Segment child= null;

    Segment(float x, float y, float angle_, float len_){
        ...
    }
    Segment(Segment parent_, float angle_, float len_){
        parent = parent_;
        a = parent.b.copy();
        len = len_;
        angle = angle_;
        calculateB();
        
    }

    void calculateB(){
        float dx = len * cos(angle);
        float dy =  len*sin(angle);
        b.set(a.x + dx, a.y + dy);
    }

    void update(){
        calculateB();
    }

    void follow(float targetX, float targetY){
        PVector traget = new PVector(targetX, targetY);
        PVector dir = PVector.sub(target, a);
        angle = arctan(dir.y, dir.x);

        // logic so that B is at the target, and A is at the correct distance from B
    }
    void follow(){
        follow(child.a.x, child.a.y);
    }
    void follow(Segment child){
        follow(child.a.x, child.a.y);
    }

    void show(){
        // make a line between a and b, vary the stroke color and weight based on which segment it is
    } 
    void setA(PVector base){
        a = base.copy();
        calculateB();
    }
  
}
```

```
@REM Segment seg1; // -> this guy still comes first
@REM Segment seg2; // -> this iwll be following the mouse
Segment[] tentacle;
void setup(){
    size(...);
    @REM seg1 = new Segment(start, end, angle, length);
    @REM seg2 = new Segment(seg1, angle2, length2);
    @REM seg1.child = seg2;
    tentacle[0] = new Segment(st, end, angle, length);
    for(int i= 1; i < 3; i++){
        tentacle[i] = new Segment[tentacle[i-1], angle, len, i]; 
        // no need of child and parent now
    }
    PVector base = new PVecto(width/2, height);
}

void draw(){
    background(..);
    @REM seg1.follow(mouseX, mouesY);
    @REM seg1.update();
    @REM segment2.update();
    @REM seg1.show();
    @REM seg2.follow(mouseX, mouseY);
    @REM seg1.follow(seg1.child.a.x, seg1.child.a.y);
    int total = tentacle.length;
    Segment end = tentacle[tentacle.length - 1];
    end.follow(mouseX, mouseY);
    tentacle.update();

    tentacle[0].setA(base);


    for(int i = total - 2; i >= 0; i--){
        tentacle[i].follow(tentacle[i+1]);
        tentacle[i].update();
    }
    // a0->b0 a1->b1 a2->b2 target
    for(int i = 1; i < total; i++){
        tentacle[i].setA(total[i-1].b);
    }
    for(int i = 0; i < total; i++){
        tentacle[i].show();
    }


}
```


## CPP Implementation

- **Vector2D Struct**: Represents 2D vectors with necessary operations.
- **Segment Class**: Represents each segment in the kinematic chain, with methods for inverse kinematics.
- **Main Program**: Demonstrates how to use the classes, updates the kinematics, and shows how to collect positions for rendering.

## Code

```cpp
#include <iostream>
#include <vector>
#include <cmath>

// Constants
const float PI = 3.14159265359f;

// Vector2D Struct
struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.f), y(0.f) {}
    Vector2D(float x_, float y_) : x(x_), y(y_) {}

    // Vector addition
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    // Vector subtraction
    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    // Scalar multiplication
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Vector length
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize the vector
    void normalize() {
        float len = length();
        if (len != 0.f) {
            x /= len;
            y /= len;
        }
    }

    // Return a normalized vector
    Vector2D normalized() const {
        float len = length();
        if (len != 0.f) {
            return Vector2D(x / len, y / len);
        } else {
            return Vector2D(0.f, 0.f);
        }
    }

    // Get the angle of the vector
    float angle() const {
        return std::atan2(y, x);
    }

    // Set vector components
    void set(float x_, float y_) {
        x = x_;
        y = y_;
    }
};

// Segment Class
class Segment {
public:
    Vector2D a;     // Start point
    Vector2D b;     // End point
    float angle;    // Angle of the segment in radians
    float length;   // Length of the segment
    Segment* parent;
    Segment* child;

    // Constructor for base segment
    Segment(float x, float y, float length_, float angle_)
        : a(x, y), length(length_), angle(angle_), parent(nullptr), child(nullptr) {
        calculateB();
    }

    // Constructor for child segments
    Segment(Segment* parent_, float length_, float angle_)
        : length(length_), angle(angle_), parent(parent_), child(nullptr) {
        parent_->child = this;
        a = parent_->b;
        calculateB();
    }

    // Calculate the end point 'b' based on 'a', 'length', and 'angle'
    void calculateB() {
        float dx = length * std::cos(angle);
        float dy = length * std::sin(angle);
        b.set(a.x + dx, a.y + dy);
    }

    // Update the segment (recalculate 'b')
    void update() {
        calculateB();
    }

    // Adjust the segment to follow a target position
    void follow(float targetX, float targetY) {
        Vector2D target(targetX, targetY);
        Vector2D dir = target - a;
        angle = std::atan2(dir.y, dir.x);

        // Move 'a' to be at the correct distance from the target
        dir = dir.normalized();
        dir = dir * (-length);
        a = target + dir;

        calculateB();
    }

    // Overloaded 'follow' to accept a Vector2D
    void follow(const Vector2D& target) {
        follow(target.x, target.y);
    }

    // Overloaded 'follow' to follow another segment
    void follow(Segment* child_) {
        follow(child_->a.x, child_->a.y);
    }

    // Set the start point 'a' and recalculate 'b'
    void setA(const Vector2D& base) {
        a = base;
        calculateB();
    }
};

// Function to collect segment positions for rendering
struct SegmentPosition {
    Vector2D a;
    Vector2D b;
};

std::vector<SegmentPosition> getSegmentPositions(const std::vector<Segment*>& tentacle) {
    std::vector<SegmentPosition> positions;
    for (Segment* segment : tentacle) {
        positions.push_back({ segment->a, segment->b });
    }
    return positions;
}

// Main Function
int main() {
    // Base position (could be the shoulder of a robotic arm)
    Vector2D base(400.f, 300.f); // Example base position

    // Create a chain of segments (e.g., a tentacle with 10 segments)
    int numSegments = 10;
    float segmentLength = 20.f;
    std::vector<Segment*> tentacle;

    // Create the first segment
    Segment* baseSegment = new Segment(base.x, base.y, segmentLength, 0.f);
    tentacle.push_back(baseSegment);

    // Create subsequent segments
    for (int i = 1; i < numSegments; ++i) {
        Segment* prevSegment = tentacle.back();
        Segment* newSegment = new Segment(prevSegment, segmentLength, 0.f);
        tentacle.push_back(newSegment);
    }

    // Example target position (could be updated dynamically)
    Vector2D target(600.f, 400.f);

    // Update the tentacle to follow the target
    // Make the end segment follow the target
    Segment* endSegment = tentacle.back();
    endSegment->follow(target.x, target.y);

    // For each segment from the end to the start, make it follow its child
    for (int i = tentacle.size() - 2; i >= 0; --i) {
        tentacle[i]->follow(tentacle[i + 1]);
    }

    // For each segment from the start to the end, set its start point to be the end point of the previous segment
    tentacle[0]->setA(base);
    for (int i = 1; i < tentacle.size(); ++i) {
        tentacle[i]->setA(tentacle[i - 1]->b);
    }

    // Collect positions for rendering
    std::vector<SegmentPosition> segmentPositions = getSegmentPositions(tentacle);

    // Output positions (for demonstration purposes)
    for (size_t i = 0; i < segmentPositions.size(); ++i) {
        std::cout << "Segment " << i << ": A(" << segmentPositions[i].a.x << ", " << segmentPositions[i].a.y
                  << ") B(" << segmentPositions[i].b.x << ", " << segmentPositions[i].b.y << ")\n";
    }

    // Clean up
    for (Segment* segment : tentacle) {
        delete segment;
    }

    return 0;
}
```

## Explanation

### Vector2D Struct

- **Purpose**: Represents a 2D vector with x and y components.
- **Operations**:
  - Addition and subtraction of vectors.
  - Scalar multiplication.
  - Calculating length and normalization.
  - Calculating the angle of the vector using `atan2`.
- **Usage**: Used for positions and direction calculations in the kinematics.

### Segment Class

- **Members**:
  - `a`: Start point of the segment.
  - `b`: End point of the segment.
  - `angle`: The angle of the segment in radians.
  - `length`: The length of the segment.
  - `parent` and `child`: Pointers to navigate the kinematic chain.
- **Methods**:
  - **Constructor**: Initializes the segment, either as a base segment or as a child of another segment.
  - **calculateB()**: Calculates the end point `b` based on the start point `a`, length, and angle.
  - **update()**: Recalculates the end point `b`. Useful if `a` or `angle` has changed.
  - **follow()**: Adjusts the segment's angle and position so that it points towards a target position. Moves the segment so that its end point `b` reaches the target, and its start point `a` is at the correct distance.
  - **setA()**: Sets the start point `a` and recalculates the end point `b`.

### Main Program Logic

- **Initialization**:
  - Sets a base position for the kinematic chain.
  - Creates a chain of segments (the tentacle) with specified lengths.
- **Inverse Kinematics Update**:
  - The end segment follows the target position.
  - Each segment from the end to the start follows its child, adjusting its angle.
  - Each segment from the start to the end updates its start point `a` to be the end point `b` of the previous segment, ensuring continuity.
- **Rendering Preparation**:
  - Collects the positions of each segment for rendering.
  - Positions are stored in a `SegmentPosition` struct for easy access.
- **Output**:
  - For demonstration purposes, the positions are printed to the console.
  - In a real application, these positions would be passed to a rendering system.


## Integration with Rendering Systems

### Passing Coordinates to JavaScript or Java

- **Data Serialization**:
  - The collected positions can be serialized into JSON or any other format suitable for the target rendering system.

```cpp
// Example of serializing positions to JSON (pseudo-code)
std::string serializePositionsToJSON(const std::vector<SegmentPosition>& positions) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < positions.size(); ++i) {
        oss << "{ \"a\": { \"x\": " << positions[i].a.x << ", \"y\": " << positions[i].a.y << " }, "
            << "\"b\": { \"x\": " << positions[i].b.x << ", \"y\": " << positions[i].b.y << " } }";
        if (i < positions.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}
```



### Visualization Using SFML for Testing

Below is an example of integrating the kinematic logic with SFML for visualization.

```cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Inverse Kinematics Visualization");

    // Base position
    Vector2D base(400.f, 300.f);

    // Create tentacle segments
    int numSegments = 10;
    float segmentLength = 20.f;
    std::vector<Segment*> tentacle;

    // Initialize segments
    Segment* baseSegment = new Segment(base.x, base.y, segmentLength, 0.f);
    tentacle.push_back(baseSegment);
    for (int i = 1; i < numSegments; ++i) {
        Segment* prevSegment = tentacle.back();
        Segment* newSegment = new Segment(prevSegment, segmentLength, 0.f);
        tentacle.push_back(newSegment);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        Vector2D target(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Update kinematics
        Segment* endSegment = tentacle.back();
        endSegment->follow(target.x, target.y);
        for (int i = tentacle.size() - 2; i >= 0; --i) {
            tentacle[i]->follow(tentacle[i + 1]);
        }
        tentacle[0]->setA(base);
        for (int i = 1; i < tentacle.size(); ++i) {
            tentacle[i]->setA(tentacle[i - 1]->b);
        }

        // Render
        window.clear(sf::Color::Black);
        for (Segment* segment : tentacle) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(segment->a.x, segment->a.y), sf::Color::White),
                sf::Vertex(sf::Vector2f(segment->b.x, segment->b.y), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }

    // Clean up
    for (Segment* segment : tentacle) {
        delete segment;
    }

    return 0;
}
```


## Further ideas to look into

1. You can have multiple tentacles, and say a "ball", and make the tentacles follow the ball. 
2. You can have boid like behavior, where the tentacles follow the ball, but also avoid each other.
3. You can have flocking
4. Fish in pond, etc.
