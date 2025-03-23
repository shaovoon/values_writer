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
	class SyslogWriter : public ValuesWriterBase
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
				results[i].ConvTypeToStr(converted, token.type);
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
				results[i].ConvTypeToStr(converted, token.type);
				resultStr.replace(token.start + start_offset, token.size, converted);

				start_offset += ((int)(converted.size()) - (int)(token.size));
			}

			syslog(facility_priority, "%s", resultStr.c_str());
		}

	};

}
#endif
