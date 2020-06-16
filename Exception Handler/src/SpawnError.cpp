#include "pch.h"
#include "SpawnError.h"

namespace exc {
	SpawnError::SpawnError()
	{
	}

	const std::string SpawnError::what() const
	{
		return "Unknown spawn error.\n";
	}
}