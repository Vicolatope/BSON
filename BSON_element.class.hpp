#ifndef _BSON_CLASS_ELEM_H_
# define _BSON_CLASS_ELEM_H_

// # include "bson.hpp"
# include <regex>
#include "BSON_document.class.hpp"
#include "BSON.class.hpp"
class BSON_document;

/*
BSON_element est la classe qui representera les données et les rendra accessible dans leur type réel,
en CPP, via l'utlisation d'une instance de BSON.
*/

class BSON_element {

	private:
		std::regex			*bs_regex;

		int32_t				bs_int32;

		int64_t				bs_int64;

		double				bs_double;
		BSON_document		*bs_document;
		int32_t				doc_size;
		unsigned char		bs_oid[12];
		unsigned char		bs_dbpointer[12];
		char				*bs_dbstring;
		char				*bs_string;
		unsigned char		bs_bin_subtype;
		unsigned char		*bs_bin_data;
		bool				bs_bool;
		uint64_t			bs_timestamp;
		long double			bs_dec128;
		char				*name;
		int32_t				size;
		bson_type_t			type;

	public:
		BSON_element(double *bs_double, char *name, int elem_size, bson_type_t type);
		BSON_element(unsigned char *bs_oid, char *name, int elem_size, bson_type_t type);
		BSON_element(char *bs_string, char *name, int elem_size, bson_type_t type);
		BSON_element(int32_t bs_int32, char *name, int elem_size, bson_type_t type);
		BSON_element(int64_t bs_int64, char *name, int elem_size, bson_type_t type);
		BSON_element(BSON_document *bs_document, char *name, int elem_size, bson_type_t type);
		BSON_element(unsigned char bin_subtype, unsigned char *bin_data, char *name, int elem_size, bson_type_t type);
		BSON_element(char *name, bson_type_t type);
		BSON_element(unsigned char bs_bool, char *name, bson_type_t type);
		BSON_element(char *pattern, char *flags, char *name, int elem_size, bson_type_t type);
		BSON_element(char *pointer_string, unsigned char *bs_dbpointer, int ptr_str_size, char *name, bson_type_t type);
		BSON_element(char *js_code, int code_size, BSON_document *co_document, int doc_size, char *name, int elem_size, bson_type_t type);
		BSON_element(uint64_t timestamp, char *name, int elem_size, bson_type_t type);
		BSON_element(long double bs_dec128, char *name, int elem_size, bson_type_t type);
		~BSON_element();
		void 	json_dump_element();
		void 	dump_value();
};

#endif
