#ifndef _BSON_CLASS_H_
	# define _BSON_CLASS_H_
	#include <vector>
	#include <string>
	#include "BSON_element.class.hpp"

	typedef std::vector<char> char_vec_t;
	typedef BSON_element bs_element_t;

	typedef struct s_element {
		bs_element_t *element;
		struct s_element *next_e;
	}				bs_list_elem_t;

	typedef struct	s_document {
		bs_list_elem_t*	element_list;
		struct s_document*	next_d;
	}				bs_document_t;

	class BSON {
		private:
			bs_document_t*	document_list;
			bs_element_t *handle_double(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_string(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_embedded_document(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_array(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_binary_data(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_undefined(char_vec_t bson_data, int& current_index);
			bs_element_t *handle_object_id(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_boolean(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_UTC_datetime(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_null_value(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_regular_expression(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_db_pointer(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_javascript_code(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_symbol(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_javascript_code_w_scope(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_int32(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_timestamp(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_int64(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_decimal128(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_min_key(char_vec_t bson_data, int& current_index);
			// bs_element_t handle_max_key(char_vec_t bson_data, int& current_index);
			void element_dispatcher(char_vec_t bson_data, int32_t element_size, int current_index);
			bs_document_t *new_document(void);
			void add_document_to_list(bs_document_t *new_document);
			bs_list_elem_t	*new_element_list_item(bs_element_t *element);
			void add_element_to_list(bs_list_elem_t **begin_list, bs_list_elem_t *new_elem);
		public:
			void json_dump(void);
			BSON(char_vec_t bson_data, int total_size);
			~BSON();
	};

#endif
