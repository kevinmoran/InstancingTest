#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "time.h"

#include "init_gl.h"
#include "maths_funcs.h"
#include "Shader.h"
#include "rand_utils.h"

GLFWwindow* window = NULL;
int gl_width = 460;
int gl_height = 360;
float gl_aspect_ratio = (float)gl_width/gl_height;

int main() {
	if (!init_gl(window, gl_width, gl_height)){ return 1; }

	//Geometry setup
	GLfloat vertex_points[] = {
		-0.05f,	0.05f,
		-0.05f, -0.05f,
		 0.05f, -0.05f,
		-0.05f,	0.05f,
		 0.05f, -0.05f,
		 0.05f,  0.05f
	};

	//Generate instance offsets
	#define NUM_INSTANCES 16
	#define NUM_COLOURS 8 //every two quads are same colour
	vec2 instance_offsets[NUM_INSTANCES];
	vec4 instance_colours[NUM_COLOURS];
	srand(time(0));
	for(int i=0; i<NUM_INSTANCES; i++){
		instance_offsets[i] = vec2(rand_betweenf(-1,1), rand_betweenf(-1,1));
	}

	for(int i=0; i<NUM_COLOURS; i++){
		instance_colours[i] = vec4(rand_betweenf(0,1), rand_betweenf(0,1), rand_betweenf(0,1), 1);
	}

	//Vertex points vbo
	GLuint points_vbo;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_points), vertex_points, GL_STATIC_DRAW);

	//Instance offsets vbo
	GLuint offset_vbo;
	glGenBuffers(1, &offset_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, offset_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(instance_offsets), instance_offsets, GL_STATIC_DRAW);

	//Instance colours vbo
	GLuint colour_vbo;
	glGenBuffers(1, &colour_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(instance_colours), instance_colours, GL_STATIC_DRAW);

	//Generate VAO
	GLuint particle_vao;
	glGenVertexArrays(1, &particle_vao);
	//Bind vertex points vbo
	glBindVertexArray(particle_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	//Bind instance offsets vbo
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, offset_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), NULL);
	glVertexAttribDivisor(1, 1); //2nd arg = 1 means updated attribute per instance, not per vertex
	//Bind instance colours vbo
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), NULL);
	glVertexAttribDivisor(2, 2);

	//Load shader
	Shader particle_shader("particles_instanced.vert", "pass.frag");
	glUseProgram(particle_shader.prog_id);

	double curr_time = glfwGetTime(), prev_time, dt;
	while (!glfwWindowShouldClose(window)) {
		//Get dt
		prev_time = curr_time;
		curr_time = glfwGetTime();
		dt = curr_time - prev_time;
		if (dt > 0.1) dt = 0.1;

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(particle_shader.prog_id);
		glBindVertexArray(particle_vao);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, NUM_INSTANCES);

		glfwSwapBuffers(window);

	}//end main loop

	return 0;
}
