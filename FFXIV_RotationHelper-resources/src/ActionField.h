#pragma once

namespace FFXIV_RotationHelper_resources
{
	//https://github.com/xivapi/ffxiv-datamining/blob/master/csv/Action.csv
	enum class ActionField
	{
		Key					= 0,
		Name				= 1,
		ActionCategory		= 4,
		ClassJob			= 11,
		ClassJobLevel		= 13,
		IsRoleAction		= 14,
		Range				= 15,
		ClassJobCategory	= 49,
		IsPvP				= 54,
		IsPlayerAction		= 66,
	};
}
