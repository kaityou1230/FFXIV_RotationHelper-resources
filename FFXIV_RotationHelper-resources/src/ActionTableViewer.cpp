#include "ActionTableViewer.h"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <stack>
#include <string>

#include "ActionCategory.h"
#include "ActionField.h"
#include "CSVWriter.h"
#include "ClassJob.h"
#include "SplitedString.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

ActionTableViewer::ActionTableViewer(const WebReader& actionsReader)
{
	actionTable = &actionsReader;
	csv = new CSVWriter("output.csv", "ClassName,ActionName,GameIdx,DBIdx");
}

ActionTableViewer::~ActionTableViewer()
{
	if (csv)
	{
		delete csv;
	}
}

void ActionTableViewer::Print(const ClassJob& classJob) const
{
	std::cout << classJob.GetFullName() << std::endl;

	int rowCount = 0;
	int actionCount = actionTable->GetCount();
	for (int i = actionTableRowStart; i < actionCount; i++)
	{
		const SplitedString& row = actionTable->Get(i);

		if (!isValidAction(row, classJob))
		{
			continue;
		}

		printRow(row);
		rowCount++;
	}

	std::cout << "Row Count : " << rowCount << std::endl << std::endl;
}

void ActionTableViewer::Edit(const ClassJob& classJob)
{
	std::cout << classJob.GetFullName() << std::endl;

	std::stack<int> prevValidIdxes;
	int actionCount = actionTable->GetCount();
	for (int i = actionTableRowStart; i < actionCount; i++)
	{
	REPEAT:

		const SplitedString& row = actionTable->Get(i);

		if (!isValidAction(row, classJob))
		{
			continue;
		}

		printRow(row);

		std::string dbIdx;
		do
		{
			std::cin >> dbIdx;

			// entered "return", return to last action to edit
			if (prevValidIdxes.size() > 0 && dbIdx == "return")
			{
				csv->EraseTop();
				i = prevValidIdxes.top();
				prevValidIdxes.pop();

				goto REPEAT;
			}

			// if input string was not numbers, insert again
		} while (!isNumber(dbIdx));

		csv->Write(classJob.GetFullName());
		csv->Write(',');

		csv->Write(row[(int)ActionField::Name]);
		csv->Write(',');

		csv->Write(row[(int)ActionField::Key]);
		csv->Write(',');

		csv->Write(dbIdx);
		csv->NewLine();

		prevValidIdxes.push(i);
	}

	std::cout << std::endl;
	csv->Save();
}

void ActionTableViewer::printRow(const SplitedString& row) const
{
	std::cout << std::left << std::setw(6) << row[(int)ActionField::Key] << " / ";
	std::cout << std::left << std::setw(40) << row[(int)ActionField::Name] << " / ";
	std::cout << std::left << std::setw(5) << row[(int)ActionField::ClassJobCategory] << " / ";
	std::cout << row[(int)ActionField::IsPlayerAction] << std::endl;
}

bool ActionTableViewer::isValidAction(const SplitedString& row, const ClassJob& classJob) const
{
	int classJobField = stoi(row[(int)ActionField::ClassJob]);
	int classJobLevelField = stoi(row[(int)ActionField::ClassJobLevel]);
	if (classJobField < 0 && classJobLevelField <= 0)
	{
		// deprecated actions or logos actions etc ..
		return false;
	}

	int classJobCategoryField = stoi(row[(int)ActionField::ClassJobCategory]);
	if (classJobCategoryField == 1)
	{
		// all classes can use this action, so ignore it
		return false;
	}

	if (!classJob.IsClassJobCategory(classJobCategoryField))
	{
		// this action is not for this classJob
		return false;
	}

	if (row[(int)ActionField::IsPvP] == "True")
	{
		return false;
	}

	int actionCategoryField = stoi(row[(int)ActionField::ActionCategory]);
	if (actionCategoryField != (int)ActionCategory::Spell &&
		actionCategoryField != (int)ActionCategory::Weaponskill &&
		actionCategoryField != (int)ActionCategory::Ability)
	{
		return false;
	}

	return true;
}

bool ActionTableViewer::isNumber(const std::string& str) const
{
	int len = (int)str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return false;
		}
	}

	return true;
}
