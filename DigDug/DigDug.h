#pragma once
#include "Minigin.h"

class DigDug final : public dae::Minigin
{
public:
	DigDug();
	~DigDug();

protected:
	void LoadGame() const override;
};

