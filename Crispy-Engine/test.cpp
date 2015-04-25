//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include <iostream>

namespace tut_one
{

	GLuint shaderProgram;
	GLuint shaderProgram_yellow;

	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint frag_shader_yellow;

	GLuint VAOs[2];
	GLuint VBOs[2];
	GLuint EBO;


	// Shaders
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 colour; \n"
		"out vec3 our_colour;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0);\n"
		"our_colour = colour;\n"
		"}\0";

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec3 our_colour;\n"
		"out vec4 colour;\n"
		"void main()\n"
		"{\n"
		"colour = vec4(our_colour, 1.0f);\n"
		"}\n\0";

	const GLchar* yellow_shader = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";

	void tut_two_shaders()
	{

		//Create a shader object in the same way a VBO is created.
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Attach the code and compile the shader.
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		//Check for errors during compilation.
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Compile Fragment Shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		//Check for errors during compilation.
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Attach the shaders to the program.
		shaderProgram = glCreateProgram();
		shaderProgram_yellow = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		//Check that linking worked correctly
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n" << infoLog << std::endl;
		}
		//Delete the shaders as they are no longer needed anymore. Frees up memory perhaps?
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		/*
		Start of binding process
		*/

		//Array of vertex positions
		GLfloat vertices[] =
		{
			//Positions - x,y,z  - Colours r,g,b
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //Top
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //Bottom Right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  //Bottom Left
		};

		glGenBuffers(2, VBOs);
		glGenVertexArrays(2, VAOs);
		glBindVertexArray(VAOs[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Colour attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);

	}

	void exercise_one()
	{

		//Create a shader object in the same way a VBO is created.
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Attach the code and compile the shader.
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		//Check for errors during compilation.
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Vertex Shader - Position of Pixels
		//Fragment Shader - Colour and effects

		//Compile Fragment Shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		frag_shader_yellow = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		glShaderSource(frag_shader_yellow, 1, &yellow_shader, nullptr);
		glCompileShader(frag_shader_yellow);

		//Check for errors during compilation.
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		glGetShaderiv(frag_shader_yellow, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Attach the shaders to the program.
		shaderProgram = glCreateProgram();
		shaderProgram_yellow = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glAttachShader(shaderProgram_yellow, vertexShader);
		glAttachShader(shaderProgram_yellow, frag_shader_yellow);
		glLinkProgram(shaderProgram_yellow);

		//Check that linking worked correctly
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		glGetProgramiv(shaderProgram_yellow, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n" << infoLog << std::endl;
		}
		//Delete the shaders as they are no longer needed anymore. Frees up memory perhaps?
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(frag_shader_yellow);

		/*
		Start of binding process
		*/

		//Array of vertex positions
		GLfloat vertices[] =
		{
			0.5f, 0.0f, 0.0f, //Top
			1.0f, -1.0f, 0.0f, //Bottom Right
			0.0f, -1.0f, 0.0f, //Bottom Left
		};


		GLfloat vertices_two[] =
		{
			-0.5f, 0.0f, 0.0f, //Top
			-1.0f, -1.0f, 0.0f, //Bottom Right
			0.0f, -1.0f, 0.0f //Bottom Left
		};

		glGenBuffers(2, VBOs);
		glGenVertexArrays(2, VAOs);
		glBindVertexArray(VAOs[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);


		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_two), vertices_two, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void tut_one()
	{

		//Create a shader object in the same way a VBO is created.
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Attach the code and compile the shader.
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		//Check for errors during compilation.
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Vertex Shader - Position of Pixels
		//Fragment Shader - Colour and effects

		//Compile Fragment Shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		//Check for errors during compilation.
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Attach the shaders to the program.
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		//Check that linking worked correctly
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINKING_ERROR\n" << infoLog << std::endl;
		}
		//Delete the shaders as they are no longer needed anymore. Frees up memory perhaps?
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		/*
			Start of binding process
			*/

		//Array of vertex positions
		GLfloat vertices[] =
		{
			0.5f, 0.5f, 0.0f, //Top Right
			0.5f, -0.5f, 0.0f, //Bottom Right
			-0.5f, -0.5f, 0.0f, //Bottom Left
			-0.5f, 0.5f, 0.0f, //Top Left
		};

		GLuint indecies[] =
		{
			0, 1, 3, //First Triangle
			1, 2, 3 //Second Triangle
		};

		//Instead, use an Element Buffer Object - EBO

		//VBO - Vertex Buffer Object
		//Stores a large amount of vertexes that we can send to the GPU in a single go.
		//Has a unique ID and takes a reference to a VBO.
		glGenBuffers(1, VBOs);
		glGenBuffers(1, &EBO);
		//Create a VAO - Vertex Array Object
		glGenVertexArrays(1, VAOs);
		//Bind the VAO
		glBindVertexArray(VAOs[0]);

		//Copy vertex array in a buffer (VBO) for OpenGL to use.
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		//This copies the VBO data into the memory on the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

		//Set vertex attribute pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Unbind the VAO - This is common to avoid misconfiguration elsewhere.
		glBindVertexArray(0);
	}

	//Callback for handling key presses.
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		//When the user presses the escape key, set WindowShouldClose to true, thus closing the application.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	int mains()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "Learning some OpenGL", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);

		//Check to make sure the window is not null. If it is, terminate.
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}

		//Initialise GLEW
		//glewExperimental allows us to use modern techniques. Not setting it to true might lead to complications
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialise GLEW" << std::endl;
			return -1;
		}

		//Tell OpenGL the size of the window, or in this case the viewport, that we wish to render to
		glViewport(0, 0, 800, 600);

		//Init shaders and setup the VBO/VBA data
		//tut_one();

		//exercise one
		//exercise_one();

		//Tutorial Two
		tut_two_shaders();

		//Simple loop
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			//Set clear colour to ensure that we're actually rendering something
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Set the uniform shader variable here.
			GLfloat time_value = glfwGetTime();
			GLfloat green_value = (sin(time_value) / 2) + 0.5;
			//This line should give the index of the uniform in the VAO
			GLint vertex_colour_location = glGetUniformLocation(shaderProgram, "our_colour");

			//Use the shader and update the green value.
			glUseProgram(shaderProgram);
			glUniform4f(vertex_colour_location, 0.0f, green_value, 0.0f, 1.0f);

			//Drawning
			glBindVertexArray(VAOs[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//Polygon mode aka wireframe mode
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(0);

			glUseProgram(shaderProgram_yellow);
			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		//Cleanup
		glfwTerminate();
		return 0;
	}

}//end namespace

