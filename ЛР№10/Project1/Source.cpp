#include <iostream>
#include <cmath>

// Task 1: Solving the problem with data structures

// Declaration of the TPoint structure
struct TPoint {
    double x;
    double y;
};

// Function to calculate the distance between two points
double Distance(const TPoint& p1, const TPoint& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// Function to calculate the perimeter of an N-sided polygon
double PerimN(const TPoint* P, int N) {
    double perimeter = 0.0;
    for (int i = 0; i < N; i++) {
        perimeter += Distance(P[i], P[(i + 1) % N]);
    }
    return perimeter;
}

// Task 2: Checking and calculating segment lengths

// Declaration of the structure for input and output data
struct Task2Data {
    TPoint A;
    TPoint B;
    TPoint C;
    double lengthAC;
    double lengthBC;
    double sumLengths;
};

// Function to process the Task2Data structure
void ProcessTask2Data(Task2Data& data) {
    data.lengthAC = Distance(data.A, data.C);
    data.lengthBC = Distance(data.B, data.C);
    data.sumLengths = data.lengthAC + data.lengthBC;
}

// Function to check and fill the input data in the Task2Data structure
void CheckAndFillData(Task2Data& data) {
    std::cout << "Enter the coordinates for point A:\n";
    std::cout << "x = ";
    std::cin >> data.A.x;
    std::cout << "y = ";
    std::cin >> data.A.y;

    std::cout << "Enter the coordinates for point B:\n";
    std::cout << "x = ";
    std::cin >> data.B.x;
    std::cout << "y = ";
    std::cin >> data.B.y;

    std::cout << "Enter the coordinates for point C:\n";
    std::cout << "x = ";
    std::cin >> data.C.x;
    std::cout << "y = ";
    std::cin >> data.C.y;
}

int main() {
    // Task 1: Calculating perimeters of three polygons

    const int polygonCount = 3;
    const int vertexCount = 4;
    TPoint polygons[polygonCount][vertexCount] = {
        { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0} },
        { {0.0, 0.0}, {2.0, 0.0}, {2.0, 2.0}, {0.0, 2.0} },
        { {0.0, 0.0}, {3.0, 0.0}, {3.0, 3.0}, {0.0, 3.0} }
    };

    for (int i = 0; i < polygonCount; i++) {
        double perimeter = PerimN(polygons[i], vertexCount);
        std::cout << "Perimeter of polygon " << i + 1 << ": " << perimeter << std::endl;
    }

    std::cout << std::endl;

    // Task 2: Checking and calculating segment lengths

    Task2Data task2Data;

    CheckAndFillData(task2Data);
    ProcessTask2Data(task2Data);

    std::cout << "Length of segment AC: " << task2Data.lengthAC << std::endl;
    std::cout << "Length of segment BC: " << task2Data.lengthBC << std::endl;
    std::cout << "Sum of lengths of segments AC and BC: " << task2Data.sumLengths << std::endl;

    return 0;
}
