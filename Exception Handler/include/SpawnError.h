#pragma once

enum class Levels;
enum class Color;

namespace exc {
	class SpawnError
	{
	private:
		const Levels level;
		const Color type;
	public:
		SpawnError(const Levels& level, const Color& type);

		const std::string what() const;
	};
}
