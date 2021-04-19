#include "ClassJobList.h"

#include <string>

#include "ClassJob.h"
#include "SplitedString.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

ClassJobList::Iterator::Iterator(ClassJob* _i)
	: i(_i)
{
}

bool ClassJobList::Iterator::operator==(const ClassJobList::Iterator& other) const
{
	return i == other.i;
}

bool ClassJobList::Iterator::operator!=(const ClassJobList::Iterator& other) const
{
	return i != other.i;
}

ClassJobList::Iterator& ClassJobList::Iterator::operator++()
{
	i++;

	return *this;
}

const ClassJob& ClassJobList::Iterator::operator*() const
{
	return *i;
}

ClassJobList::ClassJobList(const WebReader& webReader)
{
	jobs = new ClassJob[ClassJobCount]
	{
		// Tank
		{ "PLD", "Paladin", webReader },
		{ "WAR", "Warrior", webReader },
		{ "DRK", "Dark Knight", webReader },
		{ "GNB", "Gunbreaker", webReader },

		// Healer
		{ "WHM", "White Mage", webReader },
		{ "SCH", "Scholar", webReader },
		{ "AST", "Astrologian", webReader },

		// Melee DPS
		{ "MNK", "Monk", webReader },
		{ "DRG", "Dragoon", webReader },
		{ "NIN", "Ninja", webReader },
		{ "SAM", "Samurai", webReader },

		// Ranged DPS
		{ "BRD", "Bard", webReader },
		{ "MCH", "Machinist", webReader },
		{ "DNC", "Dancer", webReader },

		// Caster
		{ "BLM", "Black Mage", webReader },
		{ "SMN", "Summoner", webReader },
		{ "RDM", "Red Mage", webReader },
	};
}

ClassJobList::~ClassJobList()
{
	if (jobs)
	{
		delete[] jobs;
	}
}

ClassJobList::Iterator ClassJobList::begin() const
{
	return ClassJobList::Iterator(&jobs[0]);
}

ClassJobList::Iterator ClassJobList::end() const
{
	return ClassJobList::Iterator(&jobs[ClassJobCount]);
}
