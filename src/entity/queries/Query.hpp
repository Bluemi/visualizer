#ifndef __QUERY_CLASS__
#define __QUERY_CLASS__

#include <vector>
#include <string>

#include "../../shape/ShapeSpecification.hpp"
#include "QuerySpace.hpp"

namespace visualizer {
	class Movable;
	enum class ShapeType;

	class Query {
		public:
			Query();

			Query& with_shape(const ShapeType& spec);
			Query& with_position(const QuerySpace& space);
			Query& with_groups(const std::vector<std::string>& groups);
			Query& with_tags(const std::vector<std::string>& tags);
			Query& exclude_tags(const std::vector<std::string>& tags);

			bool entity_included(const Movable& movable) const;
			const std::vector<std::string>& get_groups() const;
		private:
			std::vector<ShapeType> _shape_types;
			QuerySpace _space;
			std::vector<std::string> _groups;
			std::vector<std::string> _include_tags;
			std::vector<std::string> _exclude_tags;
	};
}

#endif
