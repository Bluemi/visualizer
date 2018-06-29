#ifndef __SHAPE_CLASS__
#define __SHAPE_CLASS__


#include <vector>
#include <glad/glad.h>

#include "misc/Types.hpp"

namespace visualizer
{
	/**
	 * An Attribute defining the size in number of floats and the type of vertices.
	 */
	struct Attribute
	{
		Attribute(n_floats s, unsigned int t)
			: size(s), type(t)
		{}
		/**
		 * The number of floats this attribute takes.
		 */
		n_floats size;

		/**
		 * The type of this Attribute
		 */
		unsigned int type;
	};

	/**
	 * A Shape defines the following attributes:
	 *   - Vertices
	 *   - Indices if any
	 *   - Attributepointers
	 */
	class Shape
	{
		public:
			/**
			 * Deletes all used buffers of this Shape.
			 * After calling this function this Shape cant be used for rendering.
			 */
			void free_buffers();

			/**
			 * Creates a new Shape.
			 * This Shape is bound.
			 *
			 * @param vertices The vertices of the Shape
			 * @param vertices_size The number of the vertices.
			 * 						If you have 2 triangles this would be 2*3=6
			 * @param attributes A list of attributes, which define the order of the vertices.
			 */
			static Shape create(const float* vertices,
								n_vertices number_vertices,
								const std::vector<Attribute>& attributes);

			/**
			 * Binds this Shape to use for rendering.
			 * After this call the Vertices, Indices and AttributePointer of this
			 * Shape are used by any call of glDrawArrays or glDrawElements.
			 */
			void bind() const;

			// Getter
			bool use_indices() const;
			n_vertices get_number_vertices() const;

			/**
			 * Unbinds all Shapes.
			 */
			static void unbind();

			/*
			 * Attributes, which can be useful.
			 */
			static const Attribute PositionAttribute;
			static const Attribute ColorAttribute;
			static const Attribute TextureCoordinateAttribute;
			static const Attribute NormaleAttribute;
		private:
			/**
			 * Creates a new Shape
			 *
			 * @param vertex_array_object The id of the vao of this Shape
			 * @param vertex_buffer_object The id of the vbo of this Shape
			 * @param number_vertices The number of vertices used by this Shape
			 * @param use_indices If true use glDrawElements otherwise glDrawArrays.
			 */
			Shape(unsigned int vertex_array_object,
				  unsigned int vertex_buffer_object,
				  n_vertices number_vertices,
				  bool use_indices);

			/**
			 * Creates the vertex array object of this Shape and binds it.
			 *
			 * @return The id of the created vao.
			 */
			static unsigned int create_vao();

			/**
			 * Buffers the given vertices and returns the id of the created vbo.
			 *
			 * @param vertices The vertices as float array
			 * @param vertices_size The size number of all vertices added together in bytes
			 * @return The id of the new vbo
			 */
			static unsigned int buffer_vertices(const float* vertices, size_t vertices_size);

			/**
			 * @return The sum of the number of floats used by all attributes.
			 */
			static n_floats get_attributes_size(const std::vector<Attribute>& attributes);
			static void create_attribute_pointer(const std::vector<Attribute>& attributes);

			unsigned int _vertex_array_object;
			unsigned int _vertex_buffer_object;
			n_vertices _number_vertices;
			bool _use_indices;
	};
}

#endif
