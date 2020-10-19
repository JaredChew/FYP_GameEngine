#include "system.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <SOIL2/SOIL2.h>
<<<<<<< HEAD:Engine/src/Manipulators/openGL.cpp
#include <SOIL2/stb_image.h>
=======
#include <glm/gtc/type_ptr.hpp>

#include "../Utilities/logger.h"

static void System::error_callback(int error, const char* description) {

	Logger::getInstance()->customLog("GLFW ERROR", description);

}

bool System::initOpenGL() {

	glfwSetErrorCallback(System::error_callback);

	//Initialize GLFW library
	if (!glfwInit()) {

		Logger::getInstance()->errorLog("Failed to initialise GLFW");

		return false;

	}

	//Set window hints
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); //3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::getInstance()->errorLog("Failed to initialize OpenGL context");
		return false;
	}

	Logger::getInstance()->infoLog((char*)glGetString(GL_VERSION));
	Logger::getInstance()->infoLog(glfwGetVersionString());

	if (!GLAD_GL_VERSION_3_3) {

		Logger::getInstance()->errorLog("Your device must support OpenGL 3.2+");

		glfwTerminate();

		return false;

	}

	return true;

}
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487:Engine/src/Manipulators/system.cpp

bool System::initProgramObject_Shader(GLuint &programID, const GLuint &fragmentShader, const GLuint &vertexShader) {

	GLuint programObject = glCreateProgram();

	if (programObject == 0) { return false; }

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	glBindAttribLocation(programObject, 0, "vPosition");
	glBindAttribLocation(programObject, 1, "vColor");
	glBindAttribLocation(programObject, 2, "vTexCoord");

	// Link the program
	glLinkProgram(programObject);

	GLint linked;

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked) {

		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1) {

			char infoLog[1024];

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to link shader program %s", static_cast<std::string>(infoLog));

		}

		glDeleteProgram(programObject);

		return false;
	}

	// Store the program object
	programID = programObject;

	glDetachShader(programID, fragmentShader);
	glDetachShader(programID, vertexShader);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return true;

}

bool System::initTexture(GLuint &textureID, const GLsizei &size, const GLuint &resolutionWidth, const GLuint &resolutionHeight) {

	glGenTextures(size, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolutionWidth, resolutionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true ? textureID != 0 : false;

}

bool System::initTexture(const GLchar* dir, GLuint& textureID, GLint& width, GLint& height)
{
	int channels = 0;

	glGenTextures(1, &textureID);
<<<<<<< HEAD:Engine/src/Manipulators/openGL.cpp
	stbi_set_flip_vertically_on_load(true);
=======

>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487:Engine/src/Manipulators/system.cpp
	unsigned char* image = SOIL_load_image(dir, &width, &height, &channels, SOIL_LOAD_AUTO);

	glBindTexture(GL_TEXTURE_2D, textureID);

	if (image == 0) {

		Logger::getInstance()->errorLog("SOIL loading error: $s", SOIL_last_result());

		return false;

	}

	GLenum format = 0;

<<<<<<< HEAD:Engine/src/Manipulators/openGL.cpp
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); // GL_LINEAR); // magnifying = near, linear = gradient
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); //GL_NEAREST); // minifying = far, nearest = more pixel
		//GL_NEAREST_MIPMAP_NEAREST
=======
	switch (channels)
	{
	case SOIL_LOAD_L:
		format = GL_RED;
		break;
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487:Engine/src/Manipulators/system.cpp

	case SOIL_LOAD_RGB:
		format = GL_RGB;
		break;

<<<<<<< HEAD:Engine/src/Manipulators/openGL.cpp
		glGenerateMipmap(GL_TEXTURE_2D);

=======
	case SOIL_LOAD_RGBA:
		format = GL_RGBA;
		break;
>>>>>>> 4127e5edbe708cd7ead2500ddedf2d0860d10487:Engine/src/Manipulators/system.cpp
	}

	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	return true;

}

bool System::initDepthBufferTexture(GLuint &textureID, const GLuint &resolutionWidth, const GLuint &resolutionHeight) {

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolutionWidth, resolutionHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true ? textureID != 0 : false;

}

bool System::checkIsFramebufferReady() {

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {

		switch (status) {

			case GL_FRAMEBUFFER_UNDEFINED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNDEFINED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_UNSUPPORTED");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				Logger::getInstance()->warningLog("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
				break;

		}

		return false;

	}

	return true;

}

void System::loadMesh(GLuint& vbo, GLuint& ebo, GLuint& vao, const GLfloat* vertices, const GLuint& verticesSize, const GLuint* indices, const GLuint& indicesSize) {

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(GLfloat), (void*)vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), (void*)indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //TexCoord

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

bool System::loadShaderRaw(GLuint& shaderID, const GLenum& type, const char *shaderSrc) {

	GLint compiled;

	// Create the shader object
	shaderID = glCreateShader(type);

	if (shaderID == 0) { return false; }

	// Load the shader source
	glShaderSource(shaderID, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shaderID);

	// Check the compile status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		GLint infoLen = 0;

		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen == 0) {

			char infoLog[4096];

			glGetShaderInfoLog(shaderID, infoLen, NULL, infoLog);

			Logger::getInstance()->warningLog("Failed to compile shader %s", static_cast<std::string>(infoLog));

		}

		glDeleteShader(shaderID);

		return false;

	}

	return true;

}

bool System::loadShaderFromFile(GLuint& shaderID, const GLenum& type, const std::string& path) {

	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	if (!sourceFile) {

		Logger::getInstance()->warningLog("Unable to open file %s", path);

		return false;

	}

	shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());

	const GLchar* shaderSource = shaderString.c_str();

	return System::loadShaderRaw(shaderID, type, shaderSource);

}

bool System::loadCubemapTexture(GLuint& textureID, const std::vector<std::string>& facesPath) {

	unsigned char* image;

	int resolutionWidth, resolutionHeight;

	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_TEXTURE_CUBE_MAP);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < facesPath.size(); i++) {

		image = SOIL_load_image(facesPath[i].c_str(), &resolutionWidth, &resolutionHeight, NULL, SOIL_LOAD_AUTO);

		//if(image) { printf("SOIL loading error: '%s'\n", SOIL_last_result()); }

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, resolutionWidth, resolutionWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glDisable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true ? textureID != 0 : false;

}

void System::editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	uint8_t data[3] = { r, g, b };

	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void System::applyBillboard(glm::mat4& modelViewMatrix) {

	// 1st colunm
	glm::value_ptr(modelViewMatrix)[0] = 1.0;
	glm::value_ptr(modelViewMatrix)[1] = 0.0;
	glm::value_ptr(modelViewMatrix)[2] = 0.0;

	// 2nd colunm
	glm::value_ptr(modelViewMatrix)[4] = 0.0;
	glm::value_ptr(modelViewMatrix)[5] = 1.0;
	glm::value_ptr(modelViewMatrix)[6] = 0.0;

	// 3rd colunm
	glm::value_ptr(modelViewMatrix)[8] = 0.0;
	glm::value_ptr(modelViewMatrix)[9] = 0.0;
	glm::value_ptr(modelViewMatrix)[10] = 1.0;

}