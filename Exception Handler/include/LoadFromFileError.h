#pragma once

namespace exc {
	class LoadFromFileError
	{
	private:
		std::string path;
	public:
		LoadFromFileError(const std::string& path);

		const std::string what() const;
	};
}