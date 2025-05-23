#include "lexer.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
    const char*  start;
    const char*  current;
    unsigned int line;
} Lexer;

static Lexer lexer = {0};

void init_lexer(const char* source)
{
    lexer.start = source;
    lexer.current = source;
    lexer.line = 1;
}

static bool is_at_end(void)
{
    return *lexer.current == '\0';
}

static char advance(void)
{
    if (is_at_end()) return '\0';
    return *lexer.current++;
}

static Token make_token(TokenType type)
{
    return (Token) {
        .start = lexer.start,
        .len   = (unsigned int)(lexer.current - lexer.start),
        .line  = lexer.line, 
        .type  = type,
    };
}

static char peek(void)
{
    return *lexer.current;
}

static char peek_next(void)
{
    if (is_at_end()) return '\0';
    return lexer.current[1];
}

static void skip_whitespace(void)
{
    for (;;) 
    {
        char c = peek();
        switch (c) 
        {
            case '\t':
            case '\r':
            case ' ':
                advance();
                break;
            case '\n':
                lexer.line++;
                advance();
                break;
            default:
                return;
        }
    }
}

static bool is_num(char c)
{
    return (c >= '0' && c <= '9');
}

static bool is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c == '_') || (c >= 'a' && c <= 'z'); 
}

static Token read_number(void)
{
    while (is_num(peek())) advance();
    if (peek() == '.' && is_num(peek_next())) 
    {
        advance();
        while (is_num(peek())) advance();
    }

    return make_token(TOK_NUM);
}

static TokenType check_keyword(int start, int len, const char* rest, TokenType type)
{
    if (start + len == (int)(lexer.current - lexer.start) && 
        memcmp(lexer.start + start, rest, len) == 0) {
        return type;
    }
    return TOK_IDENT;
}

static TokenType identifier_type(void)
{
    switch (lexer.start[0]) 
    {
        case 'a': return check_keyword(1, 2, "nd", TOK_AND);
        case 'c': return check_keyword(1, 4, "lass", TOK_CLASS);
        case 'e': return check_keyword(1, 3, "lse", TOK_ELSE);
        case 'f':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'a': return check_keyword(2, 3, "lse", TOK_FALSE);
                    case 'n': return check_keyword(2, 0, "", TOK_FN);
                }
            }
            break;
        case 'i':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'f': return check_keyword(2, 0, "", TOK_IF);
                    case 'm': return check_keyword(2, 4, "port", TOK_IMPORT);
                    case 'n': return check_keyword(2, 2, "it", TOK_INIT);
                }
            }
            break;
        case 'l': return check_keyword(1, 2, "et", TOK_LET);
        case 'm': return check_keyword(1, 2, "ut", TOK_MUT);
        case 'n':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'i': return check_keyword(2, 1, "l", TOK_NIL);
                    case 'o': return check_keyword(2, 1, "t", TOK_NOT);
                }
            }
            break;
        case 'o': return check_keyword(1, 1, "r", TOK_OR);
        case 'r': return check_keyword(1, 5, "eturn", TOK_RETURN);
        case 't':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'h': return check_keyword(2, 2, "is", TOK_THIS);
                    case 'r': return check_keyword(2, 2, "ue", TOK_TRUE);
                }
            }
            break;
        case 'w':
            if (lexer.current - lexer.start > 1) {
                switch (lexer.start[1]) {
                    case 'h': return check_keyword(2, 3, "ile", TOK_WHILE);
                    case 'r': return check_keyword(2, 3, "ite", TOK_WRITE);
                }
            }
            break;
        default: return TOK_IDENT;
    }
    return TOK_IDENT;
}

static Token read_ident(void)
{
    while (is_alpha(peek()) || is_num(peek())) advance();
    return make_token(identifier_type());
}

static Token string(void)
{
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') lexer.line++;
        advance();
    }
    if (is_at_end()) {
        return make_token(TOK_ILLEGAL);
    }
    advance();
    return make_token(TOK_STRING);
}

static bool match(char c)
{
    if (is_at_end() || peek() != c) {
        return false;
    }
    advance();
    return true;
}

Token next_token(void)
{
    skip_whitespace();
    lexer.start = lexer.current;

    if (is_at_end()) 
    {
        return make_token(TOK_EOF);
    }

    char c = advance();

    if (is_num(c)) return read_number();
    if (is_alpha(c)) return read_ident();

    switch (c) 
    {
        case ';': return make_token(TOK_SEMI);
        case '+': return make_token(TOK_PLUS);
        case '-': return make_token(TOK_MINUS);
        case '/': return make_token(TOK_DIV);
        case '*': return make_token(TOK_MULT);
        case '=': return make_token(match('=') ? TOK_EQUAL_EQUAL : TOK_EQUAL);
        case '!': return make_token(match('=') ? TOK_BANG_EQUAL : TOK_BANG);
        case '<': return make_token(match('=') ? TOK_LESS_EQUAL : TOK_LESS);
        case '>': return make_token(match('=') ? TOK_GREATER_EQUAL : TOK_GREATER);
        case '.': return make_token(TOK_DOT);
        case ',': return make_token(TOK_COMMA);
        case '(': return make_token(TOK_LPAREN);
        case ')': return make_token(TOK_RPAREN);
        case '{': return make_token(TOK_LBRACE);
        case '}': return make_token(TOK_RBRACE);
        case '[': return make_token(TOK_LBRACKET);
        case ']': return make_token(TOK_RBRACKET);
        case '"': return string();
        case ':': return make_token(TOK_COLON);
        default: return make_token(TOK_ILLEGAL);
    }
}
