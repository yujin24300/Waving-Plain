# Waving-Plain

## 📝 Overview
This project implements a dynamically animated plane with wave and rotation effects using OpenGL and GLSL shaders. The plane responds to keyboard inputs for interactive control over animation, tessellation, and wave parameters.
![](https://github.com/yujin24300/Waving-Plain/blob/main/Waving-Plain1.jpg)| ![](https://github.com/yujin24300/Waving-Plain/blob/main/Waving-Plain2.jpg)
---|---|


## ✨ Features
- **Checkerboard Plane**: Renders a dynamically tessellated checker-patterned plane using the `MyPlain` class, with vertices, colors, and buffers managed in C++ and drawn via OpenGL.
- **Wave Effect**: Press [w] to toggle a center-originating, time-based sine wave effect applied **entirely in the vertex shader**. The wave amplitude exponentially decays with distance from the center.
- **Interactive Animation**: Press [Space] to start/stop **continuous counter-clockwise rotation** (around z-axis) and **waving** of the plane. Animation is time-synchronized and pauses/resumes on key press.
- **Dynamic Tessellation**: Press [1] to **increase** and [2] to **decrease** the number of divisions in the plane, updating the mesh resolution in real time.
- **Quit**: Press [q] to exit the application.


## ⚙️ Implementation Details
- **Main loop**: Handles OpenGL initialization, window creation, and event loop.
- **MyPlain class**: Manages plane geometry, buffer allocation, and shader data binding.
- **Shaders**: Vertex shader applies wave/rotation; fragment shader calculates color from z-value.
- **Wave calculation**: `sin(frequency * distance + time) * amplitude * exp(-distance)`, clamped beyond threshold.
- **Rotation**: 90° x-axis tilt + z-axis rotation (time-based).
- **Colors**: Normalized |z| * 4 to intensify orange/blue interpolation.


## 🚀 Trouble Shooting
- **Axis Confusion in Rotation**: Initially misapplied rotation matrices for x, y, z axes, causing incorrect tilting and rotation. Debugged with separate axis tests and fixed by applying *90° x-axis tilt* first, then time-based *z-axis rotation*.
- **Wave-Time Synchronization**: Used a redundant variable (`myWave`) for time, which caused unwanted wave motion even when paused. Simplified to a single `myTime` variable, incremented only when `bPlay` is true.
- **Unnatural Wave Attenuation**: Applied linear distance-based attenuation, resulting in unrealistic wave decay. Switched to *exponential attenuation* (`exp(-distance)`), producing more natural waves.
- **Uncontrolled Wave Boundary**: Even with exponential decay, slight waves remained at the plane edges. Set wave amplitude to zero beyond a certain distance threshold.
- **Fuzzy Color Interpolation**: Misinterpreted z-coordinate sign and normalization, causing faded or reversed gradients. Fixed by taking the *absolute value of z*, normalizing, then scaling by 4 for vivid orange-blue gradients.
- **Mesh Not Updating on Division Change**: Changing the division count did not immediately update the mesh. Fixed by calling `init()` after each `increase()`/`decrease()` to regenerate vertices and buffers.
