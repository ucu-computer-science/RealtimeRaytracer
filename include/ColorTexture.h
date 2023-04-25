#pragma once

#ifndef RAYTRACER_COLORTEXTURE_H
#define RAYTRACER_COLORTEXTURE_H

#include "Color.h"
#include <iostream>
#include <vector>

struct ColorTexture {
private:
    bool load_image(std::vector<uint8_t> &image, const std::string &filename);

public:
    std::vector<Color> bitmap;
    int width{}, height{};
    ColorTexture(std::string &&filename);
    ColorTexture(const std::string &filename);

    Color getColor(int x, int y) const;
    Color getColor(float x, float y) const;

};


#endif //RAYTRACER_COLORTEXTURE_H