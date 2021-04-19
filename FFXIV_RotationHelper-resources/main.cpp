#include <iostream>
#include <cassert>

#include "ActionTableViewer.h"
#include "ClassJob.h"
#include "ClassJobList.h"
#include "WebReader.h"

using namespace FFXIV_RotationHelper_resources;

int main()
{
	//https://github.com/microsoft/cpprestsdk/wiki/Getting-Started-Tutorial

	std::cout << "Loading tables ..." << std::endl;
	WebReader actionsReader = WebReader(L"https://raw.githubusercontent.com/xivapi/ffxiv-datamining/master/csv/Action.csv");
	WebReader classJobCategoryReader = WebReader(L"https://raw.githubusercontent.com/xivapi/ffxiv-datamining/master/csv/ClassJobCategory.csv");
	std::cout << "Completed" << std::endl;

	assert(actionsReader.GetCount());
	assert(classJobCategoryReader.GetCount());

	ClassJobList* classJobList = new ClassJobList(classJobCategoryReader);
	ActionTableViewer viewer(actionsReader);

	for (const ClassJob& classJob : *classJobList)
	{
		//if (classJob.GetShortName() == "WAR" ||
		//	classJob.GetShortName() == "WHM")
		//{
		//	viewer.Edit(classJob);
		//}
		//else
		{
			viewer.Print(classJob);
		}
	}

	delete classJobList;

	return 0;
}