#include "pch.h"
#include "LoadFromFileError.h"

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
}