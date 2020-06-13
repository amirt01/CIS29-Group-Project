#include "pch.h"
#include "SpawnError.h"

namespace exc {
	SpawnError::SpawnError(const unsigned int& level, const unsigned int& type)
		: level(level), type(type)
	{
	}

	const std::string SpawnError::what() const
	{
		static std::string ret;
		ret = "Error spawning object.\n";
		ret += "Level: ";
		ret += std::to_string(level);
		ret += "\nType: ";
		ret += type;
		ret += "\n";
		return ret;
	}
}