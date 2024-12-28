#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <ctime>
#include "clsString.h"
#include <iomanip>
#include "clsString.h"



using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;
public:

	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(string sDate) {

		vector<string>vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short DayOrder, short Year) {

		clsDate Date1;
		Date1 = DateFromDayOrder(DayOrder, Year);
		_Day = Date1._Day;
		_Month = Date1._Month;
		_Year = Date1._Year;

	}



	void setDay(short Day) {
		_Day = Day;
	}
	short getDay() {
		return _Day;
	}
	__declspec(property(get = getDay, put = setDay)) short Day;

	void setMonth(short Month) {
		_Month = Month;
	}
	short getMonth() {
		return _Month;
	}
	__declspec(property(get = getMonth, put = setMonth)) short Month;

	void setYear(short Year) {
		_Year = Year;
	}
	short getYear() {
		return _Year;
	}
	__declspec(property(get = getYear, put = setYear)) short Year;

	void Print() {
		cout << DateToString() << endl;
	}

	clsDate DateFromDayOrder(short DayOrder, short year) {

		clsDate Date;

		short RemainingDays = DayOrder;
		short MonthDays = 0;

		Date._Year = year;

		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(year, Date._Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);
		short Year, Month, Day;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static bool IsValideDate(clsDate Date) {

		if (Date._Month >= 1 && Date._Month <= 12)

			if (Date._Day >= 1 && Date._Day <= NumberOfDaysInMonth(Date._Year, Date._Month))
				return 1;
			else
				return 0;

		else
			return 0;

	}
	bool IsValideDate() {
		return IsValideDate(*this);
	}

	static string DateToString(clsDate Date) {

		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	string DateToString() {
		return DateToString(*this);
	}

	static bool IsLeapYear(short Year) {

		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate TempDate;

		TempDate._Year = Date1._Year;
		TempDate._Month = Date1._Month;
		TempDate._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;

		Date2._Year = TempDate._Year;
		Date2._Month = TempDate._Month;
		Date2._Day = TempDate._Day;

	}

	void DateAfterAddingDays(int DaysToAdd) {

		int RemainingDays = DaysToAdd + NumberOfTheDaysFromTheBeginningOfTheYear();
		_Month = 1;

		short MonthDays = 0;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Year, _Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}
	}

	static short NumberOfDaysInYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInYear() {
		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInYear(short Year) {
		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear() {
		return  NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short Year) {
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutesInYear() {
		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year) {
		return NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear() {
		return NumberOfSecondsInYear(_Year);
	}


	static short NumberOfDaysInMonth(short Year, short Month) {

		if (Month < 1 || Month > 12)
			return 0;

		short NumberOfDays[12] = { 31, 28, 31, 30, 31, 30,  31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];

	}
	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static short NumberOfHoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	short NumberOfHoursInMonth() {
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short Year, short Month) {
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMinutesInMonth() {
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month) {
		return NumberOfMinutesInMonth(Year, Month) * 60;
	}
	int NumberOfSecondsInMonth() {
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	int NumberOfTheDaysFromTheBeginningOfTheYear() {

		int TotalOfDays = 0;

		for (int i = 1; i < _Month; i++)
		{
			TotalOfDays += NumberOfDaysInMonth(_Year, i);
		}
		TotalOfDays += _Day;

		return TotalOfDays;
	}

	static void PrintYearResult(int Year) {

		cout << "Number of days      in Year [" << Year << "] is " << NumberOfDaysInYear(Year) << endl;
		cout << "Number of Hours     in Year [" << Year << "] is " << NumberOfHoursInYear(Year) << endl;
		cout << "Number of Minutes   in Year [" << Year << "] is " << NumberOfMinutesInYear(Year) << endl;
		cout << "Number of Seconds   in Year [" << Year << "] is " << NumberOfSecondsInYear(Year) << endl;

	}
	static void PrintMonthResult(int Year, short Month) {

		cout << "Number of days      in Month [" << Month << "] is " << NumberOfDaysInMonth(Year, Month) << endl;
		cout << "Number of Hours     in Month [" << Month << "] is " << NumberOfHoursInMonth(Year, Month) << endl;
		cout << "Number of Minutes   in Month [" << Month << "] is " << NumberOfMinutesInMonth(Year, Month) << endl;
		cout << "Number of Seconds   in Month [" << Month << "] is " << NumberOfSecondsInMonth(Year, Month) << endl;

	}

	static short DayOfWeekOrder(int year, short month, short day) {

		short a, y, m;

		a = (14 - month) / 12;
		y = year - a;
		m = month + 12 * a - 2;

		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string GetTheDayName(short DayOfWeekOrder) {

		string arrDayNames[] = { "Sunday", "Monday" , "Teusday", "Wednesday" , "Thursday", "Friday", "Saturday" };
		return arrDayNames[DayOfWeekOrder];
	}
	static string GetTheDayName(int year, short month, short day) {
		return GetTheDayName(DayOfWeekOrder(year, month, day));
	}
	string GetTheDayName() {
		return GetTheDayName(_Year, _Month, _Day);
	}

	static string MonthShortName(short Month) {
		string arrOfMonth[] = { "Jan", "Feb", "Mar", "Apr", "Ma", "Ju", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrOfMonth[Month - 1];
	}
	string MonthShortName() {
		return MonthShortName(_Month);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool InludeLastDay = false) {

		int Days = 0;
		short SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date2, Date2);
			SwapFlagValue = -1;
		}



		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			AddOneDay(Date1);

		}

		return InludeLastDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}
	int GetDifferenceInDays(clsDate Date2, bool InludeLastDay = false) {

		int Days = 0;
		short SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date2))
		{
			SwapDates(*this, Date2);
			SwapFlagValue = -1;
		}



		while (IsDate1BeforeDate2(Date2))
		{
			Days++;
			AddOneDay();

		}

		return InludeLastDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	static void PrintCalendar(int year, short month) {

		cout << endl;
		cout << "-----------------" << MonthShortName(month) << "-----------------" << endl << endl;
		cout << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;


		short dayOfWeek = DayOfWeekOrder(year, month, 1);
		short daysInMonth = NumberOfDaysInMonth(year, month);
		int i;
		for (i = 0; i < dayOfWeek; ++i) {
			cout << setw(5) << "";
		}



		for (int j = 1; j <= daysInMonth; ++j) {
			cout << setw(5) << j;

			if (++i == 7) {
				i = 0;
				cout << endl; // New line after Saturday
			}
		}

		cout << endl;
		cout << "-------------------------------------" << endl << endl;


	}
	void PrintCalendar() {
		return PrintCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(int year) {

		printf("\n-------------------------------------\n");
		printf("         Calendar - %d \n", year);
		printf("-------------------------------------\n");


		for (int i = 1; i <= 12; i++)
		{

			PrintCalendar(year, i);
			cout << endl;
		}


	}
	void PrintYearCalendar() {
		return PrintYearCalendar(_Year);
	}


	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? Date1._Month < Date2._Month ? true : Date1._Month == Date2._Month ? (Date1._Day < Date2._Day) : false : false);

	}
	bool IsDate1BeforeDate2(clsDate Date2) {

		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualsDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Year == Date2._Year) ? (Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false : false;

	}
	bool IsDate1EqualsDate2(clsDate Date2) {

		return (_Year == Date2._Year) ? (_Month == Date2._Month) ? (_Day == Date2._Day) : false : false;

	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualsDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2) {

		return (!IsDate1BeforeDate2(Date2) && !IsDate1EqualsDate2(Date2));
	}

	static bool IsLastDayInMonth(clsDate Date) {

		return (Date._Day == NumberOfDaysInMonth(Date._Year, Date._Month)) ? true : false;

	}
	bool IsLastDayInMonth() {

		return (_Day == NumberOfDaysInMonth(_Year, _Month)) ? true : false;

	}

	static bool IsLastMonthInYear(short month) {

		return (month == 12) ? true : false;
	}


	// Increasing Days/weeks/months/years...
	static clsDate AddOneDay(clsDate& Date) {

		if (IsLastDayInMonth(Date)) {
			Date._Day = 1;
			if (IsLastMonthInYear(Date._Month)) {
				Date._Month = 1;
				Date._Year++;
			}
			else {
				Date._Month++;
			}
		}
		else {
			Date._Day++;
		}
		return Date;
	}
	void AddOneDay() {

		AddOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate& Date) {

		for (int i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
	}
	void IncreaseDateByXDays(short Days) {
		IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {

		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek() {

		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeek(short Weeks, clsDate& Date) {

		for (int i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
	}
	void IncreaseDateByXWeek(short Weeks) {

		for (int i = 1; i <= Weeks; i++)
		{
			IncreaseDateByOneWeek(*this);
		}
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {

		if (IsLastMonthInYear(Date._Month))
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
		{
			Date._Month++;
		}

		short NumberOfDaysInTheCurrentMonth = NumberOfDaysInMonth(Date._Year, Date._Month);
		if (Date._Day > NumberOfDaysInTheCurrentMonth)
		{
			Date._Day = NumberOfDaysInTheCurrentMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(short Months, clsDate& Date) {
		for (int i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonth(short Months) {

		IncreaseDateByXMonth(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {

		Date._Year++;
		return Date;
	}
	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(short Years, clsDate& Date) {

		Date._Year += Years;
		return Date;
	}
	void IncreaseDateByXYear(short Years) {

		IncreaseDateByXYear(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {

		Date._Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade() {

		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecade(short Decades, clsDate& Date) {

		Date.Year += Decades * 10;
		return Date;
	}
	void IncreaseDateByXDecade(short Decades) {
		IncreaseDateByXDecade(Decades, *this);

	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {

		Date._Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {

		Date._Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}


	// Decreasing Days/weeks/months/years...
	static clsDate DecreaseDateByOneDay(clsDate& Date) {

		if (Date._Day == 1)
		{
			if (Date._Month == 1) {
				Date._Month = 12;
				Date._Year--;
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
			else
			{
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
		}
		else
		{
			Date._Day--;
		}
		return Date;
	}
	void DecreaseDateByOneDay() {
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate& Date) {

		for (int i = 1; i <= Days; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days) {
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {

		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(short Weeks, clsDate& Date) {

		for (int i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeek(short Weeks) {
		DecreaseDateByXWeek(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {

		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
		{
			Date._Month--;
		}

		short NumberOfDaysInTheCurrentMonth = NumberOfDaysInMonth(Date._Year, Date._Month);
		if (Date._Day > NumberOfDaysInTheCurrentMonth)
		{
			Date._Day = NumberOfDaysInTheCurrentMonth;
		}
		return Date;
	}
	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(short Months, clsDate& Date) {

		for (int i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonth(short Months) {
		DecreaseDateByXMonth(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {

		Date._Year--;
		return Date;
	}
	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYear(short Years, clsDate& Date) {

		Date._Year -= Years;
		return Date;
	}
	void DecreaseDateByXYear(short Years) {
		DecreaseDateByXYear(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {

		Date._Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecade(short Decades, clsDate& Date) {

		Date._Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecade(short Decades) {
		DecreaseDateByXDecade(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {

		Date._Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {

		Date._Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {

		return DayOfWeekOrder(Date._Year, Date._Month, Date._Day) == 6;
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate Date) {

		short DayIndex = DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
		return  (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekend() {
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date) {

		return !IsWeekend(Date);
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntilEndOfTheWeek(clsDate Date) {

		return 6 - DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
	}
	short DaysUntilEndOfTheWeek() {
		return DaysUntilEndOfTheWeek(*this);
	}

	static short DaysUntilEndOfTheMonth(clsDate Date) {

		clsDate EndOfMonthDate;
		EndOfMonthDate._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
		EndOfMonthDate._Month = Date._Month;
		EndOfMonthDate._Year = Date._Year;

		return GetDifferenceInDays(EndOfMonthDate, Date, true);
	}
	short DaysUntilEndOfTheMonth() {
		return DaysUntilEndOfTheMonth(*this);
	}

	static short DaysUntilEndOfTheYear(clsDate Date) {

		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date._Year;

		return GetDifferenceInDays(EndOfYearDate, Date, true);
	}
	short DaysUntilEndOfTheYear() {
		return DaysUntilEndOfTheYear(*this);
	}

	short CountVacationDays(clsDate DateTo) {

		short Days = 0;
		while (IsDate1BeforeDate2(DateTo)) {

			if (IsBusinessDay()) {
				Days++;
			}
			AddOneDay();
		}

		return Days;
	}
	void EndOfVacation(short VacationDays) {

		short WeekEndCounter = 0;

		/*in case the data  is weekend keep adding one day util you reach business day
		we get rid of all weekends before the first business day*/
		while (IsWeekend())
		{
			AddOneDay();
		}

		//here we increase the vacation dates to add all weekends to it.

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekend())
				WeekEndCounter++;

			AddOneDay();
		}

		//in case the return date is week end keep adding one day util you reach business day
		while (IsWeekend())
		{
			AddOneDay();
		}
	}


	//i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(DateFrom, DateTo);

	}
	//above method is eough , no need to have method for the object

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{

			if (IsWeekend(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}


	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDate1BeforeDate2(Date1, Date2)) {
			return enDateCompare::Before;
		}

		if (IsDate1EqualsDate2(Date1, Date2)) {
			return enDateCompare::Equal;
		}

		return enDateCompare::After;
	}
	enDateCompare CompareDates(clsDate Date2) {

		return CompareDates(*this, Date2);
	}


	static string GetCurrentTime() {

		string Time;

		int Year, Month, Day, Hour, Minute, Second;
		time_t t = time(0);
		tm* now = localtime(&t);

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		Time = to_string(Day) + "/";
		Time += to_string(Month) + "/";
		Time += to_string(Year) + " - ";
		Time += to_string(Hour) + ":";
		Time += to_string(Minute) + ":";
		Time += to_string(Second);

		return Time;
	}





};

