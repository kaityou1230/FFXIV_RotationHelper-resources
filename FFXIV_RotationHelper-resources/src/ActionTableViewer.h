#pragma once

#include <string>

namespace FFXIV_RotationHelper_resources
{
	class WebReader;
	class SplitedString;
	class CSVWriter;
	class ClassJob;
	class ClassJobList;

	class ActionTableViewer
	{
	public:
		ActionTableViewer(const WebReader& actionsReader);

		~ActionTableViewer();

		void Print(const ClassJob& classJob) const;

		void Edit(const ClassJob& classJob);

	private:
		void printRow(const SplitedString& row) const;

		bool isValidAction(const SplitedString& row, const ClassJob& classJob) const;

		bool isNumber(const std::string& str) const;

	private:
		const WebReader* actionTable;
		const int actionTableRowStart = 3;
		CSVWriter* csv;
	};
}
