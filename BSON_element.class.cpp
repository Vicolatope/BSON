#include "BSON_element.class.hpp"

/*
**	BSON_element constructeurs => utilisation du polymorphisme en cpp pour avoir un constructeur
***	propre a chaque type
*/

BSON_element::BSON_element(double *bs_double, char *name, int elem_size, bson_element_type type)
:  size(elem_size), type(type), bs_double(*bs_double), name(strdup(name)) {
	std::cout << "created a double" << std::endl << "named : " << name << std::endl;
}

BSON_element::BSON_element(unsigned char *bs_oid, char *name, int elem_size, bson_element_type type)
: size(elem_size), type(type), name(strdup(name)) {
	memcpy(&this->bs_oid[0], bs_oid, 12);
	std::cout << "created a oid" << std::endl << "named : " << name << std::endl;
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
		default:
			break;
	}
}

void BSON_element::json_dump_element(void) {
	std::cout << "\"" << this->name << "\":";
	this->dump_value();
}
