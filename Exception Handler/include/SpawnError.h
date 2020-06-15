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
}
