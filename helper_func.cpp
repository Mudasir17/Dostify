#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdlib>
#include <mysql.h>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

/* ================= HELPER FUNCTIONS ================= */

string urlEncode(const string& value) {
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex << uppercase;
	
	for (unsigned char uc : value) {
		char c = static_cast<char>(uc);
		if (isalnum(uc) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
		}
		else if (c == ' ') {
			escaped << "%20";
		}
		else {
			escaped << '%' << setw(2) << int(uc);
		}
	}
	return escaped.str();
}

string urlDecode(const string& s) {
	string out;
	out.reserve(s.size());
	
	for (size_t i = 0; i < s.size(); ++i) {
		char c = s[i];
		if (c == '%' && i + 2 < s.size()
			&& isxdigit(static_cast<unsigned char>(s[i + 1]))
			&& isxdigit(static_cast<unsigned char>(s[i + 2]))) {
			
			auto hexVal = [](char ch) -> int {
				if (ch >= '0' && ch <= '9') return ch - '0';
				if (ch >= 'a' && ch <= 'f') return 10 + (ch - 'a');
				if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
				return 0;
			};
			
			int v = (hexVal(s[i + 1]) << 4) | hexVal(s[i + 2]);
			out.push_back(static_cast<char>(v));
			i += 2;
		}
		else if (c == '+') {
			out.push_back(' ');
		}
		else {
			out.push_back(c);
		}
	}
	return out;
}

string get_value(string data, string key) {
	string key_pattern = key + "=";
	size_t pos = data.find(key_pattern);
	if (pos == string::npos) return "";
	
	pos += key_pattern.length();
	size_t end_pos = data.find("&", pos);
	
	string value;
	if (end_pos == string::npos) value = data.substr(pos);
	else value = data.substr(pos, end_pos - pos);
	
	return urlDecode(value);
} 