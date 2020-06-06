#pragma once

namespace exc {
	class SpawnError
	{
	private:
		const unsigned int level;
		const unsigned int type;
	public:
		SpawnError(const unsigned int& level, const unsigned int& type);

		const std::string what() const;
	};

	class LoadFromFileError
	{
	private:
		std::string path;
	public:
		LoadFromFileError(const std::string& path);

		const std::string what() const;
	};

	class WriteToFileError
	{
	private:
		std::string path;
	public:
		WriteToFileError(const std::string& path);

		const std::string what() const;
	};
}