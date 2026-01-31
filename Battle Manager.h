#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <array>
#include "Character.h"

extern bool Running;

class BattleManager
{
public:
	BattleManager(CharacterData* player, CharacterData* enemy) {
		Player.loadCharacterData(player);
		Enemy.loadCharacterData(enemy);

		round = 0;
		for (size_t i = 0; i < dashboard.size(); i++)
		{
			Player.rollWeight();
			dashboard[i] = Player.weight;
		}
	}
	~BattleManager() = default;

	enum class State
	{
		input,
		combat,
		player_damage,
		enemy_damage,
		calcDamage
	};

	void on_enter() {
		SetColor(8);
		switch (state)
		{
		case BattleManager::State::input:
			SetColor(8);
			std::cout << u8"回合数： " << round + 1 << "\n\n";
			break;
		case BattleManager::State::combat:
			break;
		case BattleManager::State::player_damage:
			break;
		case BattleManager::State::enemy_damage:
			break;
		case BattleManager::State::calcDamage:
			break;
		default:
			break;
		}
	}

	void on_update() {
		switch (state)
		{
		case BattleManager::State::input:
			Enemy.rollWeight();
			Enemy.choice = Enemy.weight;
			Enemy.setCurrentSkill(Enemy.choice);
			if (round == 0)
			{
				for (size_t i = 0; i < dashboard.size(); i++)
				{
					Player.rollWeight();
					dashboard[i] = Player.weight;
				}
			}
			else 
			{
				if (choice == 1) { dashboard[1] = dashboard[0]; }
				Player.rollWeight();
				dashboard[0] = Player.weight;
			}
			break;
		case BattleManager::State::combat:
			break;
		case BattleManager::State::player_damage:
			break;
		case BattleManager::State::enemy_damage:
			break;
		case BattleManager::State::calcDamage:
			//检测混乱
			Player.checkConfusion();
			Enemy.checkConfusion();
			//检测死亡，结束游戏
			if (Player.checkDeath())
			{
				SetColor(4);
				std::cout << Player.Data->Name << u8"死了！" << "\n";
				SetColor(8);
				Running = false;
			}
			else if (Enemy.checkDeath())
			{
				SetColor(4);
				std::cout << Enemy.Data->Name << u8"死了！" << "\n";
				SetColor(8);
				Running = false;
			}
			break;
		default:
			break;
		}
	}

	void on_draw() {
		switch (state)
		{
		case BattleManager::State::input:
			showCharacterStatus(&Player);
			showCharacterStatus(&Enemy);

			if (Enemy.status != Status::confusion)
			{
				std::cout << Enemy.Data->Name << u8" 正在使用： \n";
				showSkillStatus(Enemy.skill);
			}

			if (Player.status != Status::confusion)
			{
				std::cout << u8"\n——————————————仪表盘——————————————" << "\n\n";
				for (size_t i = 0; i < dashboard.size(); i++)
				{
					SetColor(15);
					std::cout << i + 1 << u8". ";
					showSkillStatus(Player.Data->Skill_List[dashboard[i]]);
					std::cout << "\n";
				}
				std::cout << u8"———————————————————————————————" << "\n";
				std::cout << u8"请选择技能： ";
				std::cin >> choice;
				choice--;
				Player.choice = dashboard[choice];
				Player.setCurrentSkill(Player.choice);
			}
			break;
		case BattleManager::State::combat:
			if (Player.status != Status::confusion && Enemy.status != Status::confusion)
			{
				int player_index = 0;
				int enemy_index = 0;
				do
				{

					do
					{
						Player.point = rollPoint(Player);
						if (isLevelDiff(Player, Enemy)) {
							Player.point += static_cast<int>((Player.skill.Attack_Level - Enemy.skill.Attack_Level) / 3);
						}
						std::cout << u8" 点数： " << Player.point << "\n";

						Enemy.point = rollPoint(Enemy);
						if (isLevelDiff(Enemy, Player)) {
							Enemy.point += static_cast<int>((Enemy.skill.Attack_Level - Player.skill.Attack_Level) / 3);
						}
						std::cout << u8" 点数： " << Enemy.point << "\n\n";
					} while (Player.point == Enemy.point);

					if (Player.point > Enemy.point)
					{
						Enemy.skill.Coin[enemy_index].is_Broke = true;
						enemy_index++;
					}
					else {
						Player.skill.Coin[player_index].is_Broke = true;
						player_index++;
					}

					Sleep(500);

				} while (!Player.skill.isAllCoinBroke() && !Enemy.skill.isAllCoinBroke());
			}
			else
			{
				Player.point = 0;
				Enemy.point = 0;
				if (Player.status == Status::confusion)
				{
					Enemy.point = rollPoint(Enemy);
					if (isLevelDiff(Enemy, Player)) {
						Enemy.point += static_cast<int>((Enemy.skill.Attack_Level - Player.skill.Attack_Level) / 3);
					}
					std::cout << u8" 点数： " << Enemy.point << "\n\n";
				}
				if (Enemy.status == Status::confusion)
				{
					Player.point = rollPoint(Player);
					if (isLevelDiff(Player, Enemy)) {
						Player.point += static_cast<int>((Player.skill.Attack_Level - Enemy.skill.Attack_Level) / 3);
					}
					std::cout << u8" 点数： " << Player.point << "\n\n";
				}
			}
			break;
		case BattleManager::State::player_damage:
			break;
		case BattleManager::State::enemy_damage:
			break;
		case BattleManager::State::calcDamage:
			break;
		default:
			break;
		}
	}

	void on_exit() {
		switch (state)
		{
		case BattleManager::State::input:
			state = State::combat;
			break;
		case BattleManager::State::combat:
			if (Player.point > Enemy.point)
			{
				Player.sanity += 6;
				Enemy.sanity -= 3;
				makeDamage(Player, Enemy);
			}
			else if (Enemy.point > Player.point) {
				Player.sanity -= 3;
				Enemy.sanity += 6;
				makeDamage(Enemy, Player);
			}
			state = State::calcDamage;
			break;
		case BattleManager::State::player_damage:
			state = State::calcDamage;
			break;
		case BattleManager::State::enemy_damage:
			state = State::calcDamage;
			break;
		case BattleManager::State::calcDamage:
			++round;
			system("pause");
			system("cls");
			state = State::input;
			break;
		default:
			break;
		}
	}

	void showCharacterStatus(BattleCharacter* ch) {
		SetColor(15);
		std::cout << ch->Data->Name << " ";
		SetColor(8);
		std::cout << u8"等级： ";
		SetColor(15);
		std::cout << ch->Data->Level << " ";
		SetColor(8);
		std::cout << u8"当前血量： ";
		SetColor(15);
		std::cout << ch->health << " / " << ch->Data->Health.y << " ";
		SetColor(8);
		std::cout << u8"当前理智： ";
		if (ch->sanity < 0)
		{
			SetColor(4);
		}else
		{
			SetColor(9);
		}
		std::cout << ch->sanity << " ";
		SetColor(8);
		std::cout << u8"当前速度： " << ch->speed << "\n";
		std::cout << u8"特性关键词： ";
		for (size_t i = 0; i < ch->Data->Tag_List.size(); i++)
		{
			std::cout << "[" << ch->Data->Tag_List[i] << "] ";
		}
		std::cout << u8"下一次混乱： ";
		if (!ch->confusion.empty()) {
			std::cout << ch->Data->Health.y * ch->confusion.front();
		}else {
			std::cout << u8"无";
		}
		std::cout << "\n";
		if (ch->status == Status::confusion)
		{
			SetColor(4);
			std::cout << u8"！陷入混乱！" << "\n";
			SetColor(8);
		}
		std::cout << "\n\n";
	}

	void showSkillStatus(const Skill& skl) {
		testSinColor(skl.Sin_Type);
		std::cout << "[" << skl.Name << "] ";
		for (size_t i = 0; i < skl.Coin.size(); i++)
		{
			SetColor(14);
			std::cout << u8"●";
		}
		SetColor(8);
		std::cout << u8" 攻击等级： " << skl.Attack_Level << "\n";
		std::cout << u8"基础威力： " << skl.Base << " "
			<< u8"变动威力： " << skl.Change << " "
			<< u8"攻击类型： " << attacktype_to_string.find(skl.Attack_Type)->second << " " << u8"罪孽类型： ";;
		testSinColor(skl.Sin_Type);
		std::cout << sintype_to_string.find(skl.Sin_Type)->second << "\n";
		SetColor(8);
	}

	int rollPoint(BattleCharacter& ch) {
		ch.rollPoint();
		testSinColor(ch.skill.Sin_Type);
		std::cout << "   " << ch.skill.Name << " ";
		int point = ch.skill.Base;

		if (!ch.skill.isAllCoinBroke())
		{
			for (size_t i = 0; i < ch.skill.Coin.size(); i++)
			{
				const Coin& coin = ch.skill.Coin[i];
				if (!coin.is_Broke)  // 未破碎的普通硬币
				{
					if (coin.current_Face) {
						point += ch.skill.Change;
						SetColor(14);  // 黄色 - 正面
					}
					else {
						SetColor(6);   // 棕色 - 反面
					}
					std::cout << u8"●";
				}
				else  // 破碎的普通硬币
				{
					SetColor(8);       // 灰色 - 破碎
					std::cout << u8"×";
				}
			}
			SetColor(8);
			return point;
		}
		else {
			return 0;
		}
	}

	bool isLevelDiff(BattleCharacter& ch_0, BattleCharacter& ch_1) {
		if (ch_0.skill.Attack_Level > ch_1.skill.Attack_Level)
		{
			return true;
		}
		return false;
	}

	void makeDamage(BattleCharacter& attacker, BattleCharacter& target) {
		std::cout << attacker.Data->Name << u8" 对 " << target.Data->Name << u8" 使用了\n";
		SetColor(8);
		int damage = rollPoint(attacker);
		if (damage != 0)
		{
			float resist;
			if (isLevelDiff(attacker, target))
			{
				damage += static_cast<int>((attacker.skill.Attack_Level - target.skill.Attack_Level) / 3);
			}

			std::cout << "\n";

			if (target.status == Status::confusion) { resist = 2; }
			else { resist = target.Data->Attack_Type_Resist.at(attacker.skill.Attack_Type); }

			int finalDamage = static_cast<int>(damage * resist);
			attacker.damage = finalDamage;
			target.health -= attacker.damage;
			std::cout << u8"造成了 " << attacker.damage << u8" 点伤害。" << "\n\n";
		}
	}

	void SetColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	void testSinColor(const SinType& sintype) {
		switch (sintype)
		{
		case SinType::None:
			SetColor(8);
			break;
		case SinType::Pride:
			SetColor(1);
			break;
		case SinType::Wrath:
			SetColor(4);
			break;
		case SinType::Lust:
			SetColor(12);
			break;
		case SinType::Sloth:
			SetColor(6);
			break;
		case SinType::Gluttony:
			SetColor(10);
			break;
		case SinType::Envy:
			SetColor(5);
			break;
		case SinType::Melancholy:
			SetColor(3);
			break;
		default:
			SetColor(15);
			break;
		}
	}

private:
	BattleCharacter Player;
	BattleCharacter Enemy;
	State state = State::input;
	int round;
	int choice;
	std::array<int, 2> dashboard;
};