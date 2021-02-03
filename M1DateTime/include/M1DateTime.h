namespace m1
{
	enum class Month
	{
		NONE = 0,
		January = 1,
		February = 2,
		March = 3,
		April = 4,
		May = 5,
		June = 6,
		July = 7,
		August = 8,
		September = 9,
		October = 10,
		November = 11,
		December = 12

	};
	class DateTime
	{
	public:

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