#pragma once

#include <string>
#include <unordered_map>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// cache for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();



	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
};