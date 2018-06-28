#include "ShapeInitializer.hpp"

#include <iostream>
#include <cstring>
#include <glm/glm.hpp>

#include "Shape.hpp"

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

			return Shape::create(vertices, 36, attributes);
		}

		class Triangle
		{
			public:
				Triangle(const glm::vec3& p1_arg, const glm::vec3& p2_arg, const glm::vec3& p3_arg)
					: p1(p1_arg), p2(p2_arg), p3(p3_arg)
				{}

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

				void load_into(float* vertices)
				{
					float verts[] = {p1.x, p1.y, p1.z,
									 p2.x, p2.y, p2.z,
									 p3.x, p3.y, p3.z};
					memcpy(vertices, verts, sizeof(verts));
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

		Shape sphere(unsigned int fineness)
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

			unsigned int number_floats = triangles.size() * 3 * 3;

			float vertices[number_floats];
			for (unsigned int i = 0; i < triangles.size(); i++)
			{
				triangles[i].load_into(vertices+i*9);
			}

			std::vector<Attribute> attributes = {Shape::PositionAttribute};

			return Shape::create(vertices, triangles.size() * 3, attributes);
		}
	}
}
