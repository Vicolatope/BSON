#ifndef _BSON_CLASS_ELEM_H_
# define _BSON_CLASS_ELEM_H_

# include "bson.hpp"

/*
***	BSON_element est la classe qui representera les données et les rendra accessible dans leur type réel,
***	en CPP, via l'utlisation d'une instance de BSON.

***	dump_value : dump la valeur de l'element en json.
*/

class BSON_element {

	protected:
		char				*name;
		int32_t				size;
		bson_type_t			type;
		BSON_element(char *name, int32_t size, bson_type_t type);

	public:
		~BSON_element(void);
		virtual void	dump_value(void) = 0;
		void 	print_name(void);
		char	*get_name(void);
};

/*
***	=============== BSON_dec128 ===============

*** Classe representant un decimal sur 128 bits, represente
***	par un long double. Type sur 128 bits sur Intel x86_64
***	portabilite a verifier ..
*** getter return un long double
*/

class BSON_dec128: public BSON_element {
	private:
		long double	bs_dec128;
	public:
		long double	get_value(void);
		void 		dump_value(void);
		BSON_dec128(long double bs_dec128, char *name, int elem_size, bson_type_t type);
};

/*
*** =============== BSON_timestamp ===============

***	Classe representant un timestamp grace a un
***	uint64_t, un int non signe sur 64 bits
*** getter retourne un uint64_t
*/

class BSON_timestamp: public BSON_element {
	private:
		uint64_t	bs_timestamp;
	public:
		void 		dump_value(void);
		uint64_t	get_value(void);
		BSON_timestamp(uint64_t bs_timestamp, char *name, int elem_size, bson_type_t type);
};

/*
***	=============== BSON_js_scoped_code ===============

***	Classe representant du code js avec un 'scope' de donnees,
***	represente grace a un char *(js_code) et
***	un BSON_document(bs_document, le 'scope')
***	getter retourne this BSON_js_scoped_code, inutile pour l'instant
*/

class BSON_js_scoped_code: public BSON_element {
	private:
		BSON_document	*bs_document;
		char			*js_code;
		int32_t			doc_size;
		int32_t			code_size;
	public:
		void 		dump_value(void);
		BSON_js_scoped_code	*get_value(void);
		BSON_js_scoped_code(char *js_code, int32_t code_size, BSON_document *co_document, int32_t doc_size, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_js_code ===============

***	represente du code js sur un char *,
***	getter retourne ce char *
*/

class BSON_js_code: public BSON_element {
	private:
		char	*js_code;
	public:
		void 	dump_value(void);
		char	*get_value(void);
		BSON_js_code(char *js_code, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_db_pointer ===============

***	represente un bd_pointer sur un unsigned char[12] et
***	la string accompagnant sur un char *
***	getter retourne this BSON_db_pointer => Inutile.
*/

class BSON_db_pointer: public BSON_element {
	private:
		unsigned char		bs_dbpointer[12];
		char				*bs_dbstring;
	public:
		void 	dump_value(void);
		BSON_db_pointer	*get_value(void);
		BSON_db_pointer(char *pointer_string, unsigned char *bs_dbpointer, int32_t ptr_str_size, char *name, bson_type_t type);
};

/*
***	=============== BSON_regex ===============

***	classe representant une regex grace a une instance de
***	std::regex.
***	les char *pattern et flags sont conserves pour le dump en json_dump
*/

class BSON_regex: public BSON_element {
	private:
		std::regex	*bs_regex;
		char		*pattern;
		char		*flags;
	public:
		void 	dump_value(void);
		std::regex	*get_value(void);
		BSON_regex(char *pattern, char *flags, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_bool ===============

***	Booleen represente sur un bool.
***	getter retourne ce bool.
*/

class BSON_bool: public BSON_element {
	private:
		bool	bs_bool;
	public:
		void 	dump_value(void);
		bool	get_value(void);
		BSON_bool(bool bs_bool, char *name, bson_type_t type);
};

/*
***	=============== BSON_null ===============

***	Bson null represente aussi le type BSON undefined, qui est depreceated.
***	getter renvoie simplement NULL, et il n'est stocke null part.
*/

class BSON_null: public BSON_element {
	public:
		void 	dump_value(void);
		void *get_value(void);
		BSON_null(char *name, bson_type_t type);
};

/*
***	=============== BSON_key ===============

*** represente grace au BSON_element::type,
***	true si la Key est Max, false si Min
*/

class BSON_key: public BSON_element {
	public:
		void 	dump_value(void);
		bool	get_value(void);
		BSON_key(char *name, bson_type_t type);
};

/*
***	=============== BSON_binary ===============

***	represente par un unsigned char *,
***	le subtype est conserve, cependant la data n'est
***	pas stocke differement, selon les types.
*** le getter de BSON_binary prend un int32_t* en parametre,
***	pour le remplir avec la taille de la data
*/

class BSON_binary: public BSON_element {
	private:
		unsigned char	*bs_bin_data;
		unsigned char	bs_bin_subtype;
	public:
		void 	dump_value(void);
		unsigned char	*get_value(int32_t *size);
		BSON_binary(unsigned char bin_subtype, unsigned char *bin_data, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_doc_elem ===============

*** BSON_element representant un document grace a
***	un BSON_document *. Le getter retourne ce BSON_document
*/

class BSON_doc_elem: public BSON_element {
	private:
		BSON_document	*bs_document;
	public:
		void 	dump_value(void);
		BSON_document	*get_value(void);
		BSON_doc_elem(BSON_document *bs_document, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_int64 ===============

***	Classe representant un int64_t, getter renvoie un int64_t.
*/

class BSON_int64: public BSON_element {
	private:
		int64_t		bs_int64;
	public:
		void 	dump_value(void);
		int64_t	get_value(void);
		BSON_int64(int64_t bs_int64, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_int32 ===============

***	Classe representant un entier sur 32bits, sur un int32_t
*/

class BSON_int32: public BSON_element {
	private:
		int32_t		bs_int32;
	public:
		void 	dump_value(void);
		int32_t	get_value(void);
		BSON_int32(int32_t bs_int32, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_string ===============

***	Getter retpurne un char *
*/

class BSON_string: public BSON_element {
	private:
		char	*bs_string;
	public:
		char	*get_value(void);
		void 	dump_value(void);
		BSON_string(char *bs_string, char *name, int32_t elem_size, bson_type_t type);
};

/*
***	=============== BSON_oid ===============

***	Classe representant un ObjectId sur un unsigned char[12],
***	getter retourne un unsigned char * pointant sur le premier
***	charactere du tableau bs_oid
*/

class BSON_oid: public BSON_element {
	private:
		unsigned char		bs_oid[12];
	public:
		void 	dump_value(void);
		unsigned char	*get_value(void);
		BSON_oid(unsigned char *bs_oid, char *name, bson_type_t type);
};

/*
***	=============== BSON_double ===============

***	Classe representant un double. Getter retourne un double.
*/

class BSON_double: public BSON_element {

	private:
		double bs_double;

	public:
		void 	dump_value(void);
		double	get_value(void);
		BSON_double(double *bs_double, char *name, int32_t elem_size, bson_type_t type);
};

#endif
