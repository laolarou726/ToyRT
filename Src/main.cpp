#include "Models/Vector3.h"
#include "Utils/easyppm.h"
#include "Assets/Objects/Plane.h"
#include "Assets/Objects/Sphere.h"
#include "Assets/Scene.h"
#include "Assets/Cameras/PTCamera.h"
#include "Assets/Materials/Reflection.h"
#include "Assets/Objects/XYLimitedPlane.h"
#include "Assets/Materials/Emission.h"
#include "Assets/Materials/Dielectric.h"
#include "fmt/format.h"
#include "fmt/chrono.h"
#include "Assets/Cameras/SingleThreadPTCamera.h"

using namespace std;

int main() {

    // Create image of desired dimensions.

    int myImageWidth = 800;
    int myImageHeight = 600;

    double focus = 1.7;
    double w = 3.6;
    double h = 2.4;
    Vector3 origin = {500, 0, 200};
    Vector3 direction = {-1, 0, 0.15};

    Scene scene;
    PTCamera camera = PTCamera(w, h, focus, origin, direction);

    // Cornell Box

    scene.addObject(new Sphere({0, -180, 120}, 120, new Dielectric(2.417)));
    scene.addObject(new Sphere({0, 180, 120}, 120, new Reflection({1, 1, 1}, 0)));

    /*
    scene.addObject(new Sphere({0, -220, 120}, 70, new Reflection({1, 1, 1}, 0)));
    scene.addObject(new Sphere({0, 0, 120}, 70, new Reflection({1, 1, 1}, 0.5)));
    scene.addObject(new Sphere({0, 0, 300}, 70, new Dielectric(1.5)));
    scene.addObject(new Sphere({0, 220, 120}, 70, new Reflection({1, 1, 1}, 1)));
    */

    scene.addObject(new Plane({0, 0, 0},{0, 0, 1}, new Diffusion({0.7, 0.7, 0.7})));
    scene.addObject(new Plane({0, -400, 0}, {0, 1, 0}, new Diffusion({0, 1, 0})));
    scene.addObject(new Plane({0, 400, 0}, {0, -1, 0}, new Diffusion({1, 0, 0})));
    scene.addObject(new XYLimitedPlane({-65, 0, 700}, {0, 0, -1}, 300, new Emission({1, 0.9, 0.6}, Vector3(1, 0.9, 0.7) * 10)));
    scene.addObject(new Plane({0, 0, 700}, {0, 0, -1}, new Diffusion({0.7, 0.7, 0.7})));
    scene.addObject(new Plane({-250, 0, 0}, {1, 0, 0}, new Diffusion({0.7, 0.7, 0.7})));
    scene.addObject(new Plane({500, 0, 0}, {-1, 0, 0}, new Diffusion({0.7, 0.7, 0.7})));

    camera.render(myImageWidth, myImageHeight, scene);


    const auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string fileName = fmt::format("{:%Y-%m-%d %H-%M-%S}.ppm", fmt::localtime(t));
    camera.saveTo(fileName);

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}
