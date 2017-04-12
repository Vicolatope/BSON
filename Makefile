all:
	g++ srcs/BSON.class.cpp srcs/BSON_element.class.cpp srcs/BSON_document.class.cpp srcs/main.cpp -o bson_dumper -I headers
