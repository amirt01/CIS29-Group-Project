#pragma once

namespace exc {
	class WriteToFileError
	{
	private:
		std::string path;
	public:
		WriteToFileError(const std::string& path);

		const std::string what() const;
	};
}