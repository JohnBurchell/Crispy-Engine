//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Graphics\Window\window.h"
#include "Graphics\Core\vertex_buffer_object.h"
#include "Graphics\Core\vertex_buffer_array.h"
#include "Graphics\Core\index_buffer_array.h"
#include "Graphics\Shaders\shader.h"
#include "Graphics\Sprites\sprite_renderer.h"
#include "Graphics\Resources\resource_manager.h"
#include "Graphics\Particles\particle_generator.h"
#include "Graphics\Objects\object.h"

#include <iostream>

glm::vec3 light_pos = { 200.0f, 200.0f, 0.0f };


//Callback for handling key presses.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//When the user presses the escape key, set WindowShouldClose to true, thus closing the application.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	Window window{};

	glfwSetKeyCallback(window.window, key_callback);

	//Not sure why having the projection matrix is useful at the moment - Need to read up on this
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	Sprite_Renderer* renderer = nullptr;

	Resource_Manager::load_shader("../Graphics/Shaders/Sprite_Shaders/sprite.vert", "../Graphics/Shaders/Sprite_Shaders/sprite.frag", nullptr, "Sprite_Shader");
	//Configure Shaders
	Resource_Manager::get_shader("Sprite_Shader").use().set_integer("image", 0);
	Resource_Manager::get_shader("Sprite_Shader").set_vector3f("sprite_colour", glm::vec3{ 0.0f, 0.0f, 1.0f });
	Resource_Manager::get_shader("Sprite_Shader").set_matrix4("projection", projection);

	renderer = new Sprite_Renderer(Resource_Manager::get_shader("Sprite_Shader"));

	Resource_Manager::load_texture("../Graphics/Textures/tetrominoe.png", GL_TRUE, "face");

	GLfloat delta_time = 0.0f;
	GLfloat last_frame = 0.0f;

	double mouse_x = 0.0;
	double mouse_y = 0.0;

	GLuint FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Framebuffer examples

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Attach the texture to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);


	//End framebuffer examples

	//Simple loop
	while (!window.window_is_open())
	{
		GLfloat current_frame = static_cast<GLfloat>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		glfwPollEvents();

		glfwGetCursorPos(window.window, &mouse_x, &mouse_y);

		window.clear();

		Resource_Manager::get_shader("Sprite_Shader").set_vector3f("light_position", glm::vec3{ mouse_x, mouse_y, 1.0f });

		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(200, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.434f, 0.434f, 0.434f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(232, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(264, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(1.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(296, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(296, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(328, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(360, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(392, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(424, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(456, 200), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));

		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(200, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(232, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(264, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(1.0f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(296, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.1f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(296, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.2f, 0.5f, 0.5f));
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(328, 232), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(0.3f, 0.5f, 0.5f));

		glm::vec3 blue = glm::vec3(0.0f, 0.0f, 0.474f);
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(360, 232), glm::vec2(32.0f, 32.0f), 0.0f, blue);
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(392, 232), glm::vec2(32.0f, 32.0f), 0.0f, blue);
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(424, 232), glm::vec2(32.0f, 32.0f), 0.0f, blue);
		renderer->draw_sprite(Resource_Manager::get_texture("face"), glm::vec2(456, 232), glm::vec2(32.0f, 32.0f), 0.0f, blue);

		window.flip();
	}

	glDeleteFramebuffers(1, &FBO);

	//Cleanup
	return 0;
}