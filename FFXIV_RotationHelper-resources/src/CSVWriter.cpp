#include "CSVWriter.h"

using namespace FFXIV_RotationHelper_resources;

CSVWriter::CSVWriter(const std::string& fileName, const std::string& header)
	: lineIdx(0)
{
	file.open(fileName);
	file.write(header.c_str(), header.size());
	file.put('\n');

	lines.push_back(std::string());
}

CSVWriter::~CSVWriter()
{
	file.close();
}

void CSVWriter::Write(const std::string& str)
{
	lines[lineIdx].append(str);
}

void CSVWriter::Write(const char c)
{
	lines[lineIdx].append(1, c);
}

void CSVWriter::NewLine()
{
	lines.push_back(std::string());
	lineIdx++;
}

void CSVWriter::EraseTop()
{
	lines.erase(lines.begin() + lineIdx - 1);
	lineIdx--;
}

void CSVWriter::Save()
{
	for (int i = 0; i < lineIdx; i++)
	{
		file.write(lines[i].c_str(), lines[i].size());

		if (i < lineIdx - 1)
		{
			file.put('\n');
		}
	}

	std::vector<std::string>().swap(lines);
	lines.push_back(std::string("\n"));
	lineIdx = 0;
}
