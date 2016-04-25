/*
 * VertexBuffer.cpp
 *
 *  Created on: 10.08.2013
 *      Author: NullPointer
 */

#include "VertexBuffer.h"

namespace zeptoroids {

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &buffer);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &buffer);
}

void VertexBuffer::Init(GLenum target, const std::vector<GLfloat>& data) {
	Bind(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
	VertexBuffer::Unbind(GL_ARRAY_BUFFER);
}

} /* namespace zeptoroids */
