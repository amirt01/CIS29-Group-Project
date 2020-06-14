#include "pch.h"
#include "WriteToFileError.h"

namespace exc {
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