#ifndef __SHAPE_CLASS__
#define __SHAPE_CLASS__

/**
 * A Shape defines the following attributes:
 *   - Vertices
 *   - Indices if any
 *   - Attributepointers
 *   - A shape type
 */

#include <vector>

#include <glad/glad.h>

namespace visualizer {
	enum class ShapeType
	{
		CUBE,
		SPHERE
	};

	/*
	 * An Attribute defines size and the type of vertices.
	 */
	struct Attribute
	{
		Attribute(unsigned int s, unsigned int t)
			: size(s), type(t)
		{}
		unsigned int size;
		unsigned int type;
	};

	class Shape
	{
		public:
			/**
			 * Creates a new Shape
			 */
			Shape(ShapeType shape_type, unsigned int vertex_array_object, unsigned int vertex_buffer_object, unsigned int number_vertices, bool use_indices);

			void free_buffers();

			/**
			 * Creates a new Shape.
			 *
			 * @param shape_type The type of the Shape
			 * @param vertices The vertices of the Shape
			 * @param vertices_size The number of the vertices. If you have 2 triangles this would be 2*3=6
			 * @param attributes A list of attributes, which define the order of the vertices.
			 */
			static Shape create(ShapeType shape_type, const float* vertices, unsigned int number_vertices, const std::vector<Attribute>& attributes);

			/**
			 * Binds this Shape to use for rendering.
			 */
			void bind() const;

			// Getter
			ShapeType get_shape_type() const;
			bool is_use_indices() const;
			unsigned int get_number_vertices() const;


			/**
			 * Unbinds all Shapes
			 */
			static void unbind();

			static const Attribute PositionAttribute;
			static const Attribute ColorAttribute;
			static const Attribute TextureCoordinateAttribute;
		private:
			/**
			 * Creates the vertex array object of this Shape and binds it.
			 */
			static unsigned int create_vao();

			/**
			 * Buffers the given vertices and returns the id of the created vbo.
			 */
			static unsigned int buffer_vertices(const float* vertices, unsigned int vertices_size);
			static unsigned int get_attributes_size(const std::vector<Attribute>& attributes);
			static void create_attribute_pointer(const std::vector<Attribute>& attributes);

			ShapeType _shape_type;
			unsigned int _vertex_array_object;
			unsigned int _vertex_buffer_object;
			unsigned int _number_vertices;
			bool _use_indices;
	};
}

#endif
