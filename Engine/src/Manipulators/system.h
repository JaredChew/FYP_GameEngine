#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>
#include <string>
#include <map>

#include <glm/mat4x4.hpp>

class Texture;
struct Vertex;
class Mesh;
class Material;

namespace System {

	static void error_callback(int error, const char* description);

	bool initOpenGL();

	bool initProgramObject_Shader(GLuint &programID, const GLuint &fragmentShader, const GLuint &vertexShade);

	bool initTexture(GLuint &textureID, const GLsizei &size, const GLuint &resolutionWidth, const GLuint &resolutionHeight, GLint& internalFormat, GLenum& format);
	bool initTexture(const GLchar* dir, GLuint& textureID, GLint& width, GLint& height, GLint& internalFormat, GLenum& format);
	bool saveTextureToImage(const GLchar* filename, const GLuint& textureID, const GLsizei& width, const GLsizei& height);

	void loadImageToGLFWimage(const GLchar* dir, GLFWimage& image);

	bool initDepthBufferTexture(GLuint &textureID, const GLuint& resolutionWidth, const GLuint& resolutionHeight, GLint& internalFormat, GLenum& format);
	bool initDepthBufferTexture(Texture& texture, const GLuint &resolutionWidth, const GLuint& resolutionHeight);

	bool checkIsFramebufferReady();

	void loadMesh(GLuint& vbo, GLuint& ebo, GLuint& vao, const Vertex* vertices, const GLuint& verticesSize, const GLuint* indices, const GLuint& indicesSize);
	
	void loadModel(const GLchar* dir, std::vector<Mesh*>& meshes, std::vector<Material*>& materials);

	bool loadShaderRaw(GLuint& shaderID, const GLenum& type, const char *shaderSrc);
	bool loadShaderFromFile(GLuint& shaderID, const GLenum& type, const std::string& path);

	bool loadCubemapTexture(GLuint& textureID, const std::vector<std::string>& facesPath);

	void editTexel(const GLuint &textureID, const int &xOffset, const int &yOffset, const uint8_t &r, const uint8_t &g, const uint8_t &b);

	void applyBillboard(glm::mat4& modelViewMatrix);


	void loadModelToVertexArrayObjectData(const GLchar* modelDir, const GLchar* saveFileDir);

}