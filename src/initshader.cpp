// initshader.cpp
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#include "angel.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Angel {

    static char* readShaderSource(const char* shaderFile) {
        std::cerr << "Shader yükleniyor: " << shaderFile << std::endl;
        FILE* fp = fopen(shaderFile, "r");

        if (fp == NULL) {
            std::cerr << "Dosya açýlamadý: " << shaderFile << std::endl;
            return NULL;
        }

        fseek(fp, 0L, SEEK_END);
        long size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        char* buf = new char[size + 1];
        size_t bytesRead = fread(buf, 1, size, fp);
        if (bytesRead != size) {
            std::cerr << "UYARI: Dosya tam okunamadý! Okunan byte: " << bytesRead << " / " << size << std::endl;
        }
        buf[size] = '\0';
        fclose(fp);
        return buf;
    }

    GLuint InitShader(const char* vShaderFile, const char* fShaderFile) {
        struct Shader {
            const char* filename;
            GLenum type;
            GLchar* source;
        } shaders[2] = {
            { vShaderFile, GL_VERTEX_SHADER, NULL },
            { fShaderFile, GL_FRAGMENT_SHADER, NULL }
        };

        GLuint program = glCreateProgram();

        for (int i = 0; i < 2; ++i) {
            Shader& s = shaders[i];
            s.source = readShaderSource(s.filename);
            if (s.source == NULL) {
                std::cerr << "Shader dosyasý okunamadý: " << s.filename << std::endl;
                exit(EXIT_FAILURE);
            }

            GLuint shader = glCreateShader(s.type);
            glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
            glCompileShader(shader);
            delete[] s.source;

            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLchar log[1024];
                glGetShaderInfoLog(shader, 1024, NULL, log);
                std::cerr << s.filename << " derleme hatasý: " << log << std::endl;
                exit(EXIT_FAILURE);
            }
            glAttachShader(program, shader);
        }

        glLinkProgram(program);

        GLint linked;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked) {
            std::cerr << "Program link hatasý" << std::endl;
            exit(EXIT_FAILURE);
        }

        return program;
    }

} // namespace Angel