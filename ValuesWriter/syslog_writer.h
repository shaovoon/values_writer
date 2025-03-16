// The MIT License (MIT)
// Values Writer 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once
#include "values_writer.h"

#if !defined(_MSC_VER)

#include <syslog.h>

// https://stackoverflow.com/questions/8485333/syslog-command-in-c-code

namespace writer
{
	class SyslogWriter
	{
	public:
		SyslogWriter(const char* ident, int option, int facility)
		{
			openlog(ident, option, facility);
		}
		~SyslogWriter()
		{
			closelog();
		}

		template<typename... Args>
		void WriteLine(int facility_priority, const char* fmt, Args... args)
		{
			std::vector<Token> tokens = TokenizeFmtString(fmt);

			std::vector<DataType> results;

			AddData(results, args...);

			std::string resultStr = fmt;

			if (tokens.size() != results.size())
			{
				printf("tokens.size() != results.size() : (%zu != %zu)\n", tokens.size(), results.size());
				return;
			}

			int start_offset = 0;
			for (size_t i = 0; i < tokens.size(); ++i)
			{
				std::string converted;
				const Token& token = tokens[i];
				results[i].ConvTypeToStr(converted, token.type == TokenType::Hex);
				resultStr.replace(token.start + start_offset, token.size, converted);

				start_offset += ((int)(converted.size()) - (int)(token.size));
			}

			syslog(facility_priority, "%s\n", resultStr.c_str());
		}

		template<typename... Args>
		void Write(int facility_priority, const char* fmt, Args... args)
		{
			std::vector<Token> tokens = TokenizeFmtString(fmt);

			std::vector<DataType> results;

			AddData(results, args...);

			std::string resultStr = fmt;

			if (tokens.size() != results.size())
			{
				printf("tokens.size() != results.size() : (%zu != %zu)\n", tokens.size(), results.size());
				return;
			}

			int start_offset = 0;
			for (size_t i = 0; i < tokens.size(); ++i)
			{
				std::string converted;
				const Token& token = tokens[i];
				results[i].ConvTypeToStr(converted, token.type == TokenType::Hex);
				resultStr.replace(token.start + start_offset, token.size, converted);

				start_offset += ((int)(converted.size()) - (int)(token.size));
			}

			syslog(facility_priority, "%s", resultStr.c_str());
		}

	private:
		std::vector<Token> Find(const std::string& input, TokenType type)
		{
			std::vector<Token> vec;
			size_t find_size = 2;
			const char* find = "{}";

			if (type == TokenType::Hex)
			{
				find_size = 3;
				find = "{h}";
			}

			size_t pos = 0;
			pos = input.find(find);
			while (pos != std::string::npos)
			{
				vec.push_back({ pos, find_size, type });
				pos += find_size;
				pos = input.find(find, pos);
			}
			return vec;
		}

		std::vector<Token> TokenizeFmtString(const std::string& fmt)
		{
			std::vector<Token> vecMatter = Find(fmt, TokenType::Matter);
			std::vector<Token> vecHex = Find(fmt, TokenType::Hex);

			std::vector<Token> vec;
			for (auto& a : vecMatter)
			{
				vec.push_back(a);
			}
			for (auto& a : vecHex)
			{
				vec.push_back(a);
			}

			std::sort(vec.begin(), vec.end(), [](const Token& a, const Token& b)
				{ return a.start < b.start; });

			return vec;
		}

		void AddData(std::vector<DataType>& results)
		{
		}

		template<typename T, typename... Args>
		void AddData(std::vector<DataType>& results, T& value, Args... args)
		{
			results.push_back({ value });
			AddData(results, args...);
		}
	};

}
#endif
