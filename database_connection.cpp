#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdlib>
#include <mysql.h>
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
	// 1. READ POST DATA
	string post_data = "";
	char* len_str = getenv("CONTENT_LENGTH");
	int len = 0;
	
	if (len_str != NULL) {
		len = atoi(len_str);
		if (len > 0) {
			char* buffer = new char[len + 1];
			cin.read(buffer, len);
			buffer[len] = '\0';
			post_data = buffer;
			delete[] buffer;
		}
	}
	
	string query_string = "";
	if (getenv("QUERY_STRING") != NULL) {
		query_string = getenv("QUERY_STRING");
	}
	
	string action_post = get_value(post_data, "action");
	string action_qs = get_value(query_string, "action");
	string action = !action_post.empty() ? action_post : action_qs;
	
	// 2. DATABASE CONNECTION
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "", "dostify_db", 3306, NULL, 0);
	
	if (!conn) {
		cout << "Content-type:text/html\r\n\r\n";
		cout << "<h2 style='color:red;'>Database Connection Error</h2>";
		return 0;
	}
