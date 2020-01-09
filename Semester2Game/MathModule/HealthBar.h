#pragma once

#include "JSON.h"

class HealthBar
{
public:
	//creates the Health bar
	HealthBar();
	//creates the health bar with this amount of health
	HealthBar(float health);
	//destroys the health bar
	~HealthBar();

	//displays the current health
	void DisplayHealth();

	//getters
	float GetHealth() const;
	//setters
	void SetHealth(float health);
private:
		//100% health
	float m_health = 1.f;
};

//send healthbar to json file
inline void to_json(nlohmann::json& j, const HealthBar& bar)
{
	j["Health"] = bar.GetHealth();
}

inline void from_json(const nlohmann::json& j, HealthBar& bar)
{
	bar.SetHealth(j["Health"]);
}