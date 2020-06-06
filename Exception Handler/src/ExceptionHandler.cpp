#include "pch.h"
#include "ExceptionHandler.h"

namespace exc {
	LoadFromFileError::LoadFromFileError(const std::string& path)
		: path(path)
	{
	}

	const std::string LoadFromFileError::what() const
	{
		static std::string ret;
		ret = "Error Loading data from file.\n";
		ret += "File path: ";
		ret += path;
		ret += "\n";
		return ret;
	}

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

	WriteToFileError::WriteToFileError(const std::string& path)
		: path(path)
	{
	}

	const std::string WriteToFileError::what() const
	{
		static std::string ret;
		ret = "Error writing data to file.\n";
		ret += "File path: ";
		ret += path;
		ret += "\n";
		return ret;
	}
}