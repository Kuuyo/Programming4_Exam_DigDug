#pragma once
#include "Minigin.h"

class DigDug final : public dae::Minigin
{
public:
	DigDug() = default;
	virtual ~DigDug() {}

	DigDug(const DigDug&) = delete;
	DigDug(DigDug&&) = delete;
	DigDug& operator= (const DigDug&) = delete;
	DigDug& operator= (const DigDug&&) = delete;

protected:
	void LoadGame() const override;
};

