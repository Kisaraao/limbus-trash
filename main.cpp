#include <iostream>
#include <Windows.h>

#include "Vector2.h"
#include "Character.h"
#include "Character Pool.h"
#include "XML.h"
#include "Battle Manager.h"

bool Running = true;

CharacterPool character_pool;

int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	CharacterXML xml;

	character_pool.addCharacter("yzr");
	character_pool.addCharacter("yhb");

	character_pool.addCharacter("valencina");
	character_pool.addCharacter("yhb_yzr");
	character_pool.addCharacter("tang_yi");
	character_pool.addCharacter("erlking_heathcilff");

	character_pool.addCharacter("test");

	BattleManager battle_manager(
		character_pool.get("valencina"),
		character_pool.get("valencina")
	);

	while (Running)
	{
		battle_manager.on_enter();
		battle_manager.on_update();
		battle_manager.on_draw();
		battle_manager.on_exit();
	}

	return 0;
}