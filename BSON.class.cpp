#include "BSON.class.hpp"
#include <iostream>
#include <fstream>

void BSON::handle_double(char_vec_t bson_data, int& current_index) {
	double *p_double;

	std::cout << bson_data.data() + current_index << std::endl;
	current_index += strlen(bson_data.data() + current_index) + 1;
	p_double = reinterpret_cast<double *>(bson_data.data() + current_index);

	BSON_element new_elem(p_double, bson_data.data() - strlen(bson_data.data() + current_index) + 1, 8, BSON_DOUBLE_T);
	current_index += sizeof(double);
	std::cout << *p_double << std::endl;

}

void BSON::handle_object_id(char_vec_t bson_data, int& current_index) {
	unsigned char	object_id[12];
	int		i;

	std::cout << bson_data.data() + current_index << std::endl;
	current_index += strlen(bson_data.data() + current_index) + 1;
	for (i = 0; i < 12; i++) {
		object_id[i] = bson_data[current_index + i];
		printf("%02x", object_id[i]);
	}
	current_index += i;
	std::cout << std::endl;
}

void BSON::element_dispatcher(char_vec_t bson_data, int32_t element_size, int current_index) {
	int &i = current_index;
	while (i - current_index < element_size) {
		switch (bson_data[i]) {
			case 0x00:
				return;
			case BSON_DOUBLE_T:
				i++;
				this->handle_double(bson_data, i);
				break;
			// case BSON_STRING_T:
			// 	i++;
			// 	this->handle_string(bson_data, i);
			// 	break;
			// case BSON_DOC_T:
			// 	i++;
			// 	this->handle_embedded_document(bson_data, i);
			// 	break;
			// case BSON_ARRAY_T:
			// 	i++;
			// 	this->handle_array(bson_data, i);
			// 	break;
			// case BSON_BINARY_T:
			// 	i++;
			// 	this->handle_binary_data(bson_data, i);
			// 	break;
			// case BSON_UNDEFINED_T:
			// 	i++;
			// 	this->handle_undefined(bson_data, i);
			// 	break;
			case BSON_OID_T:
				i++;
				this->handle_object_id(bson_data, i);
				break;
			// case BSON_BOOL_T:
			// 	i++;
			// 	this->handle_boolean(bson_data, i);
			// 	break;
			// case BSON_UTC_DATE_T:
			// 	i++;
			// 	this->handle_UTC_datetime(bson_data, i);
			// 	break;
			// case BSON_NULL_T:
			// 	i++;
			// 	this->handle_null_value(bson_data, i);
			// 	break;
			// case BSON_REGEX_T:
			// 	i++;
			// 	this->handle_regular_expression(bson_data, i);
			// 	break;
			// case BSON_DB_POINT_T:
			// 	i++;
			// 	this->handle_db_pointer(bson_data, i);
			// 	break;
			// case BSON_JS_CODE_T:
			// 	i++;
			// 	this->handle_javascript_code(bson_data, i);;
			// 	break;
			// case BSON_SYMBOL_T:
			// 	i++:
			// 	this->handle_symbol(bson_data, i);
			// 	break;
			// case BSON_JS_W_S_T:
			// 	i++;
			// 	this->handle_javascript_code_w_scope(bson_data, i);
			// 	break;
			// case BSON_INT32_T:
			// 	i++;
			// 	this->handle_int32(bson_data, i);
			// 	break;
			// case BSON_TIME_T:
			// 	i++;
			// 	this->handle_timestamp(bson_data, i);
			// 	break;
			// case BSON_INT64_T:
			// 	i++;
			// 	this->handle_int64(bson_data, i);
			// 	break;
			// case BSON_DEC128_T:
			// 	i++;
			// 	this->handle_decimal128(bson_data, i);
			// 	break;
			// case BSON_MIN_K_T:
			// 	i++;
			// 	this->handle_min_key(bson_data, i);
			// 	break;
			// case BSON_MAX_K_T:
			// 	i++;
			// 	this->handle_max_key(bson_data, i);
			// 	break;
			default:
				i++;
				break;

		}
	}
}


BSON::BSON(char_vec_t bson_data, int total_size) {
	int i = 0;
	int32_t		*p_elem_size;

	while (i < total_size) {
		p_elem_size = reinterpret_cast<int32_t *>(bson_data.data() + i);
		this->element_dispatcher(bson_data, *p_elem_size, i + sizeof(int32_t));
		i += *p_elem_size;
		p_elem_size = NULL;
	}
}

BSON::~BSON() {
	std::cout << "bye bye";
}

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
		}
		else
		{
			std::cout << "There was an error opening the file" << std::endl;
			return 2;
		}
	}
	else
	{
		std::cout << "usage: bsonreader [file]" << std::endl;
		return 1;
	}
	return 0;
}
