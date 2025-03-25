#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#include "angel.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "freeglut.lib")

GLuint program;
GLuint vao, vbo;

int mode = 0;
bool paused = false;
bool colorToggle = true;
float shipAngle = 0.0f;
float stationAngle = 0.0f;
float shipPosX = 0.0f;

void setProjection() {
    GLint projLoc = glGetUniformLocation(program, "proj");
    GLfloat proj[16] = {
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, -1.0f, -1.0f,
        0, 0, -2.0f, 0
    };
    glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
}

void sendColor(GLfloat r, GLfloat g, GLfloat b) {
    GLuint colorLoc = glGetUniformLocation(program, "triangleColor");
    GLfloat color[4] = { r, g, b, 1.0f };
    glUniform4fv(colorLoc, 1, color);
}

void drawTerrain() {
    GLfloat verts[] = { -0.9f, -0.9f, -0.5f, -0.1f, 0.0f, -0.3f, 0.5f, 0.2f, 0.9f, -0.7f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    // Yükseklik bazlı renklendirme
    for (int i = 0; i < 5; ++i) {
        if (verts[i * 2 + 1] > 0.1f) sendColor(1.0f, 1.0f, 1.0f); // beyaz
        else if (verts[i * 2 + 1] > -0.2f) sendColor(0.0f, 1.0f, 0.0f); // yeşil
        else sendColor(0.5f, 0.25f, 0.0f); // kahverengi
        glDrawArrays(GL_POINTS, i, 1);
    }
    glDrawArrays(GL_LINE_STRIP, 0, 5);
}

void drawShip() {
    GLfloat verts[] = { -0.1f, -0.1f, 0.1f, -0.1f, 0.0f, 0.2f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glPushMatrix();
    glTranslatef(shipPosX, 0.0f, 0);
    glRotatef(shipAngle, 0, 0, 1);
    sendColor(colorToggle ? 0.0f : 0.0f, colorToggle ? 1.0f : 0.0f, colorToggle ? 0.0f : 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();
}

void drawStation() {
    GLfloat verts[] = { -0.15f, -0.15f, 0.15f, -0.15f, 0.15f, 0.15f, -0.15f, 0.15f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glPushMatrix();
    glRotatef(stationAngle, 0, 0, 1);
    sendColor(0.5f, 0.5f, 1.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glPopMatrix();
}

void drawPlanet() {
    const int segments = 30;
    GLfloat verts[segments * 2];
    for (int i = 0; i < segments; ++i) {
        float angle = i * 2.0f * 3.14159f / segments;
        verts[2 * i] = 0.3f * cos(angle);
        verts[2 * i + 1] = 0.3f * sin(angle);
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    sendColor(0.8f, 0.4f, 0.1f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
}

void display() {
    if (paused) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    setProjection();

    glBindVertexArray(vao);

    switch (mode) {
    case 0: drawShip(); break;
    case 1: drawPlanet(); break;
    case 2: drawStation(); break;
    }

    drawTerrain();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'c': case 'C':
        colorToggle = !colorToggle;
        mode = (mode + 1) % 3;
        break;
    case 'p': case 'P':
        paused = !paused;
        break;
    case 'a': shipAngle += 5.0f; break;
    case 'd': shipAngle -= 5.0f; break;
    case 'j': stationAngle += 5.0f; break;
    case 'k': stationAngle -= 5.0f; break;
    case 'w': shipPosX += 0.05f; break;
    case 's': shipPosX -= 0.05f; break;
    case 27: exit(0);
    }
    glutPostRedisplay();
}

void init() {
    program = Angel::InitShader("Shaders/vshader21.glsl", "Shaders/fshader21.glsl");
    glUseProgram(program);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Space Simulation");

    glewExperimental = GL_TRUE;
    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
