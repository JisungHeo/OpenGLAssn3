#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
class Player {
public:
	Player(float x, float y);
	float x;
	float y;
	static GLuint vertexArrayID;
	void draw();
	static void initVAO();
	static int dummy_obj_size;
};