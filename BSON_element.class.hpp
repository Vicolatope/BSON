#ifndef _BSON_CLASS_ELEM_H_
	#define _BSON_CLASS_ELEM_H_

	#include <iostream>

	#define BSON_DOUBLE_T 1
	#define BSON_STRING_T 2
	#define BSON_DOC_T 3
	#define BSON_ARRAY_T 4
	#define BSON_BINARY_T 5
	#define BSON_UNDEFINED_T 6
	#define BSON_OID_T 7
	#define BSON_BOOL_T 8
	#define BSON_UTC_DATE_T 9
	#define BSON_NULL_T 10
	#define BSON_REGEX_T 11
	#define BSON_DB_POINT_T 12
	#define BSON_JS_CODE_T 13
	#define BSON_SYMBOL_T 14
	#define BSON_JS_W_S_T 15
	#define BSON_INT32_T 16
	#define BSON_TIME_T 17
	#define BSON_INT64_T 18
	#define BSON_DEC128_T 19
	#define BSON_MIN_K_T 0xFF
	#define BSON_MAX_K_T 0x7F



	typedef unsigned char bson_element_type;
/*
	BSON_element est la classe qui representera les données et les rendra accessible dans leur type réel,
	en CPP, via l'utlisation d'une instance de BSON.
	*/

	class BSON_element {

		private:
			double				bs_double;
			unsigned char		bs_oid[12];
			char				*name;
			int32_t				size;
			bson_element_type	type;
		public:
			BSON_element(double *bs_double, char *name, int elem_size, bson_element_type type);
			BSON_element(unsigned char *bs_oid, char *name, int elem_size, bson_element_type type);
			~BSON_element();
			void 	json_dump_element();
			void 	dump_value();
	};
#endif
