#include "WebReader.h"

#include <cassert>
#include <sstream>
#include <cpprest/http_client.h>

#include "SplitedString.h"

using namespace FFXIV_RotationHelper_resources;

WebReader::WebReader(const std::wstring& url)
{
	web::http::client::http_client client = web::http::client::http_client(url);
	web::http::http_response response = client.request(web::http::methods::GET).get();
	std::string content = response.extract_utf8string().get();

	count = getLineCount(content);
	split = new SplitedString[count];

	std::stringstream sstream = std::stringstream(content);
	std::string token;
	int idx = 0;
	while (getline(sstream, token, '\n'))
	{
		size_t tokenLen = token.size();
		if (tokenLen > 0 && token[tokenLen - 1] == '\r')
		{
			tokenLen--;
		}

		assert(idx < count);
		split[idx].Initialize(token, (int)tokenLen);
		
		assert(idx == 0 || split[idx].GetCount() == split[idx - 1].GetCount());

		idx++;
	}
}

WebReader::~WebReader()
{
	if (split)
	{
		delete[] split;
	}
}

const SplitedString& WebReader::Get(const int idx) const
{
	assert(idx >= 0 && idx < count);

	return split[idx];
}

int WebReader::GetCount() const
{
	return count;
}

int WebReader::getLineCount(const std::string& str) const
{
	int count = 1;
	int size = (int)str.size() - 1;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == '\n')
		{
			count++;
		}
	}

	return count;
}
