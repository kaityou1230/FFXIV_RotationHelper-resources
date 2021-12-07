#include "ClassJobList.h"

#include <string>

#include "ClassJob.h"
#include "ClassJobColumn.h"
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
		{ ClassJobColumn::PLD, "Paladin", webReader },
		{ ClassJobColumn::WAR, "Warrior", webReader },
		{ ClassJobColumn::DRK, "Dark Knight", webReader },
		{ ClassJobColumn::GNB, "Gunbreaker", webReader },

		// Healer
		{ ClassJobColumn::WHM, "White Mage", webReader },
		{ ClassJobColumn::SCH, "Scholar", webReader },
		{ ClassJobColumn::AST, "Astrologian", webReader },
		{ ClassJobColumn::SGE, "Sage", webReader },

		// Melee DPS
		{ ClassJobColumn::MNK, "Monk", webReader },
		{ ClassJobColumn::DRG, "Dragoon", webReader },
		{ ClassJobColumn::NIN, "Ninja", webReader },
		{ ClassJobColumn::SAM, "Samurai", webReader },
		{ ClassJobColumn::RPR, "Reaper", webReader },

		// Ranged DPS
		{ ClassJobColumn::BRD, "Bard", webReader },
		{ ClassJobColumn::MCH, "Machinist", webReader },
		{ ClassJobColumn::DNC, "Dancer", webReader },

		// Caster
		{ ClassJobColumn::BLM, "Black Mage", webReader },
		{ ClassJobColumn::SMN, "Summoner", webReader },
		{ ClassJobColumn::RDM, "Red Mage", webReader },
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
