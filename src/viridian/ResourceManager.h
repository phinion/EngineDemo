#include "Resource.h"

#include <string>
#include <memory>
#include <vector>


namespace viridian
{

	class ResourceManager
	{
	public:

		template <typename T>
		std::shared_ptr<T> loadResource(std::string _name)
		{
			std::shared_ptr<T> rtn;
			for (std::vector<std::shared_ptr<Resource>>::iterator i = resources.begin(); i != resources.end(); ++i)
			{

				if ((*i)->getName() == _name)
				{
					rtn = std::dynamic_pointer_cast<T>(*i);
					if (rtn)
					{
						return rtn;
					}
				}
			}
			throw std::exception();
			return nullptr;
		}


		template <typename T>
		std::shared_ptr<T> addResource(const std::string& _name, std::string &_path)
		{
			std::shared_ptr<T> resource = std::make_shared<T>(_path);
			resource->setName(_name);
			resource->setPath(_path);
			resources.push_back(resource);
			return resource;
		}

		std::vector<std::shared_ptr<Resource>> getResources() { return resources; }

	private:

		std::vector<std::shared_ptr<Resource>> resources;  
	};
}