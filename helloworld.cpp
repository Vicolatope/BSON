#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;
typedef std::vector<char> char_vec_t;
void print_binary_data(char_vec_t tmp, int size, int index);

void print_string_binary(char_vec_t tmp, int *current_idx)
{
	int32_t		*p_int32 = 0;
	int			idx = *current_idx;

	p_int32 = reinterpret_cast<int32_t *>(tmp.data() + idx);
	idx += 4;
	cout << "\"" << tmp.data() + idx << "\"";
	idx += strlen(tmp.data() + idx) + 1;
	*current_idx = idx;
}

void print_element_name(char_vec_t tmp, int *current_idx)
{
	cout << "\"" << tmp.data() + *current_idx  << "\"" << ":";
	*current_idx += strlen(tmp.data() + *current_idx) + 1;
}

void print_binary_data(char_vec_t tmp, int size, int index)
{
	int i = index;
	std::vector<double> doub_vec(tmp[i]);
	double			*my_doub;
	int32_t			*p_int32;
	int64_t			*p_int64;
	unsigned char	*my_uchar;
	int j;

	while (i - index < size)
	{
		if (i != index && tmp[i] != 0)
			cout << ",";
		switch (tmp[i])
		{
			case 0x00:
				return ;
			case 0x01:
				//double
				i++;
				print_element_name(tmp, &i);
				my_doub = reinterpret_cast<double*>( tmp.data() + i);
				printf("%.01f", *my_doub);
				i+= 8;
				break;
			case 0x02:
				i++;
				print_element_name(tmp, &i);
				print_string_binary(tmp, &i);
				break;
			case 0x03:
				i++;
				print_element_name(tmp, &i);
				p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
				cout << "document size is" << *p_int32 << endl;
				print_binary_data(tmp, *p_int32, i);
				i += *p_int32;
				p_int32 = 0;
				break;
			case 0x04:
				i++;
				print_element_name(tmp, &i);
				p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
				print_binary_data(tmp, *p_int32, i);
				i += *p_int32;
				p_int32 = 0;
				break;
			case 0x05:
				i++;
				print_element_name(tmp, &i);
				p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
				cout << "binary size is: " << *p_int32 << endl;
				i += 4;
				i += *p_int32;
				p_int32 = 0;
				break;
			case 0x06:
				i++;
				print_element_name(tmp, &i);
				cout << "undefined";
				break;
			case 0x07:
				i++;
				print_element_name(tmp, &i);
				cout << "{\"$oid\":\"";
				for (j=0;j< 12; j++)
				{
					my_uchar = reinterpret_cast<unsigned char *>(tmp.data() + i + j);
					printf("%02x", *my_uchar);
				}
				cout << "\"}";
				i += 12;
				break;
			case 0x08:
				i++;
				print_element_name(tmp, &i);
				if (tmp[i])
					cout << "true";
				else
					cout << "false";
				i++;
				break;
			case 0x09:
				i++;
				print_element_name(tmp, &i);
				p_int64 = reinterpret_cast<int64_t *>(tmp.data() + i);
				cout <<  *p_int64;
				p_int64 = 0;
				i += 8;
				break;
			case 0x0A:
				i++;
				print_element_name(tmp, &i);
				cout << "null";
				break;
			case 0x0B:
				//regex
				i++;
				print_element_name(tmp, &i);
				cout << "pattern is : " << tmp.data() + i << endl;
				i += strlen(tmp.data() + i) + 1;
				cout << "options are : " << tmp.data() + i << endl;
				i += strlen(tmp.data() + i) + 1;
				break;
			case 0x0C:
				i++;
				print_element_name(tmp, &i);
				p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
				cout << "string pointer size is : " << *p_int32 << endl;
				cout << tmp.data() + i << endl;
				i += *p_int32;
				for (j = 0; j< 12; j++)
				{
					my_uchar = reinterpret_cast<unsigned char *>(tmp.data() + i + j);
					printf("%02x", *my_uchar);
				}
				i += 12;
				break;
			case 0x0D:
				i++;
				print_element_name(tmp, &i);
				print_string_binary(tmp, &i);
				break;
			case 0x0E:
				i++;
				print_element_name(tmp, &i);
				print_string_binary(tmp, &i);
				break;
			case 0x10:
				i++;
				print_element_name(tmp, &i);
				p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
				cout << *p_int32;
				i += sizeof(int32_t);
				break;
			case 0x11:
				i++;
				print_element_name(tmp, &i);
				p_int64 = reinterpret_cast<int64_t *>(tmp.data() + i);
				cout << "Timestamp value is : " << *p_int64 << endl;
				i += sizeof(int64_t);
				break;
			case 0x12:
				i++;
				print_element_name(tmp, &i);
				break;
			case 0x13:
				i++;

			default:
				i++;
				break;
		}
	}
}

void get_current_document(char_vec_t tmp, int total_size)
{
	int	i = 0;
	int32_t		*p_int32;

	while (i < total_size)
	{
		p_int32 = reinterpret_cast<int32_t *>(tmp.data() + i);
		cout << "{";
		print_binary_data(tmp, *p_int32, i + sizeof(int32_t));
		cout << "}" << endl;
		i += *p_int32;// + sizeof(int32_t);
		p_int32 = 0;
	}
}

int main(int ac, char **av)
{
	fstream source;
	streampos size;

	if (ac == 2)
	{
		source.open(av[1], ios::in | ios::binary | ios::ate);
		if (source.is_open())
		{
			size = source.tellg();
			char_vec_t memblock(size);
			source.seekg(0, ios::beg);
			source.read(memblock.data(), size);
			source.close();
			get_current_document(memblock, size);
		}
		else
		{
			cout << "There was an error opening the file" << endl;
			return 1;
		}
	}
	else
	{
		cout << "usage: bsonreader [file]" << endl;
	}
	return 0;
}
