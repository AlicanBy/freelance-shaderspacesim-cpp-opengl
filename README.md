# Shader-Based Space Simulation (Freelance Practice Project)

🚀 **Project Overview**

This project is a simple shader-based 3D space simulation built using modern OpenGL (version 3.2+), written in C++.  
It was initially developed as a freelance assignment with a tight deadline. Although the project was not fully completed, it demonstrates core implementations of shader logic, object transformation, and animation basics.  
It is archived here as a real-world freelance experience and a learning milestone in shader programming.

---

## 🔧 Technologies Used

- C++
- OpenGL 3.2+
- GLSL (Shader Language)
- FreeGLUT
- GLEW
- Visual Studio (2019 or later)

---

## 🕹 Controls

| Key | Action |
|-----|--------|
| `a / d` | Rotate the spaceship left/right |
| `j / k` | Rotate the space station |
| `w / s` | Move the spaceship forward/backward |
| `p` | Pause/resume animation |
| `o` | Single-step animation |
| `c` | Change color / rendering mode |
| `ESC` | Exit simulation |

---

Work In Progress / Areas for Improvement


- Terrain generation is not fully implemented

- MVP (Model-View-Projection) matrix logic is kept simple for now

- Lighting uses beginner-level Gouraud shading

- No advanced camera movement or fullscreen toggle yet

- These aspects are open to improvement and are planned for future development in a more complete version of the project.

---

Screenshots

You can find screenshots in the screenshots/ folder.
(Note: This section will be updated with visual references.)

---

Freelance Project Note

- This project was developed as part of a freelance university assignment.
- Due to deadline constraints and scope changes, the delivered version represents about 60-65% of the intended functionality.
- Nevertheless, it serves as a valuable learning experience in shader-based rendering, OpenGL pipeline management, and freelance project execution.

---


## 🛠 How to Build & Run

**Requirements:**

- Visual Studio (2019 or later)
- GLEW & FreeGLUT libraries
- Shader files must be located inside the `shaders/` directory

**To compile using g++:**

```bash
g++ src/main.cpp src/initshader.cpp -o ShaderSim.exe -lglew32 -lfreeglut -lopengl32
