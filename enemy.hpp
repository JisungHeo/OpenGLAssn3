#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
using namespace std;
class Enemy {
public:
	Enemy(float x, float y);
	float x;
	float y;
	static GLuint vertexArrayID;
	void draw();
	static int dummy_obj_size;
	static void initVAO();
	static void initMap();
	static vector<Enemy> vectorEnemy;
	static void drawAll();
};