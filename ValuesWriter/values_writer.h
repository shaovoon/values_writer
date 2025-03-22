// The MIT License (MIT)
// Values Writer 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstdint>

#ifdef _MSC_VER
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

#ifdef __APPLE__
    #include <os/log.h>
#endif

namespace writer
{
	enum class TokenType
	{
		Hex,
		Matter
	};

	struct Token
	{
		size_t start;
		size_t size;
		TokenType type;
	};

	class DataType
	{
	public:
		DataType() = default;
		~DataType() {};

		union WUNIONPTR
		{
			int32_t i;
			uint32_t ui;
			int16_t si;
			uint16_t usi;
			int64_t i64;
			uint64_t ui64;
			float f;
			double d;
			std::string* ps;
			std::wstring* pws;
			const char* pc;
			char c;
			unsigned char uc;
			wchar_t wc;
		};

		enum WDTR_TYPE
		{
			DTR_INT,
			DTR_UINT,
			DTR_SHORT,
			DTR_USHORT,
			DTR_INT64,
			DTR_UINT64,
			DTR_FLOAT,
			DTR_DOUBLE,
			DTR_STR,
			DTR_WSTR,
			DTR_CHAR_PTR,
			DTR_CHAR,
			DTR_UCHAR,
			DTR_WCHAR
		};

		DataType(int32_t i) { m_ptr.i = i; m_type = DTR_INT; }

		DataType(uint32_t ui) { m_ptr.ui = ui; m_type = DTR_UINT; }

		DataType(int16_t si) { m_ptr.si = si; m_type = DTR_SHORT; }

		DataType(uint16_t usi) { m_ptr.usi = usi; m_type = DTR_USHORT; }

		DataType(int64_t i64) { m_ptr.i64 = i64; m_type = DTR_INT64; }

		DataType(uint64_t ui64) { m_ptr.ui64 = ui64; m_type = DTR_UINT64; }

		DataType(float f) { m_ptr.f = f; m_type = DTR_FLOAT; }

		DataType(double d) { m_ptr.d = d; m_type = DTR_DOUBLE; }

		DataType(std::string& s) { m_ptr.ps = &s; m_type = DTR_STR; }

		DataType(std::wstring& ws) { m_ptr.pws = &ws; m_type = DTR_WSTR; }

		DataType(const char* pc) { m_ptr.pc = pc; m_type = DTR_CHAR_PTR; }

		DataType(char c) { m_ptr.c = c; m_type = DTR_CHAR; }

		DataType(unsigned char uc) { m_ptr.uc = uc; m_type = DTR_UCHAR; }

		DataType(wchar_t wc) { m_ptr.wc = wc; m_type = DTR_WCHAR; }

		bool ConvTypeToStr(std::string& str, bool hex)
		{
			using namespace std;

			char buf[100];

			switch (m_type)
			{
			case DTR_INT:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%X", m_ptr.i);
				else
					snprintf(buf, sizeof(buf), "%d", m_ptr.i);
				str = buf;
				return true;
			}
			case DTR_UINT:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%X", m_ptr.ui);
				else
					snprintf(buf, sizeof(buf), "%u", m_ptr.ui);
				str = buf;
				return true;
			}
			case DTR_SHORT:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%X", m_ptr.si);
				else
					snprintf(buf, sizeof(buf), "%d", m_ptr.si);
				str = buf;
				return true;
			}
			case DTR_USHORT:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%X", m_ptr.usi);
				else
					snprintf(buf, sizeof(buf), "%u", m_ptr.usi);
				str = buf;
				return true;
			}
			case DTR_FLOAT:
			{
				snprintf(buf, sizeof(buf), "%f", m_ptr.f);
				str = buf;
				return true;
			}
			case DTR_DOUBLE:
			{
				snprintf(buf, sizeof(buf), "%lf", m_ptr.d);
				str = buf;
				return true;
			}
			case DTR_STR:
				str = *(m_ptr.ps);
				return true;
			case DTR_WSTR:
				for (wchar_t ch : *(m_ptr.pws))
					str += (char)ch;
				return true;
			case DTR_INT64:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%llX", m_ptr.i64);
				else
					snprintf(buf, sizeof(buf), "%lld", m_ptr.i64);
				str = buf;
				return true;
			}
			case DTR_UINT64:
			{
				if (hex)
					snprintf(buf, sizeof(buf), "%lluX", m_ptr.ui64);
				else
					snprintf(buf, sizeof(buf), "%llu", m_ptr.ui64);
				str = buf;
				return true;
			}
			case DTR_CHAR_PTR:
				str = m_ptr.pc;

				return true;

			case DTR_CHAR:
				str = "";
				str += m_ptr.c;

				return true;
			case DTR_UCHAR:
				str = "";
				str += (char)m_ptr.uc;

				return true;
			case DTR_WCHAR:
				str = "";
				str += (char)m_ptr.wc;

				return true;

			default:
				return false;
			}

			return false;
		}

		WDTR_TYPE m_type;

		WUNIONPTR m_ptr;
	};

	class ValuesWriterBase
	{
	public:
		static std::vector<Token> Find(const std::string& input, TokenType type)
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

		static std::vector<Token> TokenizeFmtString(const std::string& fmt)
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

		static void AddData(std::vector<DataType>& results)
		{
		}

		template<typename T, typename... Args>
		static void AddData(std::vector<DataType>& results, T& value, Args... args)
		{
			results.push_back({ value });
			AddData(results, args...);
		}
	};


	template <typename Derived>
	class ValuesWriter : public ValuesWriterBase
	{
	public:
		template<typename... Args>
		void WriteLine(const char* fmt, Args... args)
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
			for(size_t i=0; i<tokens.size(); ++i)
			{
				std::string converted;
				const Token& token = tokens[i];
				results[i].ConvTypeToStr(converted, token.type == TokenType::Hex);
				resultStr.replace(token.start + start_offset, token.size, converted);

				start_offset += ((int)(converted.size()) - (int)(token.size));
			}

			static_cast<Derived*>(this)->Print(resultStr, true);
		}

		template<typename... Args>
		void Write(const char* fmt, Args... args)
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

			static_cast<Derived*>(this)->Print(resultStr, false);
		}
	};

	class Console : public ValuesWriter<Console>
	{
	public:
		void Print(const std::string& str, bool newline)
		{
			if (newline)
			{
				printf("%s\n", str.c_str());
			}
			else
			{
				printf("%s", str.c_str());
			}
		}
	};

#ifdef _MSC_VER
	class Debug : public ValuesWriter<Debug>
	{
	public:
		void Print(const std::string& str, bool newline)
		{
			OutputDebugStringA(str.c_str());
		}
	};
#endif

#ifdef __APPLE__
	class Debug : public ValuesWriter<Debug>
	{
	public:
		void Print(const std::string& str, bool newline)
		{
			if (newline)
			{
				os_log(OS_LOG_DEFAULT, "%{public}s\n", str.c_str());
			}
			else
			{
				os_log(OS_LOG_DEFAULT, "%{public}s", str.c_str());
			}
		}
	};
#endif

	class FileWriter : public ValuesWriter<FileWriter>
	{
	public:
		FileWriter(const char* path) : FilePath(path)
		{
			File = fopen(FilePath.c_str(), "wt");
		}

		~FileWriter()
		{
			if (File)
			{
				fclose(File);
				File = nullptr;
			}
		}
		void Print(const std::string& str, bool newline)
		{
			if (File)
			{
				if (newline)
				{
					fprintf(File, "%s\n", str.c_str());
				}
				else
				{
					fprintf(File, "%s", str.c_str());
				}
			}
		}
	private:
		std::string FilePath;
		FILE* File = nullptr;
	};

}
