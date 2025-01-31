#include <iostream>
#include <thread>
#include <math.h>
#include <cmath>
#include "raylib.h"
using namespace std;

struct CustomVector {
    float x;
    float y;
};

// Legacy code to run it only in console. But console can't handle event like mouse click, so use graph design
void drawMatrix(CustomVector firstPoint, CustomVector secondPoint) {
    const int matrixSizeX = 25;
    const int matrixSizeY = 50;

    for (int i = 1; i <= matrixSizeX; i++) {
        for (int j = 1; j <= matrixSizeY; j++) {
            if (firstPoint.x == i && firstPoint.y == j || secondPoint.x == i && secondPoint.y == j) {
                cout << "@";
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }

}

CustomVector getNormalaziedVector(CustomVector firstPoint, CustomVector secondPoint){
     CustomVector resultVector = { secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y };



    float resultVectorModule = sqrt((resultVector.x * resultVector.x) + (resultVector.y * resultVector.y));

    if (resultVectorModule < 0.01f) {
        return CustomVector{0.01f, 0.01f};
    }

    CustomVector normalizedVector = { resultVector.x / resultVectorModule, resultVector.y / resultVectorModule };

    return normalizedVector;
}

CustomVector calculateMovementForPoint(CustomVector firstPoint, CustomVector secondPoint, float speed) {

    CustomVector normalizedVector = getNormalaziedVector(firstPoint, secondPoint);
    return CustomVector{ firstPoint.x + normalizedVector.x * speed,firstPoint.y + normalizedVector.y * speed };
}

bool isVectorHasSameCoords  (CustomVector firstPoint, CustomVector secondPoint){
    return firstPoint.x == secondPoint.x && firstPoint.y == secondPoint.y;
}

void drawCharacter(CustomVector characterPosition, CustomVector rotation, float characterSize, Color color) {
    float wayLineLength = 10.0f + characterSize;
    DrawLine(characterPosition.x, characterPosition.y,  characterPosition.x + rotation.x * wayLineLength, characterPosition.y + rotation.y * wayLineLength, BLUE);
    DrawCircle(characterPosition.x, characterPosition.y, characterSize, color);
}

void drawGuard(CustomVector guardPosition, float guardSize, float currentTime, Color color) {
    float fovDistance = 20.0f + guardSize;
    float fovDigrese = 60.0f;
    float fovHalfRadians = (fovDigrese / 2) * (PI / 180.0f);
    DrawCircle(guardPosition.x, guardPosition.y, guardSize, GRAY);
    CustomVector fovPosition = { guardPosition.x + cos(currentTime) * fovDistance, guardPosition.y + sin(currentTime) * fovDistance };
    Vector2 firstTriangleAngle = {
        fovPosition.x + cos(currentTime + fovHalfRadians) * fovDistance,
        fovPosition.y + sin(currentTime + fovHalfRadians) * fovDistance
    };
    Vector2 secondTriangleAngle = {
        fovPosition.x + cos(currentTime - fovHalfRadians) * fovDistance,
        fovPosition.y + sin(currentTime - fovHalfRadians) * fovDistance
    };
    Vector2 formattedGuardPosition = { guardPosition.x, guardPosition.y };
    DrawTriangle(formattedGuardPosition, firstTriangleAngle, secondTriangleAngle, YELLOW);
}

int main() {

    int windowWidth = 800;
    int windowHeight = 600;


    float speed = 1;
    float pointSize = 10;
    float guardSize = 20.0f;
    CustomVector firstPoint = { 25, 25 };
    CustomVector secondPoint = { 150, 150 };
    CustomVector rotation = { 0, 0 };

    CustomVector guardPosition = { 300, 300 };
    float guardRotationSpeed = 1.0f;


    InitWindow(windowWidth, windowHeight, "Raylib Test");


    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            secondPoint.x = mousePos.x;
            secondPoint.y = mousePos.y;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (!isVectorHasSameCoords(firstPoint, secondPoint)) {
            
            float frameTime = GetFrameTime();
            firstPoint = calculateMovementForPoint(firstPoint, secondPoint, speed * frameTime * 200);
             rotation = getNormalaziedVector(firstPoint, secondPoint);
            drawCharacter(firstPoint, rotation, pointSize, GREEN);
        }
        DrawCircle(secondPoint.x, secondPoint.y, pointSize, RED);
        drawGuard(guardPosition, guardSize, GetTime(), GRAY);



        EndDrawing();
    }


    CloseWindow();

    return 0;

}