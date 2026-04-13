#pragma once
#include <glad/glad.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "stb_image.h"

struct UVRect
{
    float u, v;   // 좌하단 (Min UV)
    float uw, vh; // 우상단 (Max UV)
    float ratio;  // (w / h) 비율
};

class Texture
{
public:
    unsigned int ID;
    int width, height, nrChannels;
    std::map<std::string, UVRect> uvMap;

    Texture(const std::string &imagePath, const std::string &jsonPath = "")
    {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        // 픽셀 아트의 선명함을 유지하기 위한 기본 설정 (GL_NEAREST)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_set_flip_vertically_on_load(true);

        unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture at: " << imagePath << std::endl;
        }
        stbi_image_free(data);

        if (!jsonPath.empty())
        {
            LoadAtlasData(jsonPath);
        }
    }

    // JSON에서 프레임 정보를 읽어와 UV 맵을 구성
    void LoadAtlasData(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "Failed to open JSON: " << path << std::endl;
            return;
        }

        json data;
        file >> data;
        file.close();

        uvMap[""] = {0.0f, 0.0f, 1.0f, 1.0f, (float)width / height}; // 전체 텍스처 UV

        for (auto &frameData : data["frames"])
        {
            std::string name = frameData["name"];
            auto frame = frameData["frame"];

            float x = frame["x"];
            float y = frame["y"];
            float w = frame["w"];
            float h = frame["h"];

            // OpenGL UV 계산 (stbi_set_flip_vertically_on_load(true) 대응)
            // JSON의 y는 위에서 아래로 내려오지만,
            // 텍스처 데이터가 뒤집혔으므로 계산 시 상하 반전을 고려
            UVRect rect;
            rect.u = x / (float)width;
            rect.v = (height - (y + h)) / (float)height; // 하단 UV
            rect.uw = (x + w) / (float)width;
            rect.vh = (height - y) / (float)height; // 상단 UV
            rect.ratio = w / h;

            uvMap.insert(std::make_pair(name, rect));
        }
        std::cout << "Loaded " << uvMap.size() << " sprites from atlas." << std::endl;
    }

    UVRect GetUV(const std::string &name = "") const
    {
        if (name.empty())
            return uvMap.at(""); // 전체 텍스처 UV 반환
        if (uvMap.find(name) != uvMap.end())
            return uvMap.at(name);
        std::cerr << "UV not found for: " << name << std::endl;
        return uvMap.at(""); // 전체 텍스처 UV 반환
    }

    float GetAspectRatio(const std::string &name = "") const
    {
        if (name.empty())
            return uvMap.at("").ratio;
        if (uvMap.find(name) != uvMap.end())
            return uvMap.at(name).ratio;
        std::cerr << "UV not found for: " << name << std::endl;
        return uvMap.at("").ratio; // 전체 텍스처 비율 반환
    }

    ~Texture()
    {
        glDeleteTextures(1, &ID);
    }

    void Bind(unsigned int unit = 0) const
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};