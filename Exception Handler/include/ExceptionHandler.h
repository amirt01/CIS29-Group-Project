#pragma once

namespace exc {
	class SpawnError
	{
	private:
		const unsigned int level;
		const unsigned int type;
	public:
		SpawnError(const unsigned int& level, const unsigned int& type) : level(level), type(type) {};

		const std::string what() const {
			static std::string ret;
			ret = "Error spawning object.\n";
			ret += "Level: ";
			ret += std::to_string(level);
			ret += "\nType: ";
			ret += type;
			ret += "\n";
			return ret;
		};
	};

	class LoadFromFileError
	{
	private:
		std::string path;
	public:
		LoadFromFileError(const std::string& path) : path(path) {};

		const std::string what() const {
			static std::string ret;
			ret = "Error Loading data from file.\n";
			ret += "File path: ";
			ret += path;
			ret += "\n";
			return ret;
		};
	};

	class WriteToFileError
	{
	private:
		std::string path;
	public:
		WriteToFileError(const std::string& path) : path(path) {};

		const std::string what() const {
			static std::string ret;
			ret = "Error writing data to file.\n";
			ret += "File path: ";
			ret += path;
			ret += "\n";
			return ret;
		}
	};
}