#ifndef _BSON_HPP_
# define _BSON_HPP_

# include <iostream>
# include <vector>
# include <regex>

/*
*** DEFINITION DES TYPES BSON
*/

# define BSON_DOUBLE_T 0x01
# define BSON_STRING_T 0x02
# define BSON_DOC_T 0x03
# define BSON_ARRAY_T 0x04
# define BSON_BINARY_T 0x05
# define BSON_UNDEFINED_T 0x06
# define BSON_OID_T 0x07
# define BSON_BOOL_T 0x08
# define BSON_UTC_DATE_T 0x09
# define BSON_NULL_T 0x0A
# define BSON_REGEX_T 0x0B
# define BSON_DB_POINT_T 0x0C
# define BSON_JS_CODE_T 0x0D
# define BSON_SYMBOL_T 0x0E
# define BSON_JS_W_S_T 0x0F
# define BSON_INT32_T 0x10
# define BSON_TIME_T 0x11
# define BSON_INT64_T 0x12
# define BSON_DEC128_T 0x13
# define BSON_MIN_K_T 0xFF
# define BSON_MAX_K_T 0x7F

typedef unsigned char		bson_type_t; //typedef pour types BSON.
typedef std::vector<char> 	char_vec_t; //typedef pour le vecteur en parametre

/*
**  Declaration des classes
*/

class BSON_document;
class BSON;
class BSON_element;

/*
**  Liste representant la liste d'element qui compose un document
*/

typedef struct			s_element {
	BSON_element		*element;
	struct s_element	*next_e;
}						bs_list_elem_t;

/*
**  liste representant la liste de document, qui compose une collection
**  (un ensemble de documents)
*/

typedef struct			s_document {
	BSON_document		*cur_doc;
	struct s_document	*next_d;
}						bs_document_list_t;

/*
**  INCLUDE DES classes
*/

#include "BSON.class.hpp"
#include "BSON_document.class.hpp"
#include "BSON.class.hpp"

typedef BSON_element		bs_element_t;
typedef BSON				bs_parser_t;

#endif
