#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <stack>
#include <algorithm>

using namespace std;

#define DEBUG 0

static string weekStr[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
static string monthStr[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
static int monthDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
static int monthDaysLeap[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

bool LeapYear(int Year, bool bNew) {
	if (bNew) {
		return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
	}
	return (Year % 4 == 0);
}

// days from 0000 January 01
int date2Days(int y, int m, int d, bool isNew) {
	--y;
	int days = y * 365 + y / 4;
	if (isNew) {
		days -= (y / 100);
		days += (y / 400);
	}
	if (m > 2 && LeapYear(y + 1, isNew)) {
		++days;
	}
	days += monthDays[m - 1] + d - 1;
	return days;
}

void days2Date(int & y, int & m, int & d, int days, bool isNew) {
	const int days400Y = 400 * 365 + 100 - 3;
	const int days100Y = 100 * 365 + 25 - 1;
	const int days4Y = 4 * 365 + 1;
	y = 0;
	if (isNew) {
		y = days / days400Y * 400;
		days %= days400Y;
		if (DEBUG) {
			cout << "400 y:" << y << " days:" << days << endl;
		}
		if (days == days100Y * 4) {
			y += 300;
			days -= days100Y * 3;
		} else {
			y += days / days100Y * 100;
			days %= days100Y;
		}
		if (DEBUG) {
			cout << "100 y:" << y << " days:" << days << endl;
		}

	}
	y += days / days4Y * 4;
	days %= days4Y;
	if (DEBUG) {
		cout << "4 y:" << y << " days:" << days << endl;
	}

	if (days == 365 * 4) {
		y += 3;
		days -= 365 * 3;
	} else {
		y += days / 365;
		days %= 365;
	}
	int *pMDays = (LeapYear(++y, isNew) ? monthDaysLeap : monthDays);
	for (m = 0; m < 12 && pMDays[m] <= days; ++m)
		;
	d = days - pMDays[m - 1] + 1;
}

int dow(int y, int m, int d, bool isNew) {
	static int mOffset[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	int cen = y / 100;
	int cenOffset;
	int yOffset;
	if (isNew) {
		cenOffset = (((cen / 4) + 1) * 4 - 1 - cen) * 2;
	} else {
		cenOffset = 7 - (cen + 3) % 7;
	}
	yOffset = (y - cen * 100) + (y - cen * 100) / 4;
	if (m < 3 && LeapYear(y, isNew)) {
		yOffset -= 1;
	}
	return (cenOffset + yOffset + mOffset[m - 1] + d % 7) % 7;
}

int main(int argc, char * argv[]) {
	int day, year, month, week;
	string sYear, sWeek, sMonth;
	bool isNew;
	while (true) {
		cin >> sWeek;
		if (sWeek == "#")
			break;
		cin >> day;
		cin >> sMonth;
		cin >> year;
		isNew = true;
		for (int i = 0; i < 7; i++) {
			if (weekStr[i] == sWeek) {
				week = i;
				break;
			}
		}
		for (int i = 0; i < 12; i++) {
			if (monthStr[i] == sMonth) {
				month = i + 1;
				break;
			}
		}
		if (week != dow(year, month, day, true)) {
			isNew = false;
		}
		int days = date2Days(year, month, day, isNew);

		if (isNew) {
			days += 2;
		} else {
			days -= 2;
		}
		//		if (DEBUG) {
		//			if (isNew)
		//				cout << "new2old days:" << days << endl;
		//			else
		//				cout << "old2new days:" << days << endl;
		//		}
		days2Date(year, month, day, days, !isNew);
		cout << sWeek << " ";
		cout << day << (isNew ? "* " : " ");
		cout << monthStr[month - 1] << " ";
		cout << year << endl;
	}
	return 0;
}

//static int aMDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
//static int aMDaysL[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
////根据指定的历法判定闰年。bNew为true代表新历法，fase代表旧历法
//bool LeapYear(int Year, bool bNew) {
//	if (bNew) {
//		//标准的闰年判断
//		return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
//	}
//	return (Year % 4 == 0);
//}
////将年月日换算为从元年1月1日(第0天)到这一天的天数
//int Date2Days(int Year, int Month, int Date, bool bNew) {
//	--Year; //年份定为以0年起始
//	//年份乘以365天，加上闰年数(总置闰天数)
//	//如果为新历法，要减去百年中不能被400整除的置闰天数
//	int Days = Year * 365 + Year / 4 + (bNew ? (Year / 400 - Year / 100) : 0);
//	//如果为闰年且月分大于2，要闰1天
//	Days += ((Month > 2) ? LeapYear(Year + 1, bNew) : 0);
//	//返回：年累计天数+月累计天数+日期-新旧历法起点对齐
//	return (Days + aMDays[Month - 1] + Date - 1 - (!bNew * 2));
//}
////主函数
//int main(void) {
//	//月分和星期的字符串表，用于处理输入和输出
//	const static string aDays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
//	const static string
//			aMonths[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
//	//400年的天数，100年的天数，4年的天数和1年的天数常量
//	const int nDays400Y = 400 * 365 + 100 - 3;
//	const int nDays100Y = 100 * 365 + 25 - 1;
//	const int nDays4Y = 4 * 365 + 1, nDays1Y = 365;
//	//循环处理每一个输出的日期
//	for (string str; cin >> str && str != "#";) {
//		int Day, Date, Month, Year;
//		//在字符串表中检索是周几
//		Day = find(&aDays[0], &aDays[7], str) - &aDays[0];
//		//读入年月日
//		cin >> Date >> str >> Year;
//		//在字符串表中检索是几月
//		Month = find(&aMonths[0], &aMonths[12], str) - &aMonths[0] + 1;
//		//将当前日期按旧历换算为天数
//		int nDays = Date2Days(Year, Month, Date, false);
//
//		bool bOld2New = true; //为真表示由旧历转新历
//		//判定算得的星期是否与输入的相符，若相符则为旧历纪年
//		if (Day == (nDays + 1) % 7) {
//			//			if (DEBUG) {
//			//				cout << "old2new days: " << nDays << endl;
//			//			}
//			//转新历时要先处理400年和100年的置闰
//			Year = nDays / nDays400Y * 400; //算出第几个400年
//			nDays %= nDays400Y;
//			if (DEBUG) {
//				cout << "400 Year:" << Year << " Days:" << nDays << endl;
//			}
//
//			//算出400年中的第几个百年
//			if (nDays == nDays100Y * 4) { //该400年的最后一天
//				Year += 300;
//				nDays -= nDays100Y * 3;
//			} else {
//				Year += nDays / nDays100Y * 100;
//				nDays %= nDays100Y; //取零头
//			}
//			if (DEBUG) {
//				cout << "100 Year:" << Year << " Days:" << nDays << endl;
//			}
//
//
//		} //否则为亲历纪年，重新计算天数，并加2与旧历对齐
//		else {
//			nDays = Date2Days(Year, Month, Date, true) + 2;
//			//			if (DEBUG) {
//			//				cout << "new2old days: " << nDays << endl;
//			//			}
//			Year = bOld2New = 0;
//		}
//		//算出百年中的第几个4年
//		Year += nDays / nDays4Y * 4;
//		nDays %= nDays4Y; //取零头
//		if (DEBUG) {
//			cout << "4 Year:" << Year << " Days:" << nDays << endl;
//		}
//		//算出4年中的第几年
//		if (nDays == nDays1Y * 4) { //年4年的最后一天
//			Year += 3;
//			nDays -= nDays1Y * 3;
//		} else {
//			Year += nDays / nDays1Y;
//			nDays %= nDays1Y; //取零头
//		}
//		//判定闰年，选取相应的各月累计天数表
//		int *pMDays = (LeapYear(++Year, bOld2New) ? aMDaysL : aMDays);
//		//按当年累计天数查找月份
//		for (Month = 0; Month < 12 && pMDays[Month] <= nDays; ++Month)
//			;
//		//计算当月日期
//		Date = nDays - pMDays[Month - 1] + 1;
//		//计算星期几
//		Day = (Date2Days(Year, Month, Date, bOld2New) + 1) % 7;
//		//按格式要求输出结果
//		cout << aDays[Day] << ' ' << Date << (bOld2New ? " " : "* ");
//		cout << aMonths[Month - 1] << ' ' << Year << endl;
//	}
//	return 0;
//}
