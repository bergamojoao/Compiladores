/* Nao usar a biblioteca do flex*/
%option noyywrap

%x COMMENT

%{

int columns = 1;
int lines = 1;
int tokens = 0;
int i=0;

int lineError=0;
int columnError=0;

%}

%%

"void"					{printf("VOID\n");tokens++;columns+=strlen(yytext);}
"int"					{printf("INT\n");tokens++;columns+=strlen(yytext);}
"char"					{printf("CHAR\n");tokens++;columns+=strlen(yytext);}
"return"				{printf("RETURN\n");tokens++;columns+=strlen(yytext);}
"break"					{printf("BREAK\n");tokens++;columns+=strlen(yytext);}
"switch"				{printf("SWITCH\n");tokens++;columns+=strlen(yytext);}
"case"					{printf("CASE\n");tokens++;columns+=strlen(yytext);}
"default" 				{printf("DEFAULT\n");tokens++;columns+=strlen(yytext);}
"do" 					{printf("DO\n");tokens++;columns+=strlen(yytext);}
"while" 				{printf("WHILE\n");tokens++;columns+=strlen(yytext);}
"for" 					{printf("FOR\n");tokens++;columns+=strlen(yytext);}
"if" 					{printf("IF\n");tokens++;columns+=strlen(yytext);}
"else"					{printf("ELSE\n");tokens++;columns+=strlen(yytext);}
"typedef"				{printf("TYPEDEF\n");tokens++;columns+=strlen(yytext);}
"struct" 				{printf("STRUCT\n");tokens++;columns+=strlen(yytext);}
"+" 					{printf("PLUS\n");tokens++;columns+=strlen(yytext);}
"-" 					{printf("MINUS\n");tokens++;columns+=strlen(yytext);}
"*" 					{printf("MULTIPLY\n");tokens++;columns+=strlen(yytext);}
"/" 					{printf("DIV\n");tokens++;columns+=strlen(yytext);}
"%" 					{printf("REMAINDER\n");tokens++;columns+=strlen(yytext);}
"++" 					{printf("INC\n");tokens++;columns+=strlen(yytext);}
"--" 					{printf("DEC\n");tokens++;columns+=strlen(yytext);}
"&" 					{printf("BITWISE_AND\n");tokens++;columns+=strlen(yytext);}
"|" 					{printf("BITWISE_OR\n");tokens++;columns+=strlen(yytext);}
"~" 					{printf("BITWISE_NOT\n");tokens++;columns+=strlen(yytext);}
"^" 					{printf("BITWISE_XOR\n");tokens++;columns+=strlen(yytext);}
"!" 					{printf("NOT\n");tokens++;columns+=strlen(yytext);}
"&&" 					{printf("LOGICAL_AND\n");tokens++;columns+=strlen(yytext);}
"||" 					{printf("LOGICAL_OR\n");tokens++;columns+=strlen(yytext);}
"==" 					{printf("EQUAL\n");tokens++;columns+=strlen(yytext);}
"!=" 					{printf("NOT_EQUAL\n");tokens++;columns+=strlen(yytext);}
"<" 					{printf("LESS_THAN\n");tokens++;columns+=strlen(yytext);}
">" 					{printf("GREATER_THAN\n");tokens++;columns+=strlen(yytext);}
"<=" 					{printf("LESS_EQUAL\n");tokens++;columns+=strlen(yytext);}
">=" 					{printf("GREATER_EQUAL\n");tokens++;columns+=strlen(yytext);}
">>" 					{printf("R_SHIFT\n");tokens++;columns+=strlen(yytext);}
"<<" 					{printf("L_SHIFT\n");tokens++;columns+=strlen(yytext);}
"=" 					{printf("ASSIGN\n");tokens++;columns+=strlen(yytext);}
"+=" 					{printf("ADD_ASSIGN\n");tokens++;columns+=strlen(yytext);}
"-=" 					{printf("MINUS_ASSIGN\n");tokens++;columns+=strlen(yytext);}
";" 					{printf("SEMICOLON\n");tokens++;columns+=strlen(yytext);}
"," 					{printf("COMMA\n");tokens++;columns+=strlen(yytext);}
":" 					{printf("COLON\n");tokens++;columns+=strlen(yytext);}
"(" 					{printf("L_PAREN\n");tokens++;columns+=strlen(yytext);}
")" 					{printf("R_PAREN\n");tokens++;columns+=strlen(yytext);}
"{" 					{printf("L_CURLY_BRACKET\n");tokens++;columns+=strlen(yytext);}
"}" 					{printf("R_CURLY_BRACKET\n");tokens++;columns+=strlen(yytext);}
"[" 					{printf("L_SQUARE_BRACKET\n");tokens++;columns+=strlen(yytext);}
"]" 					{printf("R_SQUARE_BRACKET\n");tokens++;columns+=strlen(yytext);}
"?" 					{printf("TERNARY_CONDITIONAL\n");tokens++;columns+=strlen(yytext);}
"#" 					{printf("NUMBER_SIGN\n");tokens++;columns+=strlen(yytext);}
"->" 					{printf("POINTER\n");tokens++;columns+=strlen(yytext);}
"printf" 				{printf("PRINTF\n");tokens++;columns+=strlen(yytext);}
"scanf" 				{printf("SCANF\n");tokens++;columns+=strlen(yytext);}
"define" 				{printf("DEFINE\n");tokens++;columns+=strlen(yytext);}
"exit" 					{printf("EXIT\n");tokens++;columns+=strlen(yytext);}
[_a-zA-Z][_a-zA-Z0-9]*	{printf("IDENTIFIER(%s)\n",yytext);tokens++;columns+=strlen(yytext);}
"0"[1-7][0-7]*			{printf("NUM_OCTAL(%s)\n",yytext);tokens++;columns+=strlen(yytext);}
[0-9]+					{printf("NUM_INTEGER(%s)\n",yytext);tokens++;columns+=strlen(yytext);}
"0"[x|X][a-fA-F0-9]+	{printf("NUM_HEXA(%s)\n",yytext);tokens++;columns+=strlen(yytext);}

"//"(.)*("\n")			{lines++;columns=1;}
\/\/([^\n])* 			{columns+=strlen(yytext);}

\"([^\\\"]|\\.)*\"		{i=0;printf("STRING(");
						while(yytext[i]!='\0'){
							if(i!=0 && i!=strlen(yytext)-1)
								printf("%c",yytext[i]);
							i++;
						}
						printf(")\n");tokens++;columns+=strlen(yytext);}

'\\?.?'					{i=0;printf("CHARACTER(");
						while(yytext[i]!='\0'){
							if(i!=0 && i!=strlen(yytext)-1)
								printf("%c",yytext[i]);
							i++;
						}
						printf(")\n");tokens++;columns+=strlen(yytext);}


" "						{columns+=strlen(yytext);}
"\t"        			{columns+=strlen(yytext);}   
"\n"					{lines++;columns=1;}

<INITIAL>{
    "/*"      			{lineError=lines;columnError=columns;columns+=2;}BEGIN(COMMENT);
}

<COMMENT>{
    <<EOF>>   			{printf("error:lexical:%d:%d: unterminated comment\n",lineError,columnError);}BEGIN(INITIAL);
    "*/"      			{columns+=2;}BEGIN(INITIAL);
    [^*\n]+   			{columns+=strlen(yytext);}
    "*"       			{columns+=strlen(yytext);}
    \n        			{lines++;}
}

.    					{printf("error:lexical:%d:%d: %s\n",lines,columns,yytext); columns+=strlen(yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
