#include "BSON_document.class.hpp"
#include "BSON_element.class.hpp"
#include "bson.hpp"

#define DATA_PTR(current_index) bson_data.data()+current_index

void BSON::interpret_string(int32_t **p_size, char **bs_string, char_vec_t bson_data, int& current_index) {
	*p_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	current_index += sizeof(int32_t);
	*bs_string = DATA_PTR(current_index);
	std::cout << **p_size << " : " << DATA_PTR(current_index) << std::endl;
	current_index += **p_size;
}

void BSON::interpret_cstring(char **bs_string, char_vec_t bson_data, int& current_index) {
	*bs_string = DATA_PTR(current_index);
	current_index += strlen(DATA_PTR(current_index)) + 1;
}

/*
**	methodes creant les BSON_element du type approprie
*/

bs_element_t	*BSON::handle_embedded_document(char_vec_t bson_data, int& current_index) {
	BSON_document	*bs_document;
	int32_t			*doc_size;
	bs_element_t	*new_element;
	char			*p_name;

	this->interpret_cstring(&p_name, bson_data, current_index);
	doc_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	current_index += sizeof(int32_t);
	bs_document = this->element_dispatcher(bson_data, *doc_size, current_index);
	current_index += *doc_size;
	new_element = new BSON_element(bs_document, p_name, *doc_size, BSON_DOC_T);
	return new_element;
}

// TEST A FAIRE SUR LES ARRAYS POUR LES NAMES DE CHAQUE DATA => INT32 ??
bs_element_t	*BSON::handle_array(char_vec_t bson_data, int& current_index) {
	BSON_document	*bs_document;
	int32_t			*doc_size;
	char			*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	doc_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	current_index += sizeof(int32_t);
	bs_document = this->element_dispatcher(bson_data, *doc_size, current_index);
	current_index += *doc_size;
	new_element = new BSON_element(bs_document, p_name, *doc_size, BSON_DOC_T);
	return new_element;
}

bs_element_t *BSON::handle_double(char_vec_t bson_data, int& current_index) {
	double *p_double;
	bs_element_t	*new_element;
	char			*p_name;

	// std::cout << DATA_PTR(current_index) << std::endl;
	this->interpret_cstring(&p_name, bson_data, current_index);
	p_double = reinterpret_cast<double *>(DATA_PTR(current_index));

	new_element = new BSON_element(p_double, p_name, sizeof(double), BSON_DOUBLE_T);
	current_index += sizeof(double);
	// std::cout << *p_double << std::endl;
	return new_element;
}


bs_element_t	*BSON::handle_string(char_vec_t bson_data, int& current_index,  bson_type_t type) {
	char			*bs_string;
	bs_element_t	*new_element;
	char			*p_name;
	int32_t			*p_size;

	this->interpret_cstring(&p_name, bson_data, current_index);
	this->interpret_string(&p_size, &bs_string, bson_data, current_index);
	new_element = new BSON_element(bs_string, p_name, *p_size, type);
	return new_element;
}

bs_element_t	*BSON::handle_binary_data(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	unsigned char	*p_subtype;
	bs_element_t	*new_element;
	int32_t			*bin_size;
	unsigned char	*bin_data;

	this->interpret_cstring(&p_name, bson_data, current_index);
	bin_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	current_index += sizeof(int32_t);
	p_subtype = reinterpret_cast<unsigned char *>(DATA_PTR(current_index));
	current_index += 1;
	bin_data = reinterpret_cast<unsigned char *>(DATA_PTR(current_index));
	new_element = new BSON_element(*p_subtype, bin_data, p_name, *bin_size, BSON_BINARY_T);
	current_index += *bin_size;
	return new_element;
}

bs_element_t	*BSON::handle_undefined(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	new_element = new BSON_element(p_name, BSON_UNDEFINED_T);
	return new_element;
}

bs_element_t	*BSON::handle_null_value(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	new_element = new BSON_element(p_name, BSON_NULL_T);
	return new_element;
}

bs_element_t	*BSON::handle_int64(char_vec_t bson_data, int& current_index, bson_type_t type) {
	char			*p_name;
	bs_element_t	*new_element;
	int64_t			*p_int64;

	this->interpret_cstring(&p_name, bson_data, current_index);
	p_int64 = reinterpret_cast<int64_t *>(DATA_PTR(current_index));
	new_element = new BSON_element(*p_int64, p_name, sizeof(int64_t), type);
	current_index += sizeof(int64_t);
	return new_element;
}

bs_element_t	*BSON::handle_boolean(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	bs_element_t	*new_element;
	unsigned char	*bool_value;

	this->interpret_cstring(&p_name, bson_data, current_index);
	bool_value = reinterpret_cast<unsigned char *>(DATA_PTR(current_index));
	new_element = new BSON_element(*bool_value, p_name, BSON_BOOL_T);
	return new_element;
}

bs_element_t	*BSON::handle_int32(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	bs_element_t	*new_element;
	int32_t			*p_int32;

	this->interpret_cstring(&p_name, bson_data, current_index);
	p_int32 = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	new_element = new BSON_element(*p_int32, p_name, sizeof(int32_t), BSON_INT32_T);
	current_index += sizeof(int32_t);
	return new_element;
}

bs_element_t	*BSON::handle_regular_expression(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	char			*pattern;
	int				elem_size;
	char			*flags;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	this->interpret_cstring(&pattern, bson_data, current_index);
	this->interpret_cstring(&flags, bson_data, current_index);
	elem_size = strlen(pattern) + strlen(flags) + 2;
	new_element = new BSON_element(pattern, flags, p_name, elem_size, BSON_REGEX_T);
	return new_element;
}

bs_element_t	*BSON::handle_db_pointer(char_vec_t bson_data, int& current_index) {
	char			*p_name;
	int32_t			*p_str_size;
	unsigned char	pointer[12];
	char			*pointer_string;
	bs_element_t	*new_element;
	int				i;

	this->interpret_cstring(&p_name, bson_data, current_index);
	this->interpret_string(&p_str_size, &pointer_string, bson_data, current_index);
	for (i=0;i<12;i++) {
		pointer[i] = bson_data[current_index + i];
	}
	new_element = new BSON_element(pointer_string, &pointer[0], *p_str_size, p_name, BSON_DB_POINT_T);
	current_index += i;
	return new_element;
}

bs_element_t	*BSON::handle_javascript_code_w_scope(char_vec_t bson_data, int& current_index) {
	int32_t			*elem_size;
	BSON_document	*co_document;
	int32_t			*doc_size;
	char			*js_code;
	char			*p_name;
	bs_element_t	*new_element;
	int32_t			*code_size;

	this->interpret_cstring(&p_name, bson_data, current_index);
	elem_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	this->interpret_string(&code_size, &js_code, bson_data, current_index);
	doc_size = reinterpret_cast<int32_t *>(DATA_PTR(current_index));
	co_document = this->element_dispatcher(bson_data, *doc_size, current_index);
	new_element = new BSON_element(js_code, *code_size, co_document, *doc_size, p_name, *elem_size, BSON_JS_W_S_T);
	current_index += *doc_size;
	return new_element;
}

bs_element_t	*BSON::handle_timestamp(char_vec_t bson_data, int& current_index) {
	uint64_t	*p_timestamp;
	char		*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	p_timestamp = reinterpret_cast<uint64_t *>(DATA_PTR(current_index));
	new_element = new BSON_element(*p_timestamp, p_name, sizeof(uint64_t), BSON_TIME_T);
	return new_element;
}


//LONG DOUBLE TYPE MARCHE SUR MAC OS
bs_element_t	*BSON::handle_decimal128(char_vec_t bson_data, int& current_index) {
	long double		*p_dec128;
	char			*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	p_dec128 = reinterpret_cast<long double *>(DATA_PTR(current_index));
	new_element = new BSON_element(*p_dec128, p_name, sizeof(long double), BSON_DEC128_T);
	current_index += sizeof(long double);
	return new_element;
}

bs_element_t	*BSON::handle_key(char_vec_t bson_data, int& current_index, bson_type_t type) {
	char		*p_name;
	bs_element_t	*new_element;

	this->interpret_cstring(&p_name, bson_data, current_index);
	new_element = new BSON_element(p_name, type);
	return new_element;
}

bs_element_t	*BSON::handle_object_id(char_vec_t bson_data, int& current_index) {
	unsigned char	object_id[12];
	bs_element_t	*new_element;
	char			*p_name;
	int		i;

	// std::cout << DATA_PTR(current_index) << std::endl;
	this->interpret_cstring(&p_name, bson_data, current_index);
	for (i = 0; i < 12; i++) {
		object_id[i] = bson_data[current_index + i];
		// printf("%02x", object_id[i]);
	}
	new_element = new BSON_element(&object_id[0], p_name, 12, BSON_OID_T);
	current_index += i;
	// std::cout << std::endl;
	return new_element;
}

BSON_document *BSON::element_dispatcher(char_vec_t bson_data, int32_t doc_size, int current_index) {
	BSON_document		*cur_doc;

	cur_doc = new BSON_document();
	int &i = current_index;
	while (i - current_index < doc_size) {
		switch (static_cast<unsigned char>(bson_data[i])) {
			case 0x00:
				return cur_doc;
			case BSON_DOUBLE_T:
				i++;
				cur_doc->add_element_to_list(this->handle_double(bson_data, i));
				break;
			case BSON_STRING_T:
				i++;
				cur_doc->add_element_to_list(this->handle_string(bson_data, i, BSON_STRING_T));
				break;
			case BSON_DOC_T:
				i++;
				cur_doc->add_element_to_list(this->handle_embedded_document(bson_data, i));
				break;
			case BSON_ARRAY_T:
				i++;
				cur_doc->add_element_to_list(this->handle_array(bson_data, i));
				break;
			case BSON_BINARY_T:
				i++;
				cur_doc->add_element_to_list(this->handle_binary_data(bson_data, i));
				break;
			case BSON_UNDEFINED_T:
				i++;
				cur_doc->add_element_to_list(this->handle_undefined(bson_data, i));
				break;
			case BSON_OID_T:
				i++;
				cur_doc->add_element_to_list(this->handle_object_id(bson_data, i));
				break;
			case BSON_BOOL_T:
				i++;
				cur_doc->add_element_to_list(this->handle_boolean(bson_data, i));
				break;
			case BSON_UTC_DATE_T:
				i++;
				cur_doc->add_element_to_list(this->handle_int64(bson_data, i, BSON_UTC_DATE_T));
				break;
			case BSON_NULL_T:
				i++;
				cur_doc->add_element_to_list(this->handle_null_value(bson_data, i));
				break;
			case BSON_REGEX_T:
				i++;
				cur_doc->add_element_to_list(this->handle_regular_expression(bson_data, i));
				break;
			case BSON_DB_POINT_T:
				i++;
				cur_doc->add_element_to_list(this->handle_db_pointer(bson_data, i));
				break;
			case BSON_JS_CODE_T:
				i++;
				cur_doc->add_element_to_list(this->handle_string(bson_data, i, BSON_JS_CODE_T));
				break;
			case BSON_SYMBOL_T:
				i++;
				cur_doc->add_element_to_list(this->handle_string(bson_data, i, BSON_SYMBOL_T));
				break;
			case BSON_JS_W_S_T:
				i++;
				cur_doc->add_element_to_list(this->handle_javascript_code_w_scope(bson_data, i));
				break;
			case BSON_INT32_T:
				i++;
				cur_doc->add_element_to_list(this->handle_int32(bson_data, i));
				break;
			case BSON_TIME_T:
				i++;
				cur_doc->add_element_to_list(this->handle_timestamp(bson_data, i));
				break;
			case BSON_INT64_T:
				i++;
				cur_doc->add_element_to_list(this->handle_int64(bson_data, i, BSON_INT64_T));
				break;
			case BSON_DEC128_T:
				i++;
				cur_doc->add_element_to_list(this->handle_decimal128(bson_data, i));
				break;
			case BSON_MIN_K_T:
				i++;
				cur_doc->add_element_to_list(this->handle_key(bson_data, i, BSON_MIN_K_T));
				break;
			case BSON_MAX_K_T:
				i++;
				cur_doc->add_element_to_list(this->handle_key(bson_data, i, BSON_MAX_K_T));
				break;
			default:
				i++;
				break;

		}
	}
	return NULL;
}


BSON::BSON(char_vec_t bson_data, int total_size) {
	int i = 0;
	int32_t		*p_doc_size;

	while (i < total_size) {
		p_doc_size = reinterpret_cast<int32_t *>(bson_data.data() + i);
		this->add_document_to_list(this->new_document(this->element_dispatcher(bson_data, *p_doc_size, i + sizeof(int32_t))));
		i += *p_doc_size;
		p_doc_size = NULL;
	}
}

BSON::~BSON() {
	std::cout << "bye bye";
}

/*
***	Fonctions propres a la liste de document : document_list, attribut de chaque bson,
***	ou sont stockes les documents trouvés sur le buffer
*/

bs_document_list_t *BSON::new_document(BSON_document *document) {
	bs_document_list_t	*new_document;

	new_document = new 	bs_document_list_t;
	new_document->cur_doc = document;
	new_document->next_d = NULL;
	return new_document;
}


void BSON::add_document_to_list(bs_document_list_t *new_document) {
	bs_document_list_t	*tmp_document;

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
*** return the json from the bson taken at initilization
*/

void BSON::json_dump(void) {
	bs_document_list_t	*tmp_doc;
	BSON_document		*document;

	tmp_doc = this->document_list;
	while (tmp_doc) {
        std::cout << "{";
		document = tmp_doc->cur_doc;
		document->dump_document();
		std::cout << "}" << std::endl;
		tmp_doc = tmp_doc->next_d;
	}
}
