#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>

using namespace std;

struct Translation
{
	string english;
	vector<string> russians;

	Translation()
	{
		russians = vector<string>(0);
	}
};

char CharToLowerCase(char in)
{
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

string ToLowerCase(string str)
{
	string result = str;
	size_t size = str.length();
	for (size_t i = 0; i < size; i++)
	{
		result[i] = CharToLowerCase(str[i]);
	}
	return result;
}

vector<string> Split(const string& stringToSplit, const string& regexPattern)
{
	vector<string> result;

	const regex rgx(regexPattern);
	sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);

	for (sregex_token_iterator end; iter != end; ++iter)
	{
		result.push_back(iter->str());
	}

	return result;
}

Translation ParseTranslation(string str)
{
	Translation translation;
	int quotePosition = str.find('\"');
	int nextQuotePosition = str.find('\"', quotePosition + 1);
	string englishWord = str.substr(quotePosition + 1, nextQuotePosition - quotePosition - 1);
	cout << "English: " << nextQuotePosition << endl;
	translation.english = englishWord;

	quotePosition = str.find('\"', nextQuotePosition + 1);
	int lastQuotePosition = str.find('\"', quotePosition + 1);

	translation.russians = Split(str.substr(quotePosition + 1, lastQuotePosition - quotePosition - 1), " *, *");
	return translation;
}

Translation FindTranslation(const string& filePath, const string& english)
{
	const string lowerCaseEnglish = ToLowerCase(english);
	ifstream dictionary(filePath);
	string buffer;
	regex reg("^ *\"(\\w| |[à-ÿÀ-ß¨¸])+\" *: *\"((\\w| |[à-ÿÀ-ß¨¸])+,)*(\\w| |[à-ÿÀ-ß¨¸])+\" *$");
	dictionary.seekg(ios::beg);
	while (getline(dictionary, buffer))
	{
		if (regex_match(buffer, reg))
		{
			int quotePosition = buffer.find('\"');
			int lastQuotePosition = buffer.find('\"', quotePosition + 1);
			string englishWord = ToLowerCase(buffer.substr(quotePosition + 1, lastQuotePosition - quotePosition - 1));
			if (englishWord == lowerCaseEnglish)
			{
				return ParseTranslation(buffer);
			}
		}
	}
	return Translation();
}

void SaveChanges(const string& filePath, vector<Translation>& changes)
{
	ofstream dictionary(filePath, ios::app);
	for (auto i = changes.begin(); i != changes.end(); i++)
	{
		Translation translation = *i;
		dictionary << "\"" << translation.english << "\":\"";
		for (auto i = translation.russians.begin(); i != translation.russians.end(); i++)
		{
			string russian = *i;
			dictionary << russian;
			if (i != translation.russians.end() - 1) {
				dictionary << ", ";
			}
		}
		dictionary << "\"" << endl;
	}
}
