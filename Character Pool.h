#pragma once
#include <iostream>
#include "Character.h"
#include "XML.h"

class CharacterPool
{
public:
	CharacterPool() = default;
	~CharacterPool() {
		for (auto& pair : character_pool) {
			delete pair.second;  // 释放每个IMAGE对象
			pair.second = nullptr;
		}
		character_pool.clear();
	}

	bool addCharacter(const std::string& name) {
		if (character_pool.find(name) != character_pool.end()) {
			return false; // 角色已存在
		}

		std::string path = "script/Character/" + name + ".xml";
		CharacterData* newCharacter = new CharacterData();

		xml.loadXML(path, newCharacter);
		character_pool[name] = newCharacter;
	}

	CharacterData* get(const std::string& name) {
		auto it = character_pool.find(name);
		if (it != character_pool.end()) {
			return it->second;
		}
		return nullptr; // 明确返回空指针
	}

private:
	std::unordered_map<std::string, CharacterData*> character_pool;
	CharacterXML xml;
};