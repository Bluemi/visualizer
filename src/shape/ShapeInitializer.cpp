#include "ShapeInitializer.hpp"

#include <iostream>
#include <cstring>
#include <glm/glm.hpp>

#include "Shape.hpp"
#include "../misc/Types.hpp"

namespace visualizer
{
	namespace initialize
	{
		Shape cube()
		{
			float vertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			};

			std::vector<Attribute> attributes = {Shape::PositionAttribute, Shape::TextureCoordinateAttribute};

			return Shape::create(vertices, 36, attributes, CubeSpecification());
		}

		class Triangle
		{
			public:
				Triangle(const glm::vec3& p1_arg, const glm::vec3& p2_arg, const glm::vec3& p3_arg)
					: p1(p1_arg), p2(p2_arg), p3(p3_arg)
				{}

				const static unsigned char POSITION_BIT = 0b00000001;
				const static unsigned char NORMALE_BIT  = 0b00000010;

				static std::vector<Triangle> split(const Triangle& triangle)
				{
					glm::vec3 p12 = (triangle.p1 + triangle.p2) / 2.f;
					glm::vec3 p13 = (triangle.p1 + triangle.p3) / 2.f;
					glm::vec3 p23 = (triangle.p2 + triangle.p3) / 2.f;

					return std::vector<Triangle> {
						Triangle(triangle.p1, p12, p13),
						Triangle(triangle.p2, p12, p23),
						Triangle(triangle.p3, p13, p23),
						Triangle(p12, p13, p23)
					};
				}

				void normalize()
				{
					p1 = glm::normalize(p1);
					p2 = glm::normalize(p2);
					p3 = glm::normalize(p3);
				}

				/**
				 * Returns the number of floats used for one triangle, if loaded.
				 */
				static size_t get_size(const unsigned char flags)
				{
					unsigned int n_floats = 0;
					if (flags & POSITION_BIT)
						n_floats += 9;
					if (flags & NORMALE_BIT)
						n_floats += 9;
					return n_floats;
				}

				void load_into(float* vertices, const unsigned char flags)
				{
					if (flags & POSITION_BIT) {
						if (flags & NORMALE_BIT) {
							float verts[] = {p1.x, p1.y, p1.z, p1.x, p1.y, p1.z,
											 p2.x, p2.y, p2.z, p2.x, p2.y, p2.z,
											 p3.x, p3.y, p3.z, p3.x, p3.y, p3.z};
							memcpy(vertices, verts, sizeof(verts));
						} else {
							float verts[] = {p1.x, p1.y, p1.z,
											 p2.x, p2.y, p2.z,
											 p3.x, p3.y, p3.z};
							memcpy(vertices, verts, sizeof(verts));
						}
					} else {
						std::cout << __FILE__ << ":" << __LINE__ << ": not supported" << std::endl;
					}

				}

				glm::vec3 p1, p2, p3;
		};

		std::vector<Triangle> split_triangles(std::vector<Triangle> triangles, unsigned int fineness)
		{
			for (unsigned int i = 0; i < fineness; i++)
			{
				std::vector<Triangle> tmp = triangles;
				triangles.clear();
				for (const Triangle& t : tmp)
				{
					std::vector<Triangle> temp = Triangle::split(t);
					triangles.insert(triangles.end(), temp.begin(), temp.end());
				}
			}

			return triangles;
		}

		void normalize_triangles(std::vector<Triangle>* triangles)
		{
			for (Triangle& t : *triangles)
			{
				t.normalize();
			}
		}

		Shape sphere(unsigned int fineness, bool use_normales)
		{
			glm::vec3 top(0.0f,  1.0f,  0.0f);
			glm::vec3 bot(0.0f, -1.0f,  0.0f);

			glm::vec3 p1( 1.0f,  0.0f,  0.0f);
			glm::vec3 p2( 0.0f,  0.0f,  1.0f);
			glm::vec3 p3(-1.0f,  0.0f,  0.0f);
			glm::vec3 p4( 0.0f,  0.0f, -1.0f);

			std::vector<Triangle> triangles {
				Triangle(top, p1, p2),
				Triangle(top, p2, p3),
				Triangle(top, p3, p4),
				Triangle(top, p4, p1),

				Triangle(bot, p1, p2),
				Triangle(bot, p2, p3),
				Triangle(bot, p3, p4),
				Triangle(bot, p4, p1),
			};

			triangles = split_triangles(triangles, fineness);
			normalize_triangles(&triangles);

			unsigned char flags = Triangle::POSITION_BIT;
			if (use_normales)
				flags |= Triangle::NORMALE_BIT;

			unsigned int number_floats = Triangle::get_size(flags);

			float vertices[number_floats*triangles.size()];
			for (unsigned int i = 0; i < triangles.size(); i++)
			{
				triangles[i].load_into(vertices+i*number_floats, flags);
			}

			std::vector<Attribute> attributes = {Shape::PositionAttribute};
			if (flags & Triangle::NORMALE_BIT)
				attributes.push_back(Shape::NormaleAttribute);

			return Shape::create(vertices, triangles.size() * 3, attributes, SphereSpecification(fineness));
		}
	}
}
