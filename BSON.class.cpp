#include "BSON.class.hpp"
#include <iostream>
#include <fstream>

bs_element_t *BSON::handle_double(char_vec_t bson_data, int& current_index) {
	double *p_double;
	bs_element_t	*new_element;
	char			*p_name;

	std::cout << bson_data.data() + current_index << std::endl;
	p_name = bson_data.data() + current_index;
	current_index += strlen(bson_data.data() + current_index) + 1;
	p_double = reinterpret_cast<double *>(bson_data.data() + current_index);

	new_element = new BSON_element(p_double, p_name, sizeof(double), BSON_DOUBLE_T);
	current_index += sizeof(double);
	std::cout << *p_double << std::endl;
	return new_element;
}

bs_element_t *BSON::handle_object_id(char_vec_t bson_data, int& current_index) {
	unsigned char	object_id[12];
	bs_element_t	*new_element;
	char			*p_name;
	int		i;

	std::cout << bson_data.data() + current_index << std::endl;
	p_name = bson_data.data() + current_index;
	current_index += strlen(bson_data.data() + current_index) + 1;
	for (i = 0; i < 12; i++) {
		object_id[i] = bson_data[current_index + i];
		printf("%02x", object_id[i]);
	}
	new_element = new BSON_element(&object_id[0], p_name, 12, BSON_OID_T);
	current_index += i;
	std::cout << std::endl;
	return new_element;
}


void BSON::element_dispatcher(char_vec_t bson_data, int32_t doc_size, int current_index) {
	bs_document_t *new_document = this->new_document();
	int &i = current_index;
	while (i - current_index < doc_size) {
		switch (bson_data[i]) {
			case 0x00:
				this->add_document_to_list(new_document);
				return;
			case BSON_DOUBLE_T:
				i++;
				this->add_element_to_list(&new_document->element_list, this->new_element_list_item(this->handle_double(bson_data, i)));
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
				this->add_element_to_list(&new_document->element_list, this->new_element_list_item(this->handle_object_id(bson_data, i)));
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
	int32_t		*p_doc_size;

	while (i < total_size) {
		p_doc_size = reinterpret_cast<int32_t *>(bson_data.data() + i);
		this->element_dispatcher(bson_data, *p_doc_size, i + sizeof(int32_t));
		i += *p_doc_size;
		p_doc_size = NULL;
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

/*
***	Fonctions propres a la liste de document : document_list, attribut de chaque bson,
***	ou sont stockes les documents trouvés sur le buffer
*/

bs_document_t *BSON::new_document(void) {
	bs_document_t	*new_document;

	new_document = new bs_document_t;
	new_document->element_list = NULL;
	new_document->next_d = NULL;
	return new_document;
}


void BSON::add_document_to_list(bs_document_t *new_document) {
	bs_document_t	*tmp_document;

	if (this->document_list) {
		tmp_document = this->document_list;
		while (tmp_document->next_d) {
			tmp_document = tmp_document->next_d;
		}
		if (tmp_document && !tmp_document->next_d) {
			tmp_document->next_d = new_document;
		} else {
			std::cerr << "There was a problem adding new doc to the list" << '\n';
			return ;
		}
	} else {
		this->document_list = new_document;
	}
}

/*
***	Methodes propres a l'initialisation et la manipulation de
***	la liste d'element contenue dans chaque document.
*/

bs_list_elem_t	*BSON::new_element_list_item(bs_element_t *element) {
	bs_list_elem_t *new_list_item;

	new_list_item = new bs_list_elem_t;
	new_list_item->next_e = NULL;
	new_list_item->element = element;
	return new_list_item;
}

void BSON::add_element_to_list(bs_list_elem_t **begin_list, bs_list_elem_t *new_elem) {
	bs_list_elem_t	*tmp_element;

	if (*begin_list == NULL) {
		*begin_list = new_elem;
	} else {
		tmp_element = *begin_list;
		while (tmp_element && tmp_element->next_e) {
			tmp_element = tmp_element->next_e;
		}
		if (tmp_element && !tmp_element->next_e) {
			tmp_element->next_e = new_elem;
		}
	}
}

/*
*** return the json from the bson taken at initilization
*/

void BSON::json_dump(void) {
	bs_document_t	*tmp_doc;
	bs_list_elem_t	*tmp_elm_item;
	bs_element_t	*tmp_elem;


	tmp_doc = this->document_list;
	while (tmp_doc) {
		std::cout << "{";
		tmp_elm_item = tmp_doc->element_list;
		while (tmp_elm_item) {
			tmp_elm_item->element->json_dump_element();
			tmp_elm_item = tmp_elm_item->next_e;
			if (tmp_elm_item) {
				std::cout << ",";
			}
		}
		std::cout << "}" << std::endl;
		tmp_doc = tmp_doc->next_d;
	}
}
