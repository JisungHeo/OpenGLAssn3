#include <iostream> 
#include <vector>
#include <glm/mat4x4.hpp>
#include <GL/glew.h> 
#include <GL/freeglut.h> 
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"
#include "shader.hpp"

GLuint programID;
GLuint MVPID;
GLuint ColorID;
GLuint VertexArrayID;
glm::mat4 MVP;
GLuint vertexbuffer;
unsigned int dummy_obj_size;
using namespace std; 
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(programID);
	glBindVertexArray(VertexArrayID);
	MVP = glm::perspective(glm::radians(45.0f), 4.0f / 3, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(400.0f, 0.0f, -40.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::mat4(1.0f) * glm::scale(glm::mat4(1.0f), glm::vec3(30.0f)); 

	/*MVP = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f) *
		glm::lookAt(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));*/
	
	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	glUniform4f(ColorID, 0.0f, 1.0f, 0.0f, 1.0f);
	for (int i = 0; i < dummy_obj_size/4; i++) {
		glDrawArrays(GL_LINE_LOOP, i * 4, 4);
	}
	glBindVertexArray(0);
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void init() {
	//shader
	programID = LoadShaders("myVS.glsl", "myFS.glsl");
	MVPID = glGetUniformLocation(programID, "MVP");
	ColorID = glGetUniformLocation(programID, "fragmentColor");
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("obj_files/gun.obj", vertices, uvs, normals);
	glUseProgram(programID);

	//vertexBuffer
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer 
	);
	dummy_obj_size = vertices.size();
	glutSwapBuffers();
}
void main(int argc, char **argv) {  	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(700, 700); 
	glutCreateWindow("Hello OpenGL"); 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
	glewInit();
	init();
	glutMainLoop(); 
}