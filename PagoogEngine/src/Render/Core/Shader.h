#pragma once

namespace PEngine
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Init(const char* vertexShader, const char* fragmentShader);
		void Use();

		void Set1f(const char* uniformName, float x);
		void Set2f(const char* uniformName, float x, float y);
		void Set3f(const char* uniformName, float x, float y, float z);
		void Set4f(const char* uniformName, float x, float y, float z, float w);

		void Set1i(const char* uniformName, int x);
		void Set2i(const char* uniformName, int x, int y);
		void Set3i(const char* uniformName, int x, int y, int z);
		void Set4i(const char* uniformName, int x, int y, int z, int w);

		void Set1ui(const char* uniformName, unsigned int x);
		void Set2ui(const char* uniformName, unsigned int x, unsigned int y);
		void Set3ui(const char* uniformName, unsigned int x, unsigned int y, unsigned int z);
		void Set4ui(const char* uniformName, unsigned int x, unsigned int y, unsigned int z, unsigned int w);

		void Set1fv(const char* uniformName, int count, const float* arr);
		void Set2fv(const char* uniformName, int count, const float* arr);
		void Set3fv(const char* uniformName, int count, const float* arr);
		void Set4fv(const char* uniformName, int count, const float* arr);

		void Set1iv(const char* uniformName, int count, const int* arr);
		void Set2iv(const char* uniformName, int count, const int* arr);
		void Set3iv(const char* uniformName, int count, const int* arr);
		void Set4iv(const char* uniformName, int count, const int* arr);

		void Set1uiv(const char* uniformName, int count, const unsigned int* arr);
		void Set2uiv(const char* uniformName, int count, const unsigned int* arr);
		void Set3uiv(const char* uniformName, int count, const unsigned int* arr);
		void Set4uiv(const char* uniformName, int count, const unsigned int* arr);

		void SetMatrix2fv(const char* uniformName, int count, bool transpose, const float* arr);
		void SetMatrix3fv(const char* uniformName, int count, bool transpose, const float* arr);
		void SetMatrix4fv(const char* uniformName, int count, bool transpose, const float* arr);

		void SetMatrix2x3fv(const char* uniformName, int count, bool transpose, const float* arr);
		void SetMatrix3x2fv(const char* uniformName, int count, bool transpose, const float* arr);

		void SetMatrix2x4fv(const char* uniformName, int count, bool transpose, const float* arr);
		void SetMatrix4x2fv(const char* uniformName, int count, bool transpose, const float* arr);

		void SetMatrix3x4fv(const char* uniformName, int count, bool transpose, const float* arr);
		void SetMatrix4x3fv(const char* uniformName, int count, bool transpose, const float* arr);

	private:
		unsigned int vertexShader;
		unsigned int fragmentShader;
		unsigned int shader;

		int GetUniformLocation(const char* uniformName);
	};
}

