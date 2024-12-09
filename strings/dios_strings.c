/**
 * 	This code was provided by Prof. McKee on Canvas
 */

int str_len(char* s);

/* BEGIN */
int is_space(char c) {
	return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}

char *ltrim(char *s) {
	while(is_space(*s)) s++;
	return s;
}

char *rtrim(char *s) {
	char* back = s + str_len(s);
	while (is_space(*--back));
	*(back + 1) = '\0';
	return s;
}

char *trim(char *s) {
	return rtrim(ltrim(s));
}

int strcmp(const char* s1, const char* s2) {
	while(*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*) s2;
}

/* END */

int str_len(char* s) {
	int i = 0;
	while(s[i] != 0) {
		i++;
	}
	return i;
}
