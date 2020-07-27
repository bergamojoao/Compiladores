/* Nao usar a biblioteca do flex*/
%option noyywrap

%x COMMENT

%{
int newLine=0;
int columns = 1;
int lines = 1;
int tokens = 0;
int i=0;
int lineError=0;
int columnError=0;

%}

%%

"void"					{if(newLine==1){printf("\n");}printf("VOID");tokens++;columns+=strlen(yytext);newLine=1;}
"int"					{if(newLine==1){printf("\n");}printf("INT");tokens++;columns+=strlen(yytext);newLine=1;}
"char"					{if(newLine==1){printf("\n");}printf("CHAR");tokens++;columns+=strlen(yytext);newLine=1;}
"return"				{if(newLine==1){printf("\n");}printf("RETURN");tokens++;columns+=strlen(yytext);newLine=1;}
"break"					{if(newLine==1){printf("\n");}printf("BREAK");tokens++;columns+=strlen(yytext);newLine=1;}
"switch"				{if(newLine==1){printf("\n");}printf("SWITCH");tokens++;columns+=strlen(yytext);newLine=1;}
"case"					{if(newLine==1){printf("\n");}printf("CASE");tokens++;columns+=strlen(yytext);newLine=1;}
"default" 				{if(newLine==1){printf("\n");}printf("DEFAULT");tokens++;columns+=strlen(yytext);newLine=1;}
"do" 					{if(newLine==1){printf("\n");}printf("DO");tokens++;columns+=strlen(yytext);newLine=1;}
"while" 				{if(newLine==1){printf("\n");}printf("WHILE");tokens++;columns+=strlen(yytext);newLine=1;}
"for" 					{if(newLine==1){printf("\n");}printf("FOR");tokens++;columns+=strlen(yytext);newLine=1;}
"if" 					{if(newLine==1){printf("\n");}printf("IF");tokens++;columns+=strlen(yytext);newLine=1;}
"else"					{if(newLine==1){printf("\n");}printf("ELSE");tokens++;columns+=strlen(yytext);newLine=1;}
"typedef"				{if(newLine==1){printf("\n");}printf("TYPEDEF");tokens++;columns+=strlen(yytext);newLine=1;}
"struct" 				{if(newLine==1){printf("\n");}printf("STRUCT");tokens++;columns+=strlen(yytext);newLine=1;}
"+" 					{if(newLine==1){printf("\n");}printf("PLUS");tokens++;columns+=strlen(yytext);newLine=1;}
"-" 					{if(newLine==1){printf("\n");}printf("MINUS");tokens++;columns+=strlen(yytext);newLine=1;}
"*" 					{if(newLine==1){printf("\n");}printf("MULTIPLY");tokens++;columns+=strlen(yytext);newLine=1;}
"/" 					{if(newLine==1){printf("\n");}printf("DIV");tokens++;columns+=strlen(yytext);newLine=1;}
"%" 					{if(newLine==1){printf("\n");}printf("REMAINDER");tokens++;columns+=strlen(yytext);newLine=1;}
"++" 					{if(newLine==1){printf("\n");}printf("INC");tokens++;columns+=strlen(yytext);newLine=1;}
"--" 					{if(newLine==1){printf("\n");}printf("DEC");tokens++;columns+=strlen(yytext);newLine=1;}
"&" 					{if(newLine==1){printf("\n");}printf("BITWISE_AND");tokens++;columns+=strlen(yytext);newLine=1;}
"|" 					{if(newLine==1){printf("\n");}printf("BITWISE_OR");tokens++;columns+=strlen(yytext);newLine=1;}
"~" 					{if(newLine==1){printf("\n");}printf("BITWISE_NOT");tokens++;columns+=strlen(yytext);newLine=1;}
"^" 					{if(newLine==1){printf("\n");}printf("BITWISE_XOR");tokens++;columns+=strlen(yytext);newLine=1;}
"!" 					{if(newLine==1){printf("\n");}printf("NOT");tokens++;columns+=strlen(yytext);newLine=1;}
"&&" 					{if(newLine==1){printf("\n");}printf("LOGICAL_AND");tokens++;columns+=strlen(yytext);newLine=1;}
"||" 					{if(newLine==1){printf("\n");}printf("LOGICAL_OR");tokens++;columns+=strlen(yytext);newLine=1;}
"==" 					{if(newLine==1){printf("\n");}printf("EQUAL");tokens++;columns+=strlen(yytext);newLine=1;}
"!=" 					{if(newLine==1){printf("\n");}printf("NOT_EQUAL");tokens++;columns+=strlen(yytext);newLine=1;}
"<" 					{if(newLine==1){printf("\n");}printf("LESS_THAN");tokens++;columns+=strlen(yytext);newLine=1;}
">" 					{if(newLine==1){printf("\n");}printf("GREATER_THAN");tokens++;columns+=strlen(yytext);newLine=1;}
"<=" 					{if(newLine==1){printf("\n");}printf("LESS_EQUAL");tokens++;columns+=strlen(yytext);newLine=1;}
">=" 					{if(newLine==1){printf("\n");}printf("GREATER_EQUAL");tokens++;columns+=strlen(yytext);newLine=1;}
">>" 					{if(newLine==1){printf("\n");}printf("R_SHIFT");tokens++;columns+=strlen(yytext);newLine=1;}
"<<" 					{if(newLine==1){printf("\n");}printf("L_SHIFT");tokens++;columns+=strlen(yytext);newLine=1;}
"=" 					{if(newLine==1){printf("\n");}printf("ASSIGN");tokens++;columns+=strlen(yytext);newLine=1;}
"+=" 					{if(newLine==1){printf("\n");}printf("ADD_ASSIGN");tokens++;columns+=strlen(yytext);newLine=1;}
"-=" 					{if(newLine==1){printf("\n");}printf("MINUS_ASSIGN");tokens++;columns+=strlen(yytext);newLine=1;}
";" 					{if(newLine==1){printf("\n");}printf("SEMICOLON");tokens++;columns+=strlen(yytext);newLine=1;}
"," 					{if(newLine==1){printf("\n");}printf("COMMA");tokens++;columns+=strlen(yytext);newLine=1;}
":" 					{if(newLine==1){printf("\n");}printf("COLON");tokens++;columns+=strlen(yytext);newLine=1;}
"(" 					{if(newLine==1){printf("\n");}printf("L_PAREN");tokens++;columns+=strlen(yytext);newLine=1;}
")" 					{if(newLine==1){printf("\n");}printf("R_PAREN");tokens++;columns+=strlen(yytext);newLine=1;}
"{" 					{if(newLine==1){printf("\n");}printf("L_CURLY_BRACKET");tokens++;columns+=strlen(yytext);newLine=1;}
"}" 					{if(newLine==1){printf("\n");}printf("R_CURLY_BRACKET");tokens++;columns+=strlen(yytext);newLine=1;}
"[" 					{if(newLine==1){printf("\n");}printf("L_SQUARE_BRACKET");tokens++;columns+=strlen(yytext);newLine=1;}
"]" 					{if(newLine==1){printf("\n");}printf("R_SQUARE_BRACKET");tokens++;columns+=strlen(yytext);newLine=1;}
"?" 					{if(newLine==1){printf("\n");}printf("TERNARY_CONDITIONAL");tokens++;columns+=strlen(yytext);newLine=1;}
"#" 					{if(newLine==1){printf("\n");}printf("NUMBER_SIGN");tokens++;columns+=strlen(yytext);newLine=1;}
"->" 					{if(newLine==1){printf("\n");}printf("POINTER");tokens++;columns+=strlen(yytext);newLine=1;}
"printf" 				{if(newLine==1){printf("\n");}printf("PRINTF");tokens++;columns+=strlen(yytext);newLine=1;}
"scanf" 				{if(newLine==1){printf("\n");}printf("SCANF");tokens++;columns+=strlen(yytext);newLine=1;}
"define" 				{if(newLine==1){printf("\n");}printf("DEFINE");tokens++;columns+=strlen(yytext);newLine=1;}
"exit" 					{if(newLine==1){printf("\n");}printf("EXIT");tokens++;columns+=strlen(yytext);newLine=1;}
[_a-zA-Z][_a-zA-Z0-9]*	{if(newLine==1){printf("\n");}printf("IDENTIFIER(%s)",yytext);tokens++;columns+=strlen(yytext);newLine=1;}
"0"[1-7][0-7]*			{if(newLine==1){printf("\n");}printf("NUM_OCTAL(%s)",yytext);tokens++;columns+=strlen(yytext);newLine=1;}
[0-9]+					{if(newLine==1){printf("\n");}printf("NUM_INTEGER(%s)",yytext);tokens++;columns+=strlen(yytext);newLine=1;}
"0"[x|X][a-fA-F0-9]+	{if(newLine==1){printf("\n");}printf("NUM_HEXA(%s)",yytext);tokens++;columns+=strlen(yytext);newLine=1;}

"//"(.)*("")			{lines++;columns=1;}
\/\/([^\n])* 			{columns+=strlen(yytext);}

\"([^\\\"]|\\.)*\"		{i=0;if(newLine==1){printf("\n");}printf("STRING(");
						while(yytext[i]!='\0'){
							if(i!=0 && i!=strlen(yytext)-1)
								printf("%c",yytext[i]);
							i++;
						}
						printf(")");tokens++;columns+=strlen(yytext);newLine==1;}

'\\?.?'					{i=0;if(newLine==1){printf("\n");}printf("CHARACTER(");
						while(yytext[i]!='\0'){
							if(i!=0 && i!=strlen(yytext)-1)
								printf("%c",yytext[i]);
							i++;
						}
						printf(")");tokens++;columns+=strlen(yytext);newLine==1;}


" "						{columns+=strlen(yytext);}
"\t"        			{columns+=strlen(yytext);}   
"\n"					{lines++;columns=1;}

<INITIAL>{
    "/*"      			{lineError=lines;columnError=columns;columns+=2;}BEGIN(COMMENT);
}

<COMMENT>{
    <<EOF>>   			{if(newLine==1){printf("\n");}printf("error:lexical:%d:%d: unterminated comment",lineError,columnError);newLine==1;}BEGIN(INITIAL);
    "*/"      			{columns+=2;}BEGIN(INITIAL);
    [^*\n]+   			{columns+=strlen(yytext);newLine=1;}
    "*"       			{columns+=strlen(yytext);newLine=1;}
    \n        			{lines++;}
}

.    					{if(newLine==1){printf("\n");}printf("error:lexical:%d:%d: %s",lines,columns,yytext); columns+=strlen(yytext);newLine==1;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
