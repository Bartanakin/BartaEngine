#include <Graphics/OpenGL_Bridge/Shader.h>
#include <pch.h>

namespace Barta {

Shader::Shader(
    std::string vertexPath,
    std::string fragmentPath
) {
    std::vector<const char*> vShaderLines;
    std::vector<const char*> fShaderLines;
    try {
        std::string line;

        std::ifstream vShaderFile(vertexPath);
        while (std::getline(vShaderFile, line)) {
            line += "\n";
            auto charLine = new char[line.size() + 1];
            std::memcpy(charLine, line.c_str(), line.size());
            charLine[line.size()] = '\0';
            vShaderLines.push_back(charLine);
        }

        vShaderFile.close();

        std::ifstream fShaderFile(fragmentPath);
        while (std::getline(fShaderFile, line)) {
            line += "\n";
            auto charLine = new char[line.size() + 1];
            std::memcpy(charLine, line.c_str(), line.size());
            charLine[line.size()] = '\0';
            fShaderLines.push_back(charLine);
        }

        fShaderFile.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_READ\n" << e.what() << std::endl;
    }

    int success;
    char infoLog[512];

    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertex, vShaderLines.size(), vShaderLines.data(), nullptr);
    glCompileShader(this->vertex);
    glGetShaderiv(this->vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragment, fShaderLines.size(), fShaderLines.data(), nullptr);
    glCompileShader(this->fragment);
    glGetShaderiv(this->fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->ID = glCreateProgram();
    glAttachShader(this->ID, this->vertex);
    glAttachShader(this->ID, this->fragment);
    glLinkProgram(this->ID);
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
    }

    for (const auto& line: vShaderLines) {
        delete[] line;
    }

    for (const auto& line: fShaderLines) {
        delete[] line;
    }
}

Shader::~Shader() {}
}
