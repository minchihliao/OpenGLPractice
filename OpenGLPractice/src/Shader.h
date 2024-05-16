#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, glm::vec2& value);
	void SetUniform3f(const std::string& name, glm::vec3& value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, glm::vec4& value);
	void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4F(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name) const;
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	// caching for uniforms

};

