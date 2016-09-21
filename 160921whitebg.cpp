#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstring>
#include <stdlib.h>		  // srand, rand 
#include <thread>         // std::this_thread::sleep_for 
#include <chrono>         // std::chrono::seconds 
#include "math.h"
#include <GLFW/glut.h>


const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawnline(const int& in0, const int& jn1, const int& jn2, const float& red, const float& green, const float& blue)
{
	for (int j = jn1; j <= jn2; j++)
	{
		drawPixel(in0, j, red, green, blue);
	}
}

void drawfRect(const int& i0, const int& i1, const int& j1, const int& j2, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		drawnline(i, j1, j2, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
		// std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work 
		std::fill_n(pixels, width*height * 3, 1.0f);	// white background 

		// for (int i = 0; i<width*height; i++)
		// { 
			// pixels[i * 3 + 0] = 1.0f; // red  
			// pixels[i * 3 + 1] = 1.0f; // green 
			// pixels[i * 3 + 2] = 1.0f; // blue 
		// } 
		
		const int i = rand() % width, j = rand() % height;
		drawPixel(i, j, 0.0f, 0.0f, 0.0f);
		
		// drawing a line
		// TODO: anti-aliasing
		
		const int i0 = 100, i1 = 200;
		const int j0 = 50, j1 = 80;
		drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);
		
		//TODO: try moving object
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//////

		std::fill_n(pixels, width*height * 3, 1.0f);	// white background

		// thicker line
		drawLine(50, 300, 150, 400, 0.0f, 1.0f, 0.0f);
		drawLine(51, 300, 151, 400, 0.0f, 1.0f, 0.0f);
		drawLine(52, 300, 152, 400, 0.0f, 1.0f, 0.0f);
		drawLine(53, 300, 153, 400, 0.0f, 1.0f, 0.0f);
		drawLine(54, 300, 154, 400, 0.0f, 1.0f, 0.0f);

		// triangle
		drawLine(200, 300, 330, 300, 1.0f, 0.0f, 0.0f);
		drawLine(270, 400, 330, 300, 1.0f, 0.0f, 0.0f);
		drawLine(271, 400, 331, 300, 1.0f, 0.0f, 0.0f);
		drawLine(200, 300, 270, 400, 1.0f, 0.0f, 0.0f);
		drawLine(201, 300, 271, 400, 1.0f, 0.0f, 0.0f);

		// pentagon
		drawLine(400, 300, 475, 300, 1.0f, 0.0f, 0.0f);
		drawLine(380, 350, 400, 300, 1.0f, 0.0f, 0.0f);
		drawLine(380, 350, 440, 400, 1.0f, 0.0f, 0.0f);
		drawLine(440, 400, 495, 350, 1.0f, 0.0f, 0.0f);
		drawLine(475, 300, 495, 350, 1.0f, 0.0f, 0.0f);

		// hollow rectangular
		drawnline(100, 150, 250, 0.0f, 0.0f, 1.0f);
		drawnline(200, 150, 250, 0.0f, 0.0f, 1.0f);
		drawLine(100, 150, 200, 150, 0.0f, 0.0f, 1.0f);
		drawLine(100, 250, 200, 250, 0.0f, 0.0f, 1.0f);

		// filled rectangular
		drawfRect(300, 400, 150, 250, 0.0f, 0.0f, 1.0f);

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete[] pixels;

	glfwTerminate();
	return 0;
}