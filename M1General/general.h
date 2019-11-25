#pragma once
#include <fstream>
#include <sstream>


namespace m1
{
	
	//PIXELDATA WITH LODEPNG LIB
	#include <lodepng.h>
	struct RGB
	{
		unsigned short get_r()
		{
			return r;
		}
		unsigned short get_g()
		{
			return g;
		}
		unsigned short get_b()
		{
			return b;
		}
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};


	RGB rgb(const std::vector<unsigned char>& pixeldata, unsigned int width, int x, int y)
	{
		static uint32_t index = 0;
		index = ((width * y) + x) * 4;
		static RGB rgb;
		rgb.r = pixeldata.at(index);
		rgb.g = pixeldata.at(index + 1);
		rgb.b = pixeldata.at(index + 2);

		return rgb;
	}

	inline bool is_about_flat(const long& number, const long& target, float max_diff_flat = 3)
	{
		if (number <= target + max_diff_flat && number >= target - max_diff_flat)
		{
			return true;
		}
		return false;
	}

	std::vector<m1::RGB> get_png_pixeldata(const char* filename, int width_png, int height_png)
	{
		static std::vector<unsigned char> pixeldata;
		pixeldata.clear();
		pixeldata.shrink_to_fit();

		static unsigned int w = 0;
		w = width_png;
		static unsigned int h = 0;
		h = height_png;
		
		if (lodepng::decode(pixeldata, w, h, filename))
		{
			std::cout << "Error decoding png" << std::endl;
		}

		static std::vector<m1::RGB> rgbdata;
		rgbdata.clear();
		rgbdata.shrink_to_fit();

		for (int i = 0; i < pixeldata.size(); i+=4)
		{
			rgbdata.push_back(m1::RGB{ 0,0,0 });
			rgbdata.back().r = pixeldata.at(i);
			rgbdata.back().g = pixeldata.at(i+1);
			rgbdata.back().b = pixeldata.at(i + 2);
		}

		return rgbdata;
	}

	bool rgbdata_is_equal(const std::vector<m1::RGB>& rgbdata1, const std::vector<m1::RGB>& rgbdata2, unsigned int max_value_difference)
	{
		if (rgbdata1.size() != rgbdata2.size())
		{
			return false;
		}

		for (int i = 0; i < rgbdata1.size(); ++i)
		{
			if ( is_about_flat(rgbdata1.at(i).r, rgbdata2.at(i).r, max_value_difference) == false )
			{
				return false;
			}
			if (is_about_flat(rgbdata1.at(i).g, rgbdata2.at(i).g, max_value_difference) == false)
			{
				return false;
			}
			if (is_about_flat(rgbdata1.at(i).b, rgbdata2.at(i).b, max_value_difference) == false)
			{
				return false;
			}
		}

		return true;
	}
	
	template <typename T>
	inline bool ReadConfig(const char* filename, const char* varName, T& out)
	{
		std::ifstream configIn(filename, std::ios::in);
		std::string inString = std::string();
		std::stringstream converter = std::stringstream();
		char cacheChar;
		bool foundVar = false;

		while (configIn.get(cacheChar))
		{

			if (cacheChar == ':')
			{
				if (inString == varName)
				{
					foundVar = true;
					inString.clear();
					inString.shrink_to_fit();
					continue;

				}

				else
				{
					std::cout << "False var: " << inString << std::endl;
					inString.clear();
					inString.shrink_to_fit();
					continue;
				}

			}

			else if (cacheChar == ';')
			{
				if (foundVar == true)
				{
					converter << inString;
					converter >> out;
					configIn.close();
					return true;
				}
				inString.clear();
				inString.shrink_to_fit();
				continue;
			}

			else if (cacheChar == ' ' || cacheChar == '\n')
			{
				continue;
			}

			inString.push_back(cacheChar);
		}

		configIn.close();
		return false;

	}

	inline void print_text_uppercase(const std::string& str)
	{
	static std::string op;
	op = str;

	for (int i = 0; i < op.size(); ++i)
	{
		if (op.at(i) <= 122 && op.at(i) >= 97)
		{
			op.at(i) = op.at(i) - 32;
		}
	}

	std::cout << op << std::endl;

	}
		
	inline std::string get_command_output(std::string& command)
	{
		std::string command_output;

		FILE* cmd_pipe = _popen(command.c_str(), "r");
		if (!cmd_pipe)
		{
			throw "popen failed";
		}

		char buffer[128];
		while (!feof(cmd_pipe))
		{
			if (fgets(buffer, 128, cmd_pipe) != nullptr)
			{
				command_output += buffer;
			}
		}

		_pclose(cmd_pipe);

		return command_output;
	}
	
}