#pragma once

#include "sani/types.hpp"
#include <functional>
#include <algorithm>
#include <cctype>
#include <locale>

namespace sani {

	namespace utils {

		/// Removes all whitespace character from the beginning of the given string.
		inline void trimStart(String& str) {
			str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		}
		/// Removes all whitespace character from the end of the given string.
		inline void trimEnd(String& str) {
			str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
		}
		/// Removes all whitespace character from beginning and the end of given string.
		inline void trim(String& str) {
			trimStart(str);
			trimEnd(str);
		}

		/// Removes all whitespace character from the beginning of the given string. Result
		/// string will be cleared if it is not clear.
		inline void trimStart(const String& str, String& result) {
			if (result.size() != 0) result.clear();

			result = String(str);

			trimStart(result);
		}
		/// Removes all whitespace character from the end of the given string. Result
		/// string will be cleared if it is not clear.
		inline void trimEnd(const String& str, String& result) {
			if (result.size() != 0) result.clear();

			result = String(str);

			trimEnd(result);
		}
		/// Removes all whitespace character from beginning and the end of given string. Result
		/// string will be cleared if it is not clear.
		inline void trim(const String& str, String& result) {
			if (result.size() != 0) result.clear();

			result = String(str);

			trim(result);
		}

		/// Returns the first index of given pattern.
		/// Returns -1 if match was not found.
		inline int indexOf(const String& str, const String& pattern) {
			const size_t index = str.find(pattern);

			if	(index == String::npos)		return -1;
			else							return static_cast<int>(index);
		}

		template <template <typename, typename> class Collection, class Item, class Allocator = std::allocator<Item> >
		inline void split(const String& str, const String& pattern, Collection<Item, Allocator>& results, const bool removeEmpty = false) {
			// From: http://www.cplusplus.com/forum/beginner/114790/

			size_t start = 0;
			size_t end = str.find_first_of(pattern);

			while (end <= String::npos) {
				String token = str.substr(start, end - start);

				if (!(token.empty() && removeEmpty)) results.push_back(token);

				if (end == String::npos) break;

				start = end + 1;
				end = str.find_first_of(pattern, start);
			}
		}

		/// Returns the index nth occurrence in the string.
		/// Returns string npos if nothing is matched.
		inline SizeType position(const String& str, const String& pattern, const uint32 nth)
		{
			const char* haystack = str.c_str();
			const char* needle = pattern.c_str();

			char *res = const_cast<char*>(haystack);
			
			for (uint32 i = 1; i <= nth; i++)
			{
				res = strstr(res, needle);

				if (!res)		   return String::npos;
				else if (i != nth) res = res++;
			}
			
			return res - haystack;
		}

		inline String repeat(const String& what, const uint32 count) {
			String out;

			for (uint32 i = 0; i < count; i++) out += what;

			return out;
		}

		inline uint32 count(const String& str, const char token) {
			uint32 matches = 0;

			for (const auto ch : str) if (ch == token) matches++;

			return matches;
		}
	}
}