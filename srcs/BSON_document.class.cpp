#include "bson.hpp"

BSON_document::BSON_document(void) {
    this->element_list = NULL;
}

bs_list_elem_t	*BSON_document::new_element_list_item(BSON_element *element) {
	bs_list_elem_t *new_list_item;

	new_list_item = new bs_list_elem_t;
	new_list_item->next_e = NULL;
	new_list_item->element = element;
	return new_list_item;
}

void BSON_document::add_element_to_list(BSON_element *bs_elem) {
	bs_list_elem_t	*tmp_element;
    bs_list_elem_t  *new_elem;

    new_elem = this->new_element_list_item(bs_elem);
	if (this->element_list == NULL) {
		this->element_list = new_elem;
	} else {
		tmp_element = this->element_list;
		while (tmp_element && tmp_element->next_e) {
			tmp_element = tmp_element->next_e;
		}
		if (tmp_element && !tmp_element->next_e) {
			tmp_element->next_e = new_elem;
		}
	}
}
void BSON_document::dump_document(void) {
	bs_list_elem_t	*tmp_elm_item;

    tmp_elm_item = this->element_list;
    while (tmp_elm_item) {
        tmp_elm_item->element->dump_value();
        tmp_elm_item = tmp_elm_item->next_e;
        if (tmp_elm_item) {
            std::cout << ",";
        }
    }
}

BSON_element    *BSON_document::get_element_by_name(char *name) {
    BSON_element    *match;
    bs_list_elem_t  *tmp_elem;

    tmp_elem = this->element_list;
    while (tmp_elem) {
        match = tmp_elem->element;
        if (!strcmp(match->get_name(), name)) {
            return match;
        } else {
            match = 0;
        }
        tmp_elem = tmp_elem->next_e;
    }
    return NULL;
}
