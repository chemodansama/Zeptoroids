/*
 * VertexBuffer.h
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include <GLES/gl.h>
#include <vector>

namespace zeptoroids {

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void Init(GLenum target, const std::vector<GLfloat> &data);

	void Bind(GLenum target) const {
		glBindBuffer(target, buffer);
	}

	static void Unbind(GLenum target) {
		glBindBuffer(target, 0);
	}
private:
	GLuint buffer;

	VertexBuffer(const VertexBuffer &vb) = delete;
	VertexBuffer operator=(const VertexBuffer &vb) = delete;
};

} /* namespace zeptoroids */
#endif /* VERTEXBUFFER_H_ */
