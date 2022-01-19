#ifndef DEF_ADDBUFFER
#define DEF_ADDBUFFER
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace buffer
{
	class AddBuffer
	{
	public:
		void add_buffer(std::vector<GLuint*> buffer, float sommets[]);
		void draw(std::vector<GLuint*> buffer);
	private:

	};
}


#endif // !1

