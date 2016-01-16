#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

static void errorCallback(int error, const char* description);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void windowResizeCallback(GLFWwindow* window, int width, int height);
static void update(float dt);
static void draw(void);

struct GameData {
	double ratio;
	float t;
	struct {
		float x;
		float y;
	} position;
} game;

int main(void) {
	GLFWwindow* window;

	/* Setup an error callback */
	glfwSetErrorCallback(errorCallback);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "azru", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Shto? */
	glfwSwapInterval(1);

	/* Setup a callback for keyboard events */
	glfwSetKeyCallback(window, keyCallback);

	/* Setup a callback for window resize */
	glfwSetWindowSizeCallback(window, windowResizeCallback);

	fputs("Start rendering", stdout);

	float t0 = glfwGetTime();

	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		windowResizeCallback(window, width, height);
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
	
		float t = glfwGetTime();
		float dt = t - t0;
		t0 = t;
		game.t = t;

		update(dt);
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		game.position.x += 0.1f;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		game.position.x -= 0.1f;
}

void windowResizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
	game.ratio = width / (double)height;
}

void update(float dt) {

}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-game.ratio, game.ratio, -1.f, 1.f, 1.f, -1.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(game.position.x, game.position.y, 0.f);
	glRotatef(game.t * 50.f, 0.f, 0.f, 1.f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	
	glBegin(GL_POINT);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();
}