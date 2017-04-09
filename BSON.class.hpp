#ifndef _BSON_CLASS_H_
	# define _BSON_CLASS_H_
	#include <vector>
	#include <string>
	#include "BSON_element.class.hpp"

	typedef std::vector<char> char_vec_t;
	typedef BSON_element b_element;

	class BSON {
		private:
			void handle_double(char_vec_t bson_data, int& current_index);
			// b_element handle_string(char_vec_t bson_data, int& current_index);
			// b_element handle_(char_vec_t bson_data, int& current_index);
			// b_element handle_embedded_document(char_vec_t bson_data, int& current_index);
			// b_element handle_array(char_vec_t bson_data, int& current_index);
			// b_element handle_binary_data(char_vec_t bson_data, int& current_index);
			// b_element handle_undefined(char_vec_t bson_data, int& current_index);
			void handle_object_id(char_vec_t bson_data, int& current_index);
			// b_element handle_boolean(char_vec_t bson_data, int& current_index);
			// b_element handle_UTC_datetime(char_vec_t bson_data, int& current_index);
			// b_element handle_null_value(char_vec_t bson_data, int& current_index);
			// b_element handle_regular_expression(char_vec_t bson_data, int& current_index);
			// b_element handle_db_pointer(char_vec_t bson_data, int& current_index);
			// b_element handle_javascript_code(char_vec_t bson_data, int& current_index);
			// b_element handle_symbol(char_vec_t bson_data, int& current_index);
			// b_element handle_javascript_code_w_scope(char_vec_t bson_data, int& current_index);
			// b_element handle_int32(char_vec_t bson_data, int& current_index);
			// b_element handle_timestamp(char_vec_t bson_data, int& current_index);
			// b_element handle_int64(char_vec_t bson_data, int& current_index);
			// b_element handle_decimal128(char_vec_t bson_data, int& current_index);
			// b_element handle_min_key(char_vec_t bson_data, int& current_index);
			// b_element handle_max_key(char_vec_t bson_data, int& current_index);
			void element_dispatcher(char_vec_t bson_data, int32_t element_size, int current_index);
		public:
			BSON(char_vec_t bson_data, int total_size);
			~BSON();
	};

#endif
