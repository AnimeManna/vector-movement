#include <iostream>
#include <thread>
#include <math.h>
#include <cmath>
#include "raylib.h"
using namespace std;


const int indexOfX = 0;
const int indexOfY = 1;

// Legacy code to run it only in console. But console can't handle event like mouse click, so use graph design
void drawMatrix(float firstPoint[2], float secondPoint[2]) {
    const int matrixSizeX = 25;
    const int matrixSizeY = 50;

    for (int i = 1; i <= matrixSizeX; i++) {
        for (int j = 1; j <= matrixSizeY; j++) {
            if (firstPoint[indexOfX] == i && firstPoint[indexOfY] == j || secondPoint[indexOfX] == i && secondPoint[indexOfY] == j) {
                cout << "@";
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }

}

void calculateMovementForPoint(float firstPoint[2], float secondPoint[2], float speed) {

    int resultVector[2] = { secondPoint[indexOfX] - firstPoint[indexOfX], secondPoint[indexOfY] - firstPoint[indexOfY] };



    double resultVectorModule = sqrt((resultVector[indexOfX] * resultVector[indexOfX]) + (resultVector[indexOfY] * resultVector[indexOfY]));

    if (resultVectorModule < 0.01f) {
        return;
    }

    double normalizedVector[2] = { resultVector[indexOfX] / resultVectorModule, resultVector[indexOfY] / resultVectorModule };

    firstPoint[indexOfX] = firstPoint[indexOfX] + normalizedVector[indexOfX] * speed;
    firstPoint[indexOfY] = firstPoint[indexOfY] + normalizedVector[indexOfY] * speed;
}

bool isArrayHasSameCoords  (float firstPoint[2], float secondPoint[2]){
    return firstPoint[indexOfX] == secondPoint[indexOfX] && firstPoint[indexOfY] == secondPoint[indexOfY];
}

int main() {

    int windowWidth = 800;
    int windowHeight = 600;


    float speed = 1;
    float firstPoint[2] = { 25, 25 };
    float secondPoint[2] = { 150, 150 };
    float pointSize = 10;

    InitWindow(windowWidth, windowHeight, "Raylib Test");


    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            secondPoint[indexOfX] = mousePos.x;
            secondPoint[indexOfY] = mousePos.y;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!isArrayHasSameCoords(firstPoint, secondPoint)) {
            
            float frameTime = GetFrameTime();
            calculateMovementForPoint(firstPoint, secondPoint, speed * frameTime * 200);
        }

        DrawCircle(firstPoint[indexOfX], firstPoint[indexOfY], pointSize, GREEN);
        DrawCircle(secondPoint[indexOfX], secondPoint[indexOfY], pointSize, RED);



        EndDrawing();
    }


    CloseWindow();

    return 0;

}