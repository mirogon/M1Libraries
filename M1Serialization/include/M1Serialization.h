#pragma once
#include <fstream>
#include <vector>
#include <cstring>

namespace m1
{
	typedef uint8_t byte;

	template<class T>
	//Returned pointer has to be deleted!
	char* to_char_pointer(T data)
	{
		char* c = new char[sizeof(T)];
		memcpy(c, &data, sizeof(T));
		return c;
	}

	class raw_serializer
	{
	public:

		raw_serializer() = delete;
		raw_serializer(const std::string& path, bool trunc = false, bool append = true)
		{

			m_saved_path = path;

			if(append == true && trunc == true)
			{
				m_fstream.open(path.c_str(), std::ios::trunc | std::ios::app | std::ios::in | std::ios::out | std::ios::binary);
			}
			else if(trunc == true)
			{
				m_fstream.open(path.c_str(), std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
			}

			else if(append == true)
			{
				m_fstream.open(path.c_str(), std::ios::app | std::ios::in | std::ios::out | std::ios::binary);
			}

			else if(append == false && trunc == false)
			{
				m_fstream.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
			}

			if( !m_fstream.is_open() )	
			{
				std::cout << "Could not open fstream with path: " << path << std::endl;
			}
			
		}
		
		~raw_serializer()
		{
			m_fstream.close();
		}

		template<class T>
		void serialize_out(T data, bool use_custom_size = false, unsigned short size = 0)
		{	
			if(use_custom_size == false)
			{
				size = sizeof(T);
			}
		
			char* cp = to_char_pointer(data);

			m_fstream.write(cp, size);
			m_fstream.flush();

			delete[] cp;
			cp = nullptr;
		}
		template<class T>
		void serialize_in(T& data, bool use_custom_size = false, unsigned short size = 0)
		{
			if(use_custom_size == false)
			{
				size = sizeof(T);
			}

			char* cache = new char[size];
			
			m_fstream.read(cache, size);

			memcpy(&data, cache, size);
			
			delete[] cache;
			cache = nullptr;
		}

		void set_input_position(std::streampos pos)
		{
			m_fstream.seekg(pos);
		}

		void set_output_position(std::streampos pos)
		{
			m_fstream.seekp(pos);
		}

		void set_path(std::string& path)
		{
			m_saved_path = path;
		}
		void close()
		{
			if (m_fstream.is_open())
			{
				m_fstream.close();
			}
		}

	private:
		//fstream to perform the in and output
		std::fstream m_fstream;

		//currently saved path used for in and output operations
		std::string m_saved_path;

	};


	//class ObjectSerializer
	//{
	//public:

	//	ObjectSerializer() = delete;
	//	/**
	//	* @param path the serialization path
	//	* @param trunc wheter to trunc the current data in the file or not
	//	* @param append wheter to append the output in the file or not
	//	* @param binary wheter to make binary or non binary output
	//	*/
	//	ObjectSerializer(const std::string& path, bool trunc = false, bool append = true, bool binary = true)
	//	{
	//		savedPath = path;

	//		if (trunc)
	//		{
	//			flags |= std::ios::trunc;
	//		}
	//		if (append)
	//		{
	//			flags |= std::ios::app;
	//		}
	//		if (binary)
	//		{
	//			flags |= std::ios::binary;
	//		}

	//		flags |= std::ios::in;
	//		flags |= std::ios::out;

	//		serializeStream = std::fstream(path.c_str(), flags);
	//	}

	//	~ObjectSerializer()
	//	{
	//		if (serializeStream.is_open())
	//		{
	//			serializeStream.close();
	//		}
	//	}

	//	//Single object serialization
	//	template <class T>
	//	bool SerializeOut(T* data)
	//	{
	//		if (!data)
	//		{
	//			return false;
	//		}

	//		serializeStream.write(reinterpret_cast<char*>(data), sizeof(T));
	//		serializeStream.flush();

	//		return true;
	//	}
	//	template <class T>
	//	bool SerializeIn(T* data)
	//	{
	//		if (!data)
	//		{
	//			return false;
	//		}

	//		static char* cache = new char[sizeof(T)];

	//		serializeStream.sync();
	//		serializeStream.seekg(0);
	//		serializeStream.read(cache, sizeof(T));

	//		memcpy(data, cache, sizeof(T));

	//		return true;
	//	}

	//	//Multiple object serialization
	//	template <class T>
	//	bool SerializeOut(std::vector<T>& data)
	//	{
	//		if (data.size() <= 0)
	//		{
	//			return false;
	//		}

	//		for (int i = 0; i < data.size(); ++i)
	//		{
	//			serializeStream.write(reinterpret_cast<char*>( &(data.at(i)) ), sizeof(T));
	//			serializeStream.flush();
	//		}

	//		return true;
	//	}
	//	template <class T>
	//	bool serializein(std::vector<t>& data, unsigned short numobjects)
	//	{
	//		if ( numobjects <= 0)
	//		{
	//			return false;
	//		}

	//		static char* cache = new char[sizeof(T)];
	//		static T cacheT;

	//		serializeStream.sync();
	//		serializeStream.seekg(0);

	//		while (serializeStream.good() && numObjects > 0)
	//		{
	//			serializeStream.read(cache, sizeof(T));
	//			memcpy(&cacheT, cache, sizeof(T));

	//			data.push_back(cacheT);
	//			--numObjects;
	//		}

	//		return true;
	//	}

	//	/**
	//	* @param path the serialization path
	//	* @param trunc wheter to trunc the current data in the file or not
	//	* @param append wheter to append the output in the file or not
	//	* @param binary wheter to make binary or non binary output
	//	*/
	//	void SetSettings(bool trunc = false, bool append = true, bool binary = true)
	//	{
	//		flags = std::ios_base::openmode();
	//		if (trunc)
	//		{
	//			flags |= std::ios::trunc;
	//		}
	//		if (append)
	//		{
	//			flags |= std::ios::app;
	//		}
	//		if (binary)
	//		{
	//			flags |= std::ios::binary;
	//		}

	//		flags |= std::ios::in;
	//		flags |= std::ios::out;

	//		//set the flags in the fstream
	//		serializeStream.flags(flags);

	//	}
	//	void SetPath(std::string& path)
	//	{
	//		savedPath = path;
	//	}
	//	void Close()
	//	{
	//		if (serializeStream.is_open())
	//		{
	//			serializeStream.close();
	//		}
	//	}

	//private:
	//	//fstream to perform the in and output
	//	std::fstream serializeStream;

	//	//currently saved path used for in and output operations
	//	std::string savedPath;

	//	//flags used in the fstream
	//	std::ios_base::openmode flags;
	//};

}

