#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <random>
#include "Vector2.h"

enum class AttackType
{
	None,
	Slash,
	Stab,
	Strike
};

std::unordered_map<std::string, AttackType> string_to_attacktype = { 
	{ u8"Õ¶»÷", AttackType::Slash },
	{ u8"´©´Ì", AttackType::Stab },
	{ u8"´ò»÷", AttackType::Strike },
	{ u8"ÎÞ", AttackType::None }
};

std::unordered_map<AttackType, std::string> attacktype_to_string = {
	{ AttackType::Slash, u8"Õ¶»÷" },
	{ AttackType::Stab, u8"´©´Ì" },
	{ AttackType::Strike, u8"´ò»÷" },
	{ AttackType::None, u8"ÎÞ" }
};

enum class SinType
{
	None,
	Pride,
	Wrath,
	Lust,
	Sloth,
	Gluttony,
	Envy,
	Melancholy
};

std::unordered_map<std::string, SinType> string_to_sintype = {
	{ u8"ÎÞ", SinType::None },
	{ u8"°ÁÂý", SinType::Pride },
	{ u8"±©Å­", SinType::Wrath },
	{ u8"É«Óû", SinType::Lust },
	{ u8"µ¡¶è", SinType::Sloth },
	{ u8"±©Ê³", SinType::Gluttony },
	{ u8"¼µ¶Ê", SinType::Envy },
	{ u8"ÓÇÓô", SinType::Melancholy }
};

std::unordered_map<SinType, std::string> sintype_to_string = {
	{ SinType::None, u8"ÎÞ" },
	{ SinType::Pride, u8"°ÁÂý" },
	{ SinType::Wrath, u8"±©Å­" },
	{ SinType::Lust, u8"É«Óû" },
	{ SinType::Sloth, u8"µ¡¶è" },
	{ SinType::Gluttony, u8"±©Ê³" },
	{ SinType::Envy, u8"¼µ¶Ê" },
	{ SinType::Melancholy, u8"ÓÇÓô" }
};

struct Coin
{
	bool is_Broke = false;
	bool current_Face;
	int Point;
};

class Skill
{
public:
	Skill() = default;
	~Skill() = default;

	std::string Name;
	int Attack_Level;
	int Base;
	int Change;
	AttackType Attack_Type = AttackType::None;
	SinType Sin_Type = SinType::None;
	std::vector<Coin> Coin;

	int Point;
	int Damage;

	bool isAllCoinBroke() {
		for (size_t i = 0; i < Coin.size(); i++)
		{
			if (!Coin[i].is_Broke) {
				return false;
			}
		}
		return true;
	}

};

enum class Status
{
	normal,
	confusion,
	dead
};

class CharacterData
{
public:
	CharacterData(const std::string& name, const std::vector<std::string>& tag_list, const std::vector<Skill>& skill_list, int level, const Vector2& health, const Vector2& sanity, const Vector2& speed) {
		Name = name;
		Tag_List = tag_list;
		Skill_List = skill_list;
		Level = level;
		Health = health;
		Sanity = sanity;
		Speed = speed;
	}
	CharacterData() = default;
	~CharacterData() = default;

	std::string Name;
	std::vector<std::string> Tag_List;
	std::vector<Skill> Skill_List;
	std::vector<int> Skill_weight;
	int Level;
	Vector2 Health;
	Vector2 Sanity;
	Vector2 Speed;
	std::unordered_map<AttackType, float> Attack_Type_Resist;
	std::queue<float> Confusion;

private:
};

class BattleCharacter
{
public:
	BattleCharacter(const CharacterData* data) {
		Data = data;
		reset();
	}
	BattleCharacter() = default;
	~BattleCharacter() = default;

	void loadCharacterData(const CharacterData* ch) {
		Data = ch;
		reset();
	}

	void setCurrentSkill(int index) {
		skill.Name = Data->Skill_List[index].Name;
		skill.Attack_Level = Data->Skill_List[index].Attack_Level;
		skill.Base = Data->Skill_List[index].Base;
		skill.Change = Data->Skill_List[index].Change;
		skill.Attack_Type = Data->Skill_List[index].Attack_Type;
		skill.Sin_Type = Data->Skill_List[index].Sin_Type;
		skill.Coin = Data->Skill_List[index].Coin;
	}

	bool checkConfusion() {
		if (status == Status::confusion)
		{
			status = Status::normal;
		}
		if (confusion.empty()) {
			return false;
		}
		if (health <= Data->Health.y * confusion.front())
		{
			confusion.pop();
			status = Status::confusion;
			return true;
		}
		return false;
	}

	bool checkDeath() {
		if (health < Data->Health.x)
		{
			health = Data->Health.x;
			status = Status::dead;
			return true;
		}
		return false;
	}

	void rollSpeed() {
		speed_rd.param(std::uniform_int_distribution<int>::param_type(Data->Speed.x, Data->Speed.y));
		speed = speed_rd(random);
	}

	void rollWeight() {
		weight = weight_rd(random);
	}

	void reset() {
		if (!Data) return;
		health = Data->Health.y;
		sanity = 0;
		speed = Data->Speed.x;
		confusion = Data->Confusion;
		status = Status::normal;
		damage = 0;
		weight_rd.param(std::discrete_distribution<>::param_type(Data->Skill_weight.begin(), Data->Skill_weight.end()));
	}

public:

	void rollPoint() {
		skill.Point = skill.Base;
		for (size_t i = 0; i < skill.Coin.size(); i++)
		{
			sanity_rd.param(std::bernoulli_distribution::param_type(0.5 + sanity * 0.01));
			if (sanity_rd(random)) {
				skill.Coin[i].current_Face = true;
			}
			else
			{
				skill.Coin[i].current_Face = false;
			}
		}
	}

	int point;
	int damage;

	std::random_device rd;
	std::mt19937 random = std::mt19937(rd());
	std::bernoulli_distribution sanity_rd;
	std::uniform_int_distribution<int> speed_rd;
	std::discrete_distribution<int> weight_rd;

	const CharacterData* Data = nullptr;

	Skill skill;

	int weight;
	int choice;
	Status status = Status::normal;
	std::queue<float> confusion;
	int health;
	int sanity;
	int speed;
};