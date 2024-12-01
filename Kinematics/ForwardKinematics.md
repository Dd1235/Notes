# Forward Kinematics 

## Introduction

Forward Kinematics (FK) is a fundamental concept in computer graphics, dealing with the computation of the position and orientation (pose) of the end-effector (e.g., a robotic arm's hand) based on given joint parameters. 

## Types of Joints

Understanding the types of joints is crucial for modeling and simulating robotic systems:

1. **Revolute Joint**: Rotates around a single axis by an angle \( q \).
2. **Universal Joint**: Rotates around two perpendicular axes by angles \( q_1 \) and \( q_2 \).
3. **Ball-and-Socket Joint**: Rotates around three axes by angles \( q_1 \), \( q_2 \), and \( q_3 \).
4. **Prismatic Joint**: Translates along an axis by a distance \( d \).

## Forward Kinematics Formulation

### 2-DOF Planar Manipulator

**Task Space**: \( \mathbf{x} = [x, y]^T \in \mathbb{R}^2 \)

**Joint Space**: \( \mathbf{q} = [q_1, q_2]^T \in \mathbb{R}^2 \)

**Forward Kinematics Equations**:

\[
\begin{align*}
x &= l_1 \cos(q_1) + l_2 \cos(q_1 + q_2) \\
y &= l_1 \sin(q_1) + l_2 \sin(q_1 + q_2)
\end{align*}
\]

**Orientation**:

\[
\theta = q_1 + q_2
\]

### 3-DOF Manipulator

**Task Space**: \( \mathbf{x} = [x, y, z]^T \in \mathbb{R}^3 \)

**Joint Space**: \( \mathbf{q} = [q_1, q_2, q_3]^T \in \mathbb{R}^3 \)

**Forward Kinematics Equations**:

\[
\begin{align*}
d &= l_2 \cos(q_2) + l_3 \cos(q_2 + q_3) \\
x &= d \cos(q_1) \\
y &= d \sin(q_1) \\
z &= l_1 + l_2 \sin(q_2) + l_3 \sin(q_2 + q_3)
\end{align*}
\]

## Transformation Matrices

Forward Kinematics can also be approached using transformation matrices, which represent rotations and translations in space. By concatenating these matrices, we can compute the pose of the end-effector.

\[
T_0^n = T_0^1 \cdot T_1^2 \cdot \ldots \cdot T_{n-1}^n
\]

Each \( T_i^{i+1} \) is a homogeneous transformation matrix representing the rotation and translation from joint \( i \) to joint \( i+1 \).

## Implementing Forward Kinematics in C++



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
    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
};

// Transformation Matrix for 2D
struct Matrix2x2 {
    float m[2][2];

    Matrix2x2(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        m[0][0] = c;  m[0][1] = -s;
        m[1][0] = s;  m[1][1] = c;
    }

    Vector2D operator*(const Vector2D& v) const {
        return Vector2D(
            m[0][0] * v.x + m[0][1] * v.y,
            m[1][0] * v.x + m[1][1] * v.y
        );
    }
};

class KinematicSegment {
public:
    float length;
    float selfAngle;   // Relative angle to parent in radians
    float angle;       // Absolute angle in radians
    Vector2D position; // Position of the base of this segment
    Vector2D endPoint; // Position of the end of this segment

    KinematicSegment* parent = nullptr;
    KinematicSegment* child = nullptr;

    KinematicSegment(float length, float angle)
        : length(length), selfAngle(angle), angle(angle), position(0.f, 0.f), endPoint(0.f, 0.f) {}

    void computeForwardKinematics() {
        if (parent) {
            angle = parent->angle + selfAngle;
            position = parent->endPoint;
        } else {
            angle = selfAngle;
            // For base segment, position could be set externally if needed
        }

        // Calculate end point
        Matrix2x2 rotation(angle);
        Vector2D dir = rotation * Vector2D(length, 0.f);
        endPoint = position + dir;

        // Recursively compute for child
        if (child) {
            child->computeForwardKinematics();
        }
    }
};

// Kinematic Chain Class
class KinematicChain {
public:
    KinematicSegment* baseSegment = nullptr;

    void addSegment(float length, float angle) {
        if (!baseSegment) {
            baseSegment = new KinematicSegment(length, angle);
        } else {
            KinematicSegment* current = baseSegment;
            while (current->child) {
                current = current->child;
            }
            KinematicSegment* newSegment = new KinematicSegment(length, angle);
            newSegment->parent = current;
            current->child = newSegment;
        }
    }

    void computeForwardKinematics() {
        if (baseSegment) {
            baseSegment->computeForwardKinematics();
        }
    }

    void updateAngles(const std::vector<float>& angles) {
        KinematicSegment* current = baseSegment;
        size_t index = 0;
        while (current && index < angles.size()) {
            current->selfAngle = angles[index];
            current = current->child;
            ++index;
        }
    }

    // Destructor to clean up
    ~KinematicChain() {
        KinematicSegment* current = baseSegment;
        while (current) {
            KinematicSegment* next = current->child;
            delete current;
            current = next;
        }
    }

    // Function to collect segment positions for rendering or other purposes
    void getSegmentPositions(std::vector<Vector2D>& positions) {
        positions.clear();
        KinematicSegment* current = baseSegment;
        while (current) {
            positions.push_back(current->position);
            current = current->child;
        }
        // Add the end point of the last segment
        if (baseSegment) {
            KinematicSegment* last = baseSegment;
            while (last->child) {
                last = last->child;
            }
            positions.push_back(last->endPoint);
        }
    }
};


int main() {
    // Create a kinematic chain with 5 segments
    KinematicChain chain;
    chain.addSegment(100.f, PI / 4); // Base segment
    chain.addSegment(80.f, PI / 6);
    chain.addSegment(60.f, PI / 8);
    chain.addSegment(50.f, PI / 10);
    chain.addSegment(40.f, PI / 12);

    // Update angles (could be dynamic in a loop)
    std::vector<float> angles = { PI / 4, PI / 6, PI / 8, PI / 10, PI / 12 };
    chain.updateAngles(angles);

    // Compute forward kinematics
    chain.computeForwardKinematics();

    // Get segment positions for rendering
    std::vector<Vector2D> positions;
    chain.getSegmentPositions(positions);

    // Output positions (for demonstration purposes)
    for (size_t i = 0; i < positions.size(); ++i) {
        std::cout << "Position " << i << ": (" << positions[i].x << ", " << positions[i].y << ")\n";
    }

    return 0;
}
```

### Explanation

**Vector2D Struct**:
- Represents a 2D vector with basic operations like addition and scalar multiplication.
- This is useful for position calculations without relying on external libraries.

**Matrix2x2 Struct**:
- Represents a 2D rotation matrix based on an angle.
- Provides a method to multiply the matrix by a `Vector2D`, effectively rotating the vector.
- Using matrices for rotations is more scalable and efficient, especially when extending to 3D.

**KinematicSegment Class**:
- Represents a single segment (or link) in the kinematic chain.
- Contains:
  - `length`: The length of the segment.
  - `selfAngle`: The relative angle of this segment with respect to its parent.
  - `angle`: The absolute angle in the world coordinate system.
  - `position`: The position of the base of this segment.
  - `endPoint`: The position of the end of this segment.
  - `parent` and `child` pointers to navigate the kinematic chain.

- **Methods**:
  - `computeForwardKinematics()`: Recursively computes the absolute angles and positions of the segment and its child segments.
    - If the segment has a parent, it calculates its absolute angle by adding its `selfAngle` to the parent's `angle`.
    - The `position` is set to the `endPoint` of the parent.
    - The `endPoint` is calculated by rotating a vector of length `length` using the absolute `angle` and adding it to the `position`.
    - If the segment has a child, it calls `computeForwardKinematics()` on the child.

**KinematicChain Class**:
- Manages the entire kinematic chain.
- Contains a pointer to the `baseSegment`.
- **Methods**:
  - `addSegment(float length, float angle)`: Adds a new segment to the chain.
    - If there is no base segment, it creates one.
    - Otherwise, it traverses to the end of the chain and adds a new segment as the child of the last segment.
  - `computeForwardKinematics()`: Starts the computation from the base segment.
  - `updateAngles(const std::vector<float>& angles)`: Updates the `selfAngle` of each segment in the chain.
  - `getSegmentPositions(std::vector<Vector2D>& positions)`: Collects the positions of each segment's base for rendering or other purposes.
  - Destructor cleans up the allocated memory for segments.

**Main Function**:
- Demonstrates how to use the `KinematicChain` class.
- Creates a chain of 5 segments with specified lengths and initial angles.
- Updates the angles (this could be dynamic in a real application).
- Computes the forward kinematics to update positions.
- Retrieves the positions for rendering or other purposes.
- Outputs the positions to the console.

### Separation of Logic and Rendering

- **Logic**: All the kinematic computations are encapsulated within the `KinematicSegment` and `KinematicChain` classes.


## Notes on simulating later


- **Communication**: Use serial communication to send joint parameters from the computer to the Arduino.
- **Actuation**: Map the joint angles to servo positions.
- **Feedback**: Optionally, implement sensors to provide feedback to the computer for closed-loop control.



## Further Reading

- [Denavit-Hartenberg Parameters](https://en.wikipedia.org/wiki/Denavit%E2%80%93Hartenberg_parameters)
- [Robot Modeling and Control](http://hades.mech.northwestern.edu/index.php/Modern_Robotics)

