#include "BSON_document.class.hpp"
#include "BSON_element.class.hpp"
#include "bson.hpp"
/*
**	BSON_element constructeurs => utilisation du polymorphisme en cpp pour avoir un constructeur
***	propre a chaque type

*** ====> Ajouter une name_size pr strndup name size.

*/

/*
***	============== BSON_element methods ==============
*/

/*
***	Constructeur BSON_element, initialise size, name et type
***	pour tous les BSON_element
*/

BSON_element::BSON_element(char *name, int32_t size, bson_type_t type) :
name(strdup(name)),
size(size),
type(type) {}

/*
**	getter & json_dumper pour le name
*/

char	*BSON_element::get_name(void) {
	return this->name;
}

void 	BSON_element::dump_name(void) {
	std::cout << "\"" << this->get_name() << "\":";
}

/*
**	============== BSON_double methods ==============
*/

BSON_double::BSON_double(double *bs_double, char *name, int32_t elem_size, bson_type_t type)
:  BSON_element(name, elem_size, type), bs_double(*bs_double) {
}

double	BSON_double::get_value(void) {
	return this->bs_double;
}

void BSON_double::dump_value(void) {
	this->dump_name();
	printf("%f", this->get_value());
}

/*
**	============== BSON_int32 methods ==============
*/

BSON_int32::BSON_int32(int32_t bs_int32, char *name, int32_t elem_size, bson_type_t type)
: BSON_element(name, elem_size, type), bs_int32(bs_int32) {}

int32_t	BSON_int32::get_value(void) {
	return this->bs_int32;
}

void BSON_int32::dump_value(void) {
	this->dump_name();
	std::cout << this->get_value();
}

/*
** ==============	BSON_int64 methods ==============
*/

BSON_int64::BSON_int64(int64_t bs_int64, char *name, int32_t elem_size, bson_type_t type)
: BSON_element(name, elem_size, type), bs_int64(bs_int64) {
}

int64_t	BSON_int64::get_value(void) {
	return this->bs_int64;
}

void BSON_int64::dump_value(void) {
	this->dump_name();
	std::cout << this->get_value();
}

/*
**	============== BSON_oid methods ==============
*/

BSON_oid::BSON_oid(unsigned char *bs_oid, char *name, bson_type_t type)
: BSON_element(name, 12, type) {
	memcpy(&this->bs_oid[0], bs_oid, 12);
}

unsigned char	*BSON_oid::get_value() {
	return &this->bs_oid[0];
}

void BSON_oid::dump_value(void) {
	this->dump_name();
	std::cout << "{\"$oid\":\"";
	for (int i=0; i < 12; i++) {
		printf("%02x", this->get_value()[i]);
	}
	std::cout << "\"";
}

/*
**	============== BSON_string methods ==============
*/

BSON_string::BSON_string(char *bs_string, char *name, int32_t elem_size, bson_type_t type)
	: BSON_element(name, elem_size, type), bs_string(strndup(bs_string, elem_size)) {
}

char	*BSON_string::get_value(void) {
	return this->bs_string;
}

void BSON_string::dump_value(void) {
	this->dump_name();
	std::cout << "\"" << this->get_value() << "\"";
}

/*
**	============== BSON_js_code ==============
*/

BSON_js_code::BSON_js_code(char *js_code, char *name, int32_t elem_size, bson_type_t type)
: js_code(strndup(js_code, elem_size)), BSON_element(name, elem_size, type) {}

char	*BSON_js_code::get_value(void) {
	return this->js_code;
}

void BSON_js_code::dump_value(void) {
	this->dump_name();
	std::cout << "\"" << this->get_value() << "\"";
}

/*
**	============== BSON_doc_elem methods ==============
*/

BSON_doc_elem::BSON_doc_elem(BSON_document *bs_document, char *name, int32_t elem_size, bson_type_t type)
: BSON_element(name, elem_size, type), bs_document(bs_document) {
}

BSON_document	*BSON_doc_elem::get_value(void) {
	return this->bs_document;
}

void BSON_doc_elem::dump_value(void) {
	this->dump_name();
	this->get_value()->dump_document();
}

/*
**	============== BSON_binary ==============
*/

BSON_binary::BSON_binary(unsigned char bin_subtype, unsigned char *bin_data, char *name, int32_t elem_size, bson_type_t type)
: bs_bin_subtype(bin_subtype), BSON_element(name, elem_size, type) {
	this->bs_bin_data = new unsigned char[elem_size];
	memcpy(this->bs_bin_data, bin_data, elem_size);
}

unsigned char	*BSON_binary::get_value(int32_t *bin_size=NULL) {
	if (bin_size)
		*bin_size = this->size;
	return this->bs_bin_data;
}

void 	BSON_binary::dump_value(void) {
	unsigned char	*bin_data;
	int32_t			data_size;

	bin_data = this->get_value(&size);
	this->dump_name();
	for(int32_t i=0;i< data_size;i++) {
		printf("%02x", bin_data[i]);
	}
}

/*
**	============== BSON_key methods ==============
*/

BSON_key::BSON_key(char *name, bson_type_t type)
: BSON_element(name, 0, type) {}

bool	BSON_key::get_value(void) {
	return this->type == BSON_MIN_K_T ? 0 : 1;
}

void BSON_key::dump_value(void) {
	this->dump_name();
	std::cout << (this->get_value() ? "MAX_KEY" : "MIN_KEY");
}

/*
**	============== BSON_null methods ==============
*/

BSON_null::BSON_null(char *name, bson_type_t type)
: BSON_element(name, 0, type) {}

void *BSON_null::get_value(void) {
	return NULL;
}

void BSON_null::dump_value(void) {
	this->dump_name();
	std::cout << "null";
}

/*
**	============== BSON_bool ==============
*/

BSON_bool::BSON_bool(bool bs_bool, char *name, bson_type_t type)
: bs_bool(bs_bool), BSON_element(name, 1, type) {}

bool	BSON_bool::get_value(void) {
	return this->bs_bool;
}

void BSON_bool::dump_value(void) {
	this->dump_name();
	std::cout << (this->get_value() ? "true" : "false");
}

/*
***	============== BSON_db_pointer methods ==============

***	DEPRECEATED ====>GETTER AND JSON_DUMPER NOT IMPLEMENTED
*/

BSON_db_pointer::BSON_db_pointer(char *pointer_string, unsigned char *bs_dbpointer, int32_t ptr_str_size, char *name, bson_type_t type)
: bs_dbstring(strndup(pointer_string, ptr_str_size)), BSON_element(name, ptr_str_size + 12, type) {
	memcpy(&this->bs_dbpointer[0], bs_dbpointer, 12);
}

BSON_db_pointer	*BSON_db_pointer::get_value(void) {
	return NULL;
}

void BSON_db_pointer::dump_value(void) {
	this->dump_name();
	std::cout << "DB_POINTER";
}

/*
***	============== BSON_js_scoped_code methods ==============

***	 le getter returne sa propre instance ==> INUTILE POUR L'INSTANT
*/

BSON_js_scoped_code::BSON_js_scoped_code(char *js_code, int32_t code_size, BSON_document *co_document, int32_t doc_size, char *name, int32_t elem_size, bson_type_t type)
: js_code(strndup(js_code, code_size)), bs_document(co_document), doc_size(doc_size), code_size(code_size), BSON_element(name, elem_size, type) {}

BSON_js_scoped_code		*BSON_js_scoped_code::get_value(void) {
	return this;
}

void BSON_js_scoped_code::dump_value(void) {
	this->dump_name();
	std::cout << "{\"code\":\"" << this->js_code << "\",\"scope\":";
	this->bs_document->dump_document();
}

/*
***	============== BSON_timestamp methods ==============
*/

BSON_timestamp::BSON_timestamp(uint64_t bs_timestamp, char *name, int32_t elem_size, bson_type_t type)
: BSON_element(name, elem_size, type), bs_timestamp(bs_timestamp) {}

uint64_t	BSON_timestamp::get_value(void) {
	return this->bs_timestamp;
}

void 	BSON_timestamp::dump_value(void) {
	this->dump_name();
	std::cout << this->get_value();
}

/*
***	============== BSON_dec128 methods ==============
*/

BSON_dec128::BSON_dec128(long double bs_dec128, char *name, int32_t elem_size, bson_type_t type)
: bs_dec128(bs_dec128), BSON_element(name, elem_size, type) {}

long double BSON_dec128::get_value(void) {
	return this->bs_dec128;
}

void 	BSON_dec128::dump_value(void) {
	this->dump_name();
	printf("%Lf", this->get_value());
}


/*
***	============== BSON_regex methods ==============

***	Flags supporte pour regex == 'i', 'l'. les autres en attente.
*/

BSON_regex::BSON_regex(char *pattern, char *flags, char *name, int32_t elem_size, bson_type_t type)
: BSON_element(name, elem_size, type), pattern(strdup(pattern)), flags(strdup(flags)) {
	std::regex_constants::syntax_option_type reg_flags = std::regex_constants::ECMAScript;
	for (int32_t i = 0;i < strlen(flags); i++) {
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

std::regex	*BSON_regex::get_value(void) {
	return this->bs_regex;
}

void BSON_regex::dump_value(void) {
	this->dump_name();
	std::cout << "\\/" << this->pattern << "\\/" << this->flags;
}

BSON_element::~BSON_element() {
}
