#include "Shape.hpp"

#include <glad/glad.h>

namespace visualizer
{
	const Attribute Shape::PositionAttribute(3, GL_FLOAT);
	const Attribute Shape::ColorAttribute(3, GL_FLOAT);
	const Attribute Shape::TextureCoordinateAttribute(2, GL_FLOAT);
	const Attribute Shape::NormaleAttribute(3, GL_FLOAT);

	Shape::Shape(unsigned int vertex_array_object,
				 unsigned int vertex_buffer_object,
				 n_vertices number_vertices,
				 bool use_indices)
		: _vertex_array_object(vertex_array_object),
		  _vertex_buffer_object(vertex_buffer_object),
		  _number_vertices(number_vertices),
		  _use_indices(use_indices)
	{}

	void Shape::free_buffers()
	{
		glDeleteVertexArrays(1, &_vertex_array_object);
	}

	Shape Shape::create(const float* vertices,
						n_vertices number_vertices,
						const std::vector<Attribute>& attributes)
	{
		unsigned int vao = create_vao();
		unsigned int attributes_size = get_attributes_size(attributes);
		unsigned int vbo;
		vbo = buffer_vertices(vertices, number_vertices * attributes_size * sizeof(float));
		create_attribute_pointer(attributes);

		return Shape(vao, vbo, number_vertices, false);
	}

	void Shape::bind() const
	{
		glBindVertexArray(_vertex_array_object);
	}

	bool Shape::use_indices() const
	{
		return _use_indices;
	}

	n_vertices Shape::get_number_vertices() const
	{
		return _number_vertices;
	}

	void Shape::unbind()
	{
		glBindVertexArray(0);
	}

	unsigned int Shape::create_vao()
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		return vao;
	}

	unsigned int Shape::buffer_vertices(const float* vertices, size_t vertices_size)
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
		return vbo;
	}

	n_floats Shape::get_attributes_size(const std::vector<Attribute>& attributes)
	{
		unsigned int attributes_size = 0;
		for (Attribute a : attributes)
		{
			attributes_size += a.size;
		}
		return attributes_size;
	}

	void Shape::create_attribute_pointer(const std::vector<Attribute>& attributes)
	{
		size_t attributes_stride = get_attributes_size(attributes) * sizeof(float);

		size_t offset = 0;
		for (unsigned int i = 0; i < attributes.size(); i++)
		{
			glVertexAttribPointer(i,
								  attributes[i].size,
								  attributes[i].type,
								  GL_FALSE,
								  attributes_stride,
								  (void*)offset);
			offset += attributes[i].size * sizeof(float);
			glEnableVertexAttribArray(i);
		}
	}
}
