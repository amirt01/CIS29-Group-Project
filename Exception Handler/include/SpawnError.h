#pragma once

namespace exc {
	class SpawnError
	{
	public:
		SpawnError();

		const std::string what() const;
	};
}
