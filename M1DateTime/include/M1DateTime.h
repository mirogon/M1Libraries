#include <iostream>
#include <ctime>
#include <algorithm>
#include <limits>

namespace m1
{
	enum class Month
	{
		NONE = 0,
		JANUARY = 1,
		FEBRUARY = 2,
		MARCH = 3,
		APRIL = 4,
		MAY = 5,
		JUNE = 6,
		JULY = 7,
		AUGUST = 8,
		SEPTEMBER = 9,
		OCTOBER = 10,
		NOVEMBER = 11,
		DECEMBER = 12
	};
	
	struct Duration
	{
		Duration()
		{
			years = 0;
			months = 0;
			days = 0;
			hours = 0;
			minutes = 0;
			seconds = 0;
		}
		uint16_t years;
		uint8_t	months; 
		uint8_t	days; 
		uint8_t	hours; 
		uint8_t minutes; 
		uint8_t seconds; 
	};
	class DateTime
	{
	public:

		uint8_t NumOfDays(Month m)
		{
			bool isLeapYear = false;
			if (yearSince1900 + 1900 % 4 == 0)
			{
				isLeapYear = true;
			}

			switch (m)
			{
				case Month::NONE: return 0; break;
				case Month::JANUARY: return 31; break;
				case Month::FEBRUARY: if (isLeapYear) { return 29;} else {return 28; } break;
				case Month::MARCH: return 31; break;
				case Month::APRIL: return 30; break;
				case Month::MAY: return 31; break;
				case Month::JUNE: return 30; break;
				case Month::JULY: return 31; break;
				case Month::AUGUST: return 31; break;
				case Month::SEPTEMBER: return 30; break;
				case Month::OCTOBER: return 31; break;
				case Month::NOVEMBER: return 30; break;
				case Month::DECEMBER: return 31; break;
			}
			return 0;
		}

		bool operator<(const DateTime& dt)
		{
			if (dt.yearSince1900 > yearSince1900)
			{
				return true;
			}
			else if (dt.yearSince1900 < yearSince1900)
			{
				return false;
			}

			if (dt.month > month)
			{
				return true;
			}
			else if (dt.month < month)
			{
				return false;
			}

			if (dt.day > day)
			{
				return true;
			}
			else if(dt.day < day)
			{
				return false;
			}

			if (dt.hour > hour)
			{
				return true;
			}
			else if (dt.hour < hour)
			{
				return false;
			}
			if (dt.minutes > minutes)
			{
				return true;
			}
			else if (dt.minutes < minutes)
			{
				return false;
			}

			if (dt.seconds > seconds)
			{
				return true;
			}
			else if (dt.seconds < seconds)
			{
				return false;
			}

			return false;
		}

		bool operator>(const DateTime& dt)
		{
			if (operator<(dt))
			{
				return false;
			}
			return true;
		}

		DateTime operator+(const Duration& d)
		{
			DateTime r = *this;
			
			//Handle seconds
			long sumSec = long(r.seconds + d.seconds);
			long addMin = sumSec / 60;
			sumSec -= sumSec % 60;
			r.seconds = sumSec;

			//Handle minutes
			long sumMin = r.minutes + addMin + d.minutes;
			long addHours = sumMin / 60;
			sumMin -= sumMin % 60;
			r.minutes = sumMin;

			//Handle hours
			long sumHours = r.hour + addHours + d.hours;
			long addDays = sumHours / 24;
			sumHours = sumHours % 24;
			r.hour = sumHours;

			//Handle days
			long sumDays = r.day + addDays + d.days;
			//long addMonths = sumDays / NumOfDays(Month(r.month));


			/*r.yearSince1900 = std::clamp<int>(int(r.yearSince1900 + d.years), std::numeric_limits<decltype(r.yearSince1900)>::min(), std::numeric_limits<decltype(r.yearSince1900)>::max());
			r.month = std::clamp<int>(int(r.month + d.months), std::numeric_limits<decltype(r.month)>::min(), std::numeric_limits<decltype(r.month)>::max());
			r.day = std::clamp<int>(int(r.day + d.days), std::numeric_limits<decltype(r.day)>::min(), std::numeric_limits<decltype(r.day)>::max());
			r.hour = std::clamp<int>(int(r.hour + d.hours), std::numeric_limits<decltype(r.hour)>::min(), std::numeric_limits<decltype(r.hour)>::max());
			r.minutes = std::clamp<int>(int(r.minutes + d.minutes), std::numeric_limits<decltype(r.minutes)>::min(), std::numeric_limits<decltype(r.minutes)>::max());
			r.seconds = std::clamp<int>(int(r.seconds + d.seconds), std::numeric_limits<decltype(r.seconds)>::min(), std::numeric_limits<decltype(r.seconds)>::max());
			*/
			return r;
		}
		DateTime operator-(const Duration& d)
		{
			DateTime r = *this;
			r.yearSince1900 = std::clamp<int>(int(r.yearSince1900 - d.years), std::numeric_limits<decltype(r.yearSince1900)>::min(), std::numeric_limits<decltype(r.yearSince1900)>::max());
			r.month = std::clamp<int>(int(r.month - d.months), std::numeric_limits<decltype(r.month)>::min(), std::numeric_limits<decltype(r.month)>::max());
			r.day = std::clamp<int>(int(r.day - d.days), std::numeric_limits<decltype(r.day)>::min(), std::numeric_limits<decltype(r.day)>::max());
			r.hour = std::clamp<int>(int(r.hour - d.hours), std::numeric_limits<decltype(r.hour)>::min(), std::numeric_limits<decltype(r.hour)>::max());
			r.minutes = std::clamp<int>(int(r.minutes - d.minutes), std::numeric_limits<decltype(r.minutes)>::min(), std::numeric_limits<decltype(r.minutes)>::max());
			r.seconds = std::clamp<int>(int(r.seconds - d.seconds), std::numeric_limits<decltype(r.seconds)>::min(), std::numeric_limits<decltype(r.seconds)>::max());
			return r;
		}
		DateTime()
		{
			yearSince1900 = 0;
			month = 0;
			day = 0;
			hour = 0;
			minutes = 0;
			seconds = 0;
		}
		DateTime(uint16_t pYear, uint8_t pMonth, uint8_t pDay, uint8_t pHour, uint8_t pSeconds)
		{
			SetYear(pYear);
			SetMonth(pMonth);
			SetDay(pDay);
			SetHour(pHour);
			SetSeconds(pSeconds);
		}

		void SetToNow()
		{
			time_t time = std::time(nullptr);
			tm tmtime = *std::localtime(&time);

			yearSince1900 = tmtime.tm_year;
			month = tmtime.tm_mon;
			day = tmtime.tm_mday;
			hour = tmtime.tm_hour;
			minutes = tmtime.tm_min;
			seconds = tmtime.tm_sec;
		}

		void SetYear(uint16_t pYear)
		{
			yearSince1900 = pYear - 1900;
		}

		void SetMonth(uint8_t pMonth)
		{
			month = pMonth - 1;
		}
		void SetMonth(Month pMonth)
		{
			if (pMonth == Month::NONE)
			{
				month = 0;
				return;
			}

			month = int(pMonth) - 1;
		}
		void SetDay(uint8_t pDay)
		{
			day = pDay;
		}
		void SetHour(uint8_t pHour)
		{
			hour = pHour;
		}
		void SetMinutes(uint8_t pMinutes)
		{
			minutes = pMinutes;
		}
		void SetSeconds(uint8_t pSeconds)
		{
			seconds = pSeconds;
		}

		int GetYear()
		{
			return yearSince1900 + 1900;
		}
		int GetMonth()
		{
			return month + 1;
		}
		int GetDay()
		{
			return day;
		}
		int GetHour()
		{
			return hour;
		}
		int GetMinutes()
		{
			return minutes;
		}
		int GetSeconds()
		{
			return seconds;
		}
		std::string GetTime()
		{
			static std::string amOrPm;
			amOrPm = "am";
			int hour_ = hour;
			if (hour > 12)
			{
				amOrPm = "pm";
				hour_ -= 12;
			}
			static std::string sSeconds;
			sSeconds = "";
			if (seconds < 10)
			{
				sSeconds = "0";
			}
			sSeconds.append(std::to_string(seconds));
			return std::to_string(hour_) + ":" + std::to_string(minutes) + ":" + sSeconds +  amOrPm;
		}

		void PrintDate()
		{
			std::cout << GetMonth() << "/" << GetDay() << "/" << GetYear() << "/" << GetTime() << std::endl;
		}

	private:

		uint16_t yearSince1900;
		uint8_t	month; // 0-11
		uint8_t	day; // 1-31
		uint8_t	hour; // 0-23
		uint8_t minutes; // 0-59
		uint8_t seconds; //0-59
	};
}