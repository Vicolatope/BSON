#include "BSON_document.class.hpp"
#include "BSON_element.class.hpp"
#include "bson.hpp"
/*
**	BSON_element constructeurs => utilisation du polymorphisme en cpp pour avoir un constructeur
***	propre a chaque type

*** ====> Ajouter une name_size pr strndup name size.

*/

BSON_element::BSON_element(double *bs_double, char *name, int elem_size, bson_type_t type)
:  size(elem_size), type(type), bs_double(*bs_double), name(strdup(name)) {
	std::cout << "created a double" << std::endl << "named : " << name << std::endl;
}

BSON_element::BSON_element(int32_t bs_int32, char *name, int elem_size, bson_type_t type)
: size(elem_size), name(strdup(name)), type(type), bs_int32(bs_int32) {
	std::cout << "created an int32 named : " << name << std::endl;
}

BSON_element::BSON_element(int64_t bs_int64, char *name, int elem_size, bson_type_t type)
: size(elem_size), name(strdup(name)), type(type), bs_int64(bs_int64) {
	std::cout << "created an int32 named : " << name << std::endl;
}

BSON_element::BSON_element(unsigned char *bs_oid, char *name, int elem_size, bson_type_t type)
: size(elem_size), type(type), name(strdup(name)) {
	memcpy(&this->bs_oid[0], bs_oid, 12);
	std::cout << "created a oid" << std::endl << "named : " << name << std::endl;
}

BSON_element::BSON_element(char *bs_string, char *name, int elem_size, bson_type_t type)
	: size(elem_size), type(type), name(strdup(name)), bs_string(strndup(bs_string, elem_size)) {
	std::cout << "created a string named :" << name << std::endl << bs_string << std::endl;
}

BSON_element::BSON_element(BSON_document *bs_document, char *name, int elem_size, bson_type_t type)
: bs_document(bs_document), name(strdup(name)), size(elem_size), type(type) {
	std::cout << "created a doc named :" << name << std::endl;
}

BSON_element::BSON_element(unsigned char bin_subtype, unsigned char *bin_data, char *name, int elem_size, bson_type_t type)
: bs_bin_subtype(bin_subtype), name(strdup(name)), size(elem_size), type(type) {
	this->bs_bin_data = new unsigned char[elem_size];
	memcpy(this->bs_bin_data, bin_data, elem_size);
}

BSON_element::BSON_element(char *name, bson_type_t type)
: type(type), size(0), name(strdup(name)) {}

BSON_element::BSON_element(unsigned char bs_bool, char *name, bson_type_t type)
: bs_bool(bs_bool ? true : false), name(strdup(name)), type(type), size(1) {}

BSON_element::BSON_element(char *pointer_string, unsigned char *bs_dbpointer, int ptr_str_size, char *name, bson_type_t type)
: bs_dbstring(strndup(pointer_string, ptr_str_size)), name(name), size(ptr_str_size + 12), type(type) {
	memcpy(&this->bs_dbpointer[0], bs_dbpointer, 12);
}

BSON_element::BSON_element(char *js_code, int code_size, BSON_document *co_document, int doc_size, char *name, int elem_size, bson_type_t type)
: bs_string(strndup(js_code, code_size)), bs_document(co_document), doc_size(doc_size), name(strdup(name)), size(elem_size), type(type) {}

BSON_element::BSON_element(uint64_t bs_timestamp, char *name, int elem_size, bson_type_t type)
: type(type), name(strdup(name)), bs_timestamp(bs_timestamp), size(elem_size) {}

BSON_element::BSON_element(long double bs_dec128, char *name, int elem_size, bson_type_t type)
: bs_dec128(bs_dec128), name(strdup(name)), size(elem_size), type(type) {}

/*
*** constrcteur regex element
***	Flags supporte pour regex == 'i', 'l'. les autres en attente.
*/

BSON_element::BSON_element(char *pattern, char *flags, char *name, int elem_size, bson_type_t type)
: name(strdup(name)), type(type), size(elem_size) {
	std::regex_constants::syntax_option_type reg_flags;
	for (int i = 0;i < strlen(flags); i++) {
		switch (flags[i]) {
			case 'i':
				reg_flags = reg_flags | std::regex_constants::icase;
				break;
			case 'l':
				reg_flags = reg_flags | std::regex_constants::collate;
		}
	}
	this->bs_regex = new std::regex(pattern, reg_flags);
}

BSON_element::~BSON_element() {
	std::cout << "Bye";
}

void BSON_element::dump_value(void) {
	switch (this->type) {
		case BSON_DOUBLE_T:
			printf("%f", this->bs_double);
			break;
		case BSON_OID_T:
			std::cout << "{\"$oid\":\"";
			for (int i=0;i<12;i++) {
				printf("%02x", this->bs_oid[i]);
			}
			std::cout << "\"}";
			break;
		case BSON_STRING_T:
			std::cout << "\"" << this->bs_string << "\"";
			break;
		case BSON_INT32_T:
			std::cout << this->bs_int32;
		default:
			break;
	}
}

void BSON_element::json_dump_element(void) {
	std::cout << "\"" << this->name << "\":";
	this->dump_value();
}
