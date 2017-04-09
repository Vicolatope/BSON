#include "BSON_element.class.hpp"

BSON_element::BSON_element(void *data, char *name, int elem_size, bson_element_type type) {
	switch (type) {
		case BSON_DOUBLE_T:
			this->data = new double;
			*this->data = *data;
			break;
		default:
			break;
	}
}

BSON_element::~BSON_element() {
	std::cout << "Bye";
}
