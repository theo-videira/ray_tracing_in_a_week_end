#include <iostream>

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGTH = 256;
const int COLOR_MAX = 255;

int main(void) {

    // Image parameters

    std::cout << "P3" << std::endl;
    std::cout << IMAGE_WIDTH << " " << IMAGE_HEIGTH << std::endl;
    std::cout << COLOR_MAX << std::endl;

    // Image pixels
    for (size_t j = 0; j < IMAGE_HEIGTH; j++) {
        for (size_t i = 0; i < IMAGE_WIDTH; i++) {
            auto r = double(i) / (IMAGE_WIDTH - 1);
            auto g = double(j) / (IMAGE_HEIGTH - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
    return 0;
}