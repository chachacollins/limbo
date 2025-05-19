#include <stdio.h>
#include <string.h>
#include "lexer.h"

void repl(void)
{
    char buffer[1024] = {0};
    while(1)
    {
        printf(">> ");
        if(!fgets(buffer, sizeof(buffer), stdin))
        {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        init_lexer(buffer);
        Token tok;
        do {
            tok = next_token();
            printf("%.*s : %d\n", tok.len, tok.start, tok.type);
        } while(tok.type != TOK_EOF);
    }
}


int main(void)
{
    repl();
    return 0;
}
