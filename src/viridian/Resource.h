#ifndef VIRIDIAN_RESOURCE_H
#define VIRIDIAN_RESOURCE_H

#include <memory>
#include <string>

namespace viridian
{
	class Resource
	{
	public:

		virtual ~Resource() {}

		std::string getName() { return name; }
		std::string getPath() { return path; }

		void setName(std::string _name) { name = _name; }
		void setPath(std::string _path) { path = _path; }

	private:

		std::string name;
		std::string path; 
	};
}

#endif