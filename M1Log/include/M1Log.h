#pragma once
#include <fstream>
#include <string>

namespace m1
{
	class M1Log
	{
	public:

		M1Log(std::string filename, bool active = true)
		{
			m_active = active;
			m_stream.open(filename.c_str(), std::ios::trunc | std::ios::out);
		}

		~M1Log()
		{
			m_stream.close();
		}

		void set_active(bool set)
		{
			m_active = set;
		}

		void log(std::string log_line)
		{
			if (!m_active)
			{
				return;
			}

			const char* text = log_line.c_str();

			m_stream.write(text, strlen(text));
			m_stream.flush();
		}

	private:

		std::fstream m_stream;
		bool m_active;

	};
}