#ifndef LEXER_H
#define LEXER_H

typedef enum {
    // Literals
    TOK_NUM,
    TOK_STRING,
    TOK_IDENT,
    // Keywords
    TOK_LET,
    TOK_MUT,
    TOK_FN,
    TOK_RETURN,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_CLASS,
    TOK_THIS,
    TOK_INIT,
    TOK_IMPORT,
    TOK_TRUE,
    TOK_FALSE,
    TOK_NIL,
    TOK_WRITE,
    // Logical operators
    TOK_AND,        // and
    TOK_OR,         // or
    TOK_NOT,        // not
    // Comparison operators
    TOK_EQUAL,          // =
    TOK_EQUAL_EQUAL,    // ==
    TOK_BANG_EQUAL,     // !=
    TOK_BANG,           // !=
    TOK_LESS,           // <
    TOK_LESS_EQUAL,     // <=
    TOK_GREATER,        // >
    TOK_GREATER_EQUAL,  // >=
    // Arithmetic operators
    TOK_PLUS,       // +
    TOK_MINUS,      // -
    TOK_MULT,       // *
    TOK_DIV,        // /
    // Punctuation
    TOK_DOT,        // .
    TOK_COMMA,      // ,
    TOK_SEMI,       // ;
    TOK_COLON,      // :
    // Delimiters
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
    TOK_LBRACE,     // {
    TOK_RBRACE,     // }
    TOK_LBRACKET,   // [
    TOK_RBRACKET,   // ]
    // Special tokens
    TOK_ILLEGAL,
    TOK_EOF,
} TokenType;

typedef struct {
    TokenType    type;
    const char*  start; 
    unsigned int len;
    unsigned int line;
} Token;

void init_lexer(const char* source);
Token next_token(void);

#endif // LEXER_H
