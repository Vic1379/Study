#include <iostream>
#include <sstream>
#include <string>

class Date {
 public:
	 int y, m, d;
	 Date(int year, int mounth, int day) {
		 y = year;
		 m = mounth;
		 d = day;
	 }
	 bool IsLeap() {
		 if (y % 4 == 0) {
			 if (y % 100 != 0) return true;
			 else if (y % 400 == 0) return true;
			 else
				 return false;
		 } else {
			 return false;
		 }
	 }
	 std::string ToString() {
		 std::string s = "";
		 std::stringstream ss;
		 for (int i = 0; i < 3; i++) {
			 if (i == 0) {
				 ss << d;
			 }
			 else if (i == 1) {
				 ss << m;
				 s += ".";
			 } else {
				 ss << y;
				 s += ".";
				 if (ss.str().size() < 4) {
					 for (int j = 0; j < (4 - ss.str().size()); j++)
						 s += "0";
				 }
			 }
			 if (ss.str().size() == 1 && i != 2) s += "0";
			 s += ss.str();
			 ss.str("");
		 }
		 return s;
	 }
	 Date DaysLater(int days) {
		 int yrs = days / 365;
		 for (int i = 0; i < yrs; i++) {
			 if ((m <= 2 and IsLeap()) || (i != 0 && IsLeap() && (d != 31 || m != 12))) {
				 d--;
				 if (d == 0) {
					 m--;
					 if (m == 3) {
						 d = 28;
					 }
					 else if (m == 1) {
						 y--;
						 m = 12;
						 d = 31;
					 }
					 else if ((m <= 7 && m % 2 == 1) || (m > 8 && m % 2 == 0)) {
						 d = 30;
					 }
					 else {
						 d = 31;
					 }
				 }
			 }
			 y++;
		 }
		 if (IsLeap() && yrs != 0 && m > 2) {
			 d--;
			 if (d == 0) {
				 m--;
				 if (m == 2) {
					 d = 28;
				 }
				 else if (m == 0) {
					 y--;
					 m = 12;
					 d = 31;
				 }
				 else if ((m <= 7 && m % 2 == 1) || (m > 8 && m % 2 == 0)) {
					 d = 31;
				 }
				 else {
					 d = 30;
				 }
			 }
		 }
		 for (int i = 0; i < (days % 365); i++) {
			 d++;
			 if ((IsLeap() && m == 2 && d == 30) || (!IsLeap() && m == 2 && d == 29)) {
				 d = 1;
				 m++;
			 } else if (d == 31 && ((m <= 7 && m % 2 == 0) || (m > 8 && m % 2 == 1)) || d == 32) {
				 d = 1;
				 m++;
				 if (m == 13) {
					 m = 1;
					 y++;
				 }
			 }
		 }
		 Date nwdt(y, m, d);
		 return nwdt;
	 }
	 int DaysLeft(Date date) {
		 int days = 0, ds = 0, i, k, j;
		 for (i = y; i < date.y; i++) {
			 if (IsLeap()) days += 366;
			 else
				 days += 365;
			 y++;
		 }
		 if (m > date.m) {
			 j = date.m;
			 k = m;
		 } else {
			 k = date.m;
			 j = m;
		 }
		 for (i = j; i < k; i++) {
			 m++;
			 if (i == 2 and IsLeap()) ds += 29;
			 else if (i == 2 and !IsLeap()) ds += 28;
			 else if ((i <= 7 && i % 2 == 1) || (i > 8 && i % 2 == 0) || i == 8) ds += 31;
			 else
				 ds += 30;
		 }
		 if (m > date.m)
			 ds = ds * (-1);
		 days += ds;
		 ds = 0;
		 if (d > date.d) {
			 j = date.d;
			 k = d;
		 }
		 else {
			 k = date.d;
			 j = d;
		 }
		 for (int i = j; i < k; i++)
			 ds += 1;
		 if (d > date.d)
			 ds = ds * (-1);
		 days += ds;
		 return days;
	 }
};
