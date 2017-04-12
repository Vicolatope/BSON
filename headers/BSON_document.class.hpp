#ifndef _BSON_DOCUMENT_CLASS_HPP
# define _BSON_DOCUMENT_CLASS_HPP

class BSON_element;
#include "BSON_element.class.hpp"

typedef BSON_element bs_element_t;

class BSON_document {
    private:
        bs_list_elem_t *element_list;
    public:
		BSON_document(void);
        void   	add_element_to_list(BSON_element *new_elem);
        bs_list_elem_t 	*new_element_list_item(BSON_element *element);
		void 	dump_document(void);
		BSON_element	*get_element_by_name(char *name);
};

#endif
