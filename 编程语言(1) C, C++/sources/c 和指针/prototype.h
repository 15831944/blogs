/************************
	function prototype
************************/
int          specified_format_output(char *format_string, char const *digit_string);
void         decrypt_key(char *data, char const *key);
void         encrypt_key(char *data, char const *key);
int          delete_repeated_chars(char *key);
int          prepare_key(char *key);
int          string_word_count(char *string, char *word);
int          palindrome_v2(char *string);
int          string_count_chars(char const *str, char const *chars);
void         char_type_count(void);
int          compare_integers(void const *a, void const *b);
void         palindrome(char *buffer, int SIZE);
int          lookup_keyword(char const * const desired_word, char const *keyword_table[], int const size);
int          max_value(int a, ...);
void         int_to_ascii(unsigned int );
int          delete_substring(char *, char const *);
char const   *stringpointbreak(char const *, char const *);
int          store_bit_field(int, int, unsigned, unsigned);
void         set_bit(char *, unsigned);
unsigned int reverse_bits(unsigned int);
void         Encrypt(void);
void         UpperToLowerCase(void);
