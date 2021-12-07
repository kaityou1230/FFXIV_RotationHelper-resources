#pragma once

namespace FFXIV_RotationHelper_resources
{
	// https://github.com/xivapi/ffxiv-datamining/blob/master/csv/ActionCategory.csv
	enum class ActionCategory
	{
		None = 0,
		Auto_Attack = 1,
		Spell = 2,
		Weaponskill = 3,
		Ability = 4,
		Item = 5,
		DoL_Ability = 6,
		DoH_Ability = 7,
		Event = 8,
		Limit_Break = 9,
		System_1 = 10,
		System_2 = 11,
		Mount = 12,
		Special = 13,
		Item_Manipulation = 14,
		Adrenaline_Rush = 15,
		Unknown = 16,
		Artillery = 17,
	};
}