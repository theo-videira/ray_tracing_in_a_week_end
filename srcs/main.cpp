#include "rtweekend.hpp"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"



color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);

    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(void) {

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;

    // Compute image height and ensure it's at least 1
    int image_height = int(IMAGE_WIDTH / ASPECT_RATIO);
    const int IMAGE_HEIGHT = (image_height < 1) ? 1 : image_height;

    // World
    hittable_list world;
    
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    const double FOCAL_LENGTH = 1.0;
    const double VIEWPORT_HEIGHT = 2.0;
    const double VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH)/IMAGE_HEIGHT);
    const point3 CAMERA_CENTER = point3(0.0, 0.0, 0.0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const vec3 VIEWPORT_U = vec3(VIEWPORT_WIDTH, 0.0, 0.0);
    const vec3 VIEWPORT_V = vec3(0.0, -VIEWPORT_HEIGHT, 0.0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const vec3 PIXEL_DELTA_U = VIEWPORT_U / IMAGE_WIDTH;
    const vec3 PIXEL_DELTA_V = VIEWPORT_V / IMAGE_HEIGHT;

    // Calculate the location of the upper left pixel.
    const vec3 VIEWPORT_UPPER_LEFT = 
        CAMERA_CENTER - vec3(0, 0, FOCAL_LENGTH) - VIEWPORT_U/2 - VIEWPORT_V/2;
    const point3 FIRST_PIXEL = VIEWPORT_UPPER_LEFT + 0.5 * (PIXEL_DELTA_U + PIXEL_DELTA_V);
    
    


    // Render image
    // Image ppm parameters

    std::cout << "P3" << std::endl;
    std::cout << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl;
    std::cout << "255" << std::endl;

    // Image pixels
    for (int j = 0; j < IMAGE_HEIGHT; j++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT-j) << " " << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; i++) {
            auto pixel_center = FIRST_PIXEL + (i * PIXEL_DELTA_U) + (j * PIXEL_DELTA_V);
            auto ray_direction = pixel_center - CAMERA_CENTER;
            ray r(CAMERA_CENTER, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
            std::cout << std::endl;
        }
    }
    std::clog << "\rScanlines remaining: 0" << std::endl;
    std::clog << "Done." << std::endl;
    return 0;
}