/* Nao usar a biblioteca do flex*/
%option noyywrap

%x COMMENT

%{
	int lines=1;
	int blankLines=0;
	int commentLines=0;
	int nbncLines=0;
	int semiColons=0;
	int directives=0;

	int aux=0;
%}

%%

";"						{semiColons++;aux++;}
"#include"|"#define"	{directives++;aux++;}
"//"(.)*("")			{commentLines++;aux++;}
"\n"					{lines++;if(aux==0){blankLines++;}else{nbncLines++;};aux=0;}

<INITIAL>{
    "/*"      			{commentLines++;aux++;}BEGIN(COMMENT);
}
<COMMENT>{
    <<EOF>>   			BEGIN(INITIAL);
    "*/"      			{aux++;}BEGIN(INITIAL);
	[^*\n]+   			{aux++;}
    "*"       			{aux++;}
    \n        			{lines++;commentLines++;if(aux==0){blankLines++;};aux=0;}

}

.						{aux++;continue;}
<<EOF>>					{if(aux==0){blankLines++;}else{nbncLines++;}return 0;}

%%

int main(int argc, char **argv)
{
	int i,totalLines=0,totalBlankLines=0,totalCommentLines=0;
	int totalNbnbLines=0,totalSemiColons=0,totalDirectives=0;
	printf(" total    blank lines w/   nb, nc   semi- preproc. file\n");
	printf(" lines    lines comments    lines  colons  direct.\n");
	printf("------+--------+--------+--------+-------+--------+----\n");
	for(i=1;i<argc;i++){
		yyin = fopen(argv[i],"r");
		yylex();
		printf("%6d%9d%9d%9d%8d%9d %s\n",lines,blankLines,commentLines,nbncLines,semiColons,directives,argv[i]);
		totalLines+=lines;
		totalBlankLines+=blankLines;
		totalCommentLines+=commentLines;
		totalNbnbLines+=nbncLines;
		totalSemiColons+=semiColons;
		totalDirectives+=directives;
		lines=1;
		blankLines=0;
		commentLines=0;
		nbncLines=0;
		semiColons=0;
		directives=0;
		aux=0;
	}
	printf("%6d%9d%9d%9d%8d%9d total",totalLines,totalBlankLines,totalCommentLines,totalNbnbLines,totalSemiColons,totalDirectives);
	return 0;
}
