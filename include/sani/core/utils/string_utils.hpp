#pragma once

#include "sani/precompiled.hpp"
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
			// From: https://github.com/Babelz/EUS/blob/master/EUS/StringHelper.cpp
			// Optimize if needed.

			size_t start = 0;
			size_t end = str.find(pattern);

			while (end != String::npos) {
				const String sub = str.substr(start, end - start);

				start = end + pattern.size();
				end = str.find(pattern, start);

				if (sub.empty() && removeEmpty) continue;

				results.push_back(sub);
			}

			const String sub = str.substr(start, end - start);

			if (sub.empty() && removeEmpty) return;

			results.push_back(sub);
		}
	}
}