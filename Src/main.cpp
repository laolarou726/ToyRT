#include "Tuple.h"
#include "easyppm.h"
#include "Assets/Objects/Plane.h"
#include "Assets/Objects/Sphere.h"
#include "Scene.h"
#include "Assets/Cameras/PTCamera.h"
#include "Assets/Materials/Reflection.h"
#include "Assets/Objects/XYLimitedPlane.h"
#include "Assets/Materials/Emission.h"
#include <cmath>

using namespace std;

int main() {

    // PART 1
    /*
    Ray testRay = Ray({0, 0, 0}, {0, 0, -1});
    auto* testPlane1 = new Plane({0, 0, 10}, {0, 0, -1});
    auto* testPlane2 = new Plane({0, 0, 10}, {0, 1, 0});

    cout << "TEST PLANE 1: " << testPlane1->intersect(testRay.origin, testRay.direction) << endl;
    cout << "TEST PLANE 2: " << testPlane2->intersect(testRay.origin, testRay.direction) << endl;

    // PART 2
    Ray testRay2 = Ray({0, 2.6, 0}, {0, 0, 1});
    auto* testSphere1 = new Sphere({0, 0, 10}, 2.5);

    cout << "TEST SPHERE 1: " << testSphere1->intersect(testRay.origin, testRay.direction) << endl;
    cout << "TEST SPHERE 2: " << testSphere1->intersect(testRay2.origin, testRay2.direction) << endl;
     */
    // Create image of desired dimensions.

    int myImageWidth = 800;
    int myImageHeight = 600;

    double focus = 1.7;
    double w = 3.6;
    double h = 2.4;
    Tuple origin = {500, 0, 200};
    Tuple direction = {-1, 0, 0.15};

    Scene scene;
    PTCamera camera = PTCamera(w, h, focus, origin, direction);

    // TEST 1
    //scene.addObject(testPlane1);

    // TEST 2
    //scene.addObject(testSphere1);

    // EXTRA PART 1
    // scene.addObject(new Plane({0, 0, 10}, {0, 0, -1}, Diffusion({1, 0, 0})));
    // scene.addObject(new Plane({0, 0, 10}, {0, 1, -1}, Diffusion({0, 1, 0})));

    // EXTRA PART 2
    //scene.addObject(new Sphere({0, 0, 10}, 2.5, Diffusion({0, 1, 0}, {0.3, 0.4, 0.2})));
    // scene.addObject(new Sphere({0, 0, 6}, 1, Diffusion({1, 0, 0}, {0.3, 0.4, 0.2})));

    //scene.addLight(new PointLight({0, 0, 5}, {1, 1, 1}));
    //scene.addLight(new PointLight({-2, 0, 5}, {1, 1, 1}));

    // Cornell Box
    scene.addObject(new Sphere({0, -180, 120}, 120, new Diffusion({0.9, 1, 1})));
    scene.addObject(new Sphere({0, 180, 120}, 120, new Reflection({1, 1, 1})));
    scene.addObject(new Plane({0, 0, 0},{0, 0, 1}, new Diffusion({0.7, 0.7, 0.7})));
    scene.addObject(new Plane({0, -400, 0}, {0, 1, 0}, new Diffusion({0, 1, 0})));
    scene.addObject(new Plane({0, 400, 0}, {0, -1, 0}, new Diffusion({1, 0, 0})));
    scene.addObject(new XYLimitedPlane({-65, 0, 700}, {0, 0, -1}, 300, new Emission({1, 0.9, 0.6}, Tuple(1, 0.9, 0.7) * 10)));
    scene.addObject(new Plane({0, 0, 700}, {0, 0, -1}, new Diffusion({0.7, 0.7, 0.7})));
    scene.addObject(new Plane({-250, 0, 0}, {1, 0, 0}, new Diffusion({0.7, 0.7, 0.7})));

    //scene.addLight(new PointLight({-65, 0, 600}, {0.5, 0.5, 0.5}));
    //scene.addLight(new PointLight({-65, -40, 650}, {1, 1, 1}));
    //scene.addLight(new PointLight({-265, 0, 350}, {0.2, 0, 0}));

    camera.render(myImageWidth, myImageHeight, scene);
    camera.saveTo("test_image.ppm");

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}
