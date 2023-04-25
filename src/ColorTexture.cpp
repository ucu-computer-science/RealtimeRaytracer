#include "ColorTexture.h"

extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

}

ColorTexture::ColorTexture(std::string &&filename) {

    std::vector<uint8_t> image;
    bool success = load_image(image, filename);
    if (!success) {
        std::cerr << "Error loading texture " << filename << "\n";
//            return 1;
    }

    const size_t RGBA = 4;
    bitmap.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            size_t index = RGBA * (y * width + x);
            bitmap.emplace_back(Color{image[index + 0], image[index + 1], image[index + 2]});
        }

    }
}
ColorTexture::ColorTexture(const std::string &filename) {

    std::vector<uint8_t> image;
    bool success = load_image(image, filename);
    if (!success) {
        std::cerr << "Error loading texture " << filename << "\n";
//            return 1;
    }

    const size_t RGBA = 4;
    bitmap.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            size_t index = RGBA * (y * width + x);
            bitmap.emplace_back(Color{image[index + 0], image[index + 1], image[index + 2]});
        }

    }
}

bool ColorTexture::load_image(std::vector<uint8_t> &image, const std::string &filename) {
    int n;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n, 4);
    if (data != nullptr) {
        image = std::vector<uint8_t>(data, data + width * height * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

Color ColorTexture::getColor(float x, float y) const{
    int w = static_cast<float>(std::max(ceil(x*static_cast<float>(width))-1, 0.f));
    int h = static_cast<float>(std::max(ceil(y*static_cast<float>(height))-1, 0.f));
    return getColor(w, h);
}

Color ColorTexture::getColor(int x, int y) const{

    size_t index = (y * width + x);
    return bitmap.at(index);
}