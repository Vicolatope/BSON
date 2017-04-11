#include <iostream>
#include <fstream>
#include "bson.hpp"

int main(int ac, char **av)
{
	std::streampos	size;

	if (ac == 2)
	{
		std::fstream		source(av[1], std::ios::in | std::ios::binary | std::ios::ate);
		// source.open(av[1], std::ios::in | std::ios::binary | std::ios::ate);
		if (source.is_open())
		{
			size = source.tellg();
			char_vec_t memblock(size);
			source.seekg(0, std::ios::beg);
			source.read(memblock.data(), size);
			source.close();
			BSON bson_parser(memblock, size);
			bson_parser.json_dump();
		}
		else
		{
			std::cerr << "There was an error opening the file" << std::endl;
			return 2;
		}
	}
	else
	{
		std::cerr << "usage: bsonreader [file]" << std::endl;
		return 1;
	}
	return 0;
}
