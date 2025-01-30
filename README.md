# Vector Movement Project

Hello! I am **AnimeManna**. It's nice to see you on my page!

This is a small C++ project that uses native C++ for calculate position and operations with vectors and using **Raylib** to render, handle click event and animate objects. It demonstrates how a ball moves toward a point clicked by the user.

---

## 🚀 How to Run the Project

### 1. **Clone the Repository**
```sh
git clone https://github.com/AnimeManna/vector-movement.git
cd vector-movement
```
2. Open the Project in Visual Studio
Launch Visual Studio.
Open the solution file (.sln) located in the root of the project.
3. Install Dependencies
This project uses the Raylib library installed via vcpkg.

If you don't have vcpkg, install it with the following commands:

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # For Windows
./bootstrap-vcpkg.sh   # For Linux/Mac
```
Install Raylib using vcpkg:
```sh
vcpkg install raylib
```
Integrate vcpkg with Visual Studio:
```sh
vcpkg integrate install
```
4. Build the Project
In Visual Studio, press Ctrl + Shift + B to build the project.
Make sure the build configuration is set to Release or Debug.
5. Run the Project
After a successful build, press Ctrl + F5 or click "Start Without Debugging".
A window will open showing two circles. The green circle moves toward the red one, which you can reposition by clicking anywhere in the window.
## 🛠 Project Features

- **Dynamic movement of objects.**
- **Mouse click handling.**
- **Rendering of primitives using Raylib.**


## 💡 Code Example
Here is the main function that calculates the movement of the point:
```cpp
void calculateMovementForPoint(float firstPoint[2], int secondPoint[2], float speed) {
    float resultVector[2] = { (float)secondPoint[0] - firstPoint[0], (float)secondPoint[1] - firstPoint[1] };

    float resultVectorModule = sqrt((resultVector[0] * resultVector[0]) + (resultVector[1] * resultVector[1]));

    if (resultVectorModule < 0.01f) {
        return;
    }

    float normalizedVector[2] = { resultVector[0] / resultVectorModule, resultVector[1] / resultVectorModule };

    firstPoint[0] += normalizedVector[0] * speed;
    firstPoint[1] += normalizedVector[1] * speed;
}
```
## 📚 Useful Links
Raylib Documentation
vcpkg Documentation
###✨ Thank You
Thank you for visiting! If you liked the project, feel free to star ⭐ the repository and follow me for more updates!

