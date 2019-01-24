/*
Compile: make secret_message
Run: ./secret_message
*/

#include "base.h"

//todo: Write decode method
String decode(String text , int verschiebung) {
	String copied_text = s_copy(text);
	int new_verschiebung = verschiebung % 26;
	for (int i = 0 ; i < s_length(text) ; i++) {
		char get_char = s_get(copied_text , i);
		if (get_char >= 'a' && get_char <= 'z') {
			get_char -= new_verschiebung;
			if (get_char < 'a') get_char += 26;
		}
		else if (get_char >= 'A' && get_char <= 'Z') {
			get_char -= new_verschiebung;
			if (get_char < 'A') get_char += 26; 
		}
		s_set(copied_text , i , get_char);
	}
	return copied_text;
}

//todo: Write test method for decode
void decode_test() {
	test_equal_s(decode("apww" , 7) , "tipp");
	test_equal_s(decode("fF" , 83) , "aA");
}
//todo: Write encode method
String encode(String text , int verschiebung) {
	return decode(text , verschiebung);
}

//todo: Write test method for encode
void encode_test() {
	test_equal_s(encode("xYzA" , 0) , "xYzA");
	test_equal_s(encode("fg" , 1) , "ab");
}

int main(void){
	//todo: Decode this message to get a hint for part f) 
	
	String secret_message = "Apww: Dhz pu kpl lpul Ypjoabun nloa, nloa hbjo pu kpl huklyl. Kpl Svlzbun whzza pu lpul Glpsl.";
	
	printsln(decode(secret_message , 7));
	printsln(encode(decode(secret_message , 7) , 7));
	
	//call test functions
	decode_test();
	encode_test();
	return 0;
}