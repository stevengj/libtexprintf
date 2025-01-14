#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "boxes.h"
#include "parser.h"
#include "drawchars.h"
#include "stringutils.h"
#include "drawbox.h"
#include "mapunicode.h"
#include "error.h"


Style STYLE_UNI={
	/* plain brackets */
	{0x28   ,0x0239D,0x0239C,0x0239B}, // single, lower, extender, upper
	{0x29   ,0x023A0,0x0239F,0x0239E}, 
	{0x5B   ,0x023A3,0x023A2,0x023A1},
	{0x5D   ,0x023A6,0x023A5,0x023A4},
	{0x023A2,0x023A2,0x023A2,0x023A2},
	{0x02016,0x02551,0x02551,0x02551},
	/* floor/ceil and up/down arrows */
	{0x0230A,0x023A3,0x023A2,0x023A2}, // single, lower, extender, upper
	{0x0230B,0x023A6,0x023A5,0x023A5},
	{0x02308,0x023A2,0x023A2,0x023A1},
	{0x02309,0x023A5,0x023A5,0x023A4},
	{0x02191,0x023A2,0x023A2,0x025B2}, // single, lower, extender, extender
	{0x021D1,0x02551,0x02551,0x025B2},
	{0x02193,0x025BC,0x023A2,0x023A2}, // single, extender, extender, upper
	{0x021D3,0x025BC,0x02551,0x02551},
	{0x02195,0x025BC,0x023A2,0x025B2}, // single, lower, extender, upper
	{0x021D5,0x025BC,0x02551,0x025B2},
	/* symmetrical brackets (for use with SymBrac)*/
	{0x7B   ,0x023A9,0x023A8,0x023AA,0x023A7}, // single, lower, center, extender, upper
	{0x7D   ,0x023AD,0x023AC,0x023AE,0x023AB}, // single, lower, center, extender, upper
	/* angle brackets (for use with AngleBrac) */
	{0x02572,0x02571}, // downward, upward
	0x02571,    // forward slash
	0x02572,	   // backward slash
	/* fraction, overline, underline */ 
	0x02500,
	0x02581,
	0x02500,
	/* array characters 
	 *                     0      1      2      3      4      5      6      7      8      9      10
	 *                     │      ─      ┌      ┬      ┐      ├      ┼      ┤      └      ┴      ┘       */
	{0x2502,0x2500,0x250C,0x252C,0x2510,0x251C,0x253C,0x2524,0x2514,0x2534,0x2518},
	/* integrals and sqrt */
	{0x02572,0x02502,0x0250C,0x02500,0x02510}, // downward diagonal, vertical, left top corner, horizontal, right top corner
	{0x02321,0x023AE,0x02320}, // bottom, extender, top
	{0x0222B,0x0222C,0x0222D,0x022EF}, // single, double, tripple, dots
	{0x02E26,0x02E27}, // quasi-circle
	{0x0222E,0x0222F,0x02230,0x022EF}, // single, double, tripple, dots
	/* row mayor character arrays for drawing large symbols */
	{2,4,0x023BA,0x023BA,0x02571,0x00020,0x02572,0x00020,0x023AF,0x023AF}, // width, height, start lower left, end upper right
	{3,2,0x02502,0x00020,0x02502,0x0252C,0x02500,0x0252C}, // width, height, start lower left, end upper right
};
Style STYLE_ASC={
	/* plain brackets */
	{0x28   ,'\\' ,'|','/'}, // single, lower, extender, upper
	{0x29   ,'/','|','\\'}, 
	{0x5B   ,'+','|','+'},
	{0x5D   ,'+','|','+'},
	{'|','|','|','|'},
	{0x02016,0x02551,0x02551,0x02551}, // no reasonable ASCII version
	/* floor/ceil and up/down arrows */
	{0x0230A,0x023A3,0x023A2,0x023A2}, // single, lower, extender, upper// no reasonable ASCII version
	{0x0230B,0x023A6,0x023A5,0x023A5},
	{0x02308,0x023A2,0x023A2,0x023A1},
	{0x02309,0x023A5,0x023A5,0x023A4},
	{0x02191,0x023A2,0x023A2,0x025B2}, // single, lower, extender, extender
	{0x021D1,0x02551,0x02551,0x025B2},
	{0x02193,0x025BC,0x023A2,0x023A2}, // single, extender, extender, upper
	{0x021D3,0x025BC,0x02551,0x02551},
	{0x02195,0x025BC,0x023A2,0x025B2}, // single, lower, extender, upper
	{0x021D5,0x025BC,0x02551,0x025B2},	
	/* symmetrical brackets (for use with SymBrac)*/
	{0x7B   ,'\\','<','|','/'}, // single, lower, center, extender, upper
	{0x7D   ,'/','>','|','\\'}, // single, lower, center, extender, upper
	/* angle brackets (for use with AngleBrac) */
	{'\\','/'}, // downward, upward
	'/',    // forward slash
	'\\',	   // backward slash
	/* fraction, overline, underline */ 
	'-',
	'_',
	'-',
	/* array characters 
	 *0      1      2      3      4      5      6      7      8      9      10
	 *│      ─      ┌      ┬      ┐      ├      ┼      ┤      └      ┴      ┘       */
	{'|',   '-',   '+',   '+',   '+',   '+',   '+',   '+',   '+',    '+',  '+'},
	/* integrals and sqrt */
	{'\\','|','_','_','_'}, // downward diagonal, vertical, left top corner, horizontal, right top corner
	{'/','|','/'}, // bottom, extender, top
	{0x0222B,0x0222C,0x0222D,0x022EF}, // single, double, tripple, dots
	{'(',')'}, // quasi-circle
	{0x0222E,0x0222F,0x02230,0x022EF}, // single, double, tripple, dots
	/* row mayor character arrays for drawing large symbols */
	{2,3,'/','_','\\',' ','_','_'}, // width, height, start lower left, end upper right
	{3,2,'|',' ','|','+','-','+'}, // width, height, start lower left, end upper right
};


void ParseStringRecursive(char *B, box *parent, int Font);
void ParseStringInBox(char *B, box *parent, int Font);
int RootFont;
Style *style=&STYLE_UNI;
void AddScripts(char *subscript, char *superscript, box *b, int limits, int Font)
/* adds sub and/or super scripts to a box */
{
	int *xy;
	int Nc=1;
	int w,h, yoff=0;
	int bi=1,i;
	
	if (!subscript&&!superscript)
		return;
	/* get the size of box b */
	BoxPos(b);
	h=b->h;
	w=b->w;
	Nc+=(subscript!=NULL);
	Nc+=(superscript!=NULL);
	
	/* put box b in a posbox */
	/* the posbox will have a maximum of 3 children
	 * one original box
	 * one subscript box
	 * one superscript box
	 */
	xy=calloc(6, sizeof(int));	
	if (BoxInBox(b, B_POS, (void *)xy))
		return;/*BoxInBox failed, abort AddScripts */
	
	/* now b points to a posbox of which the old b is (currently the only) child */
	
	b->yc=b->child[b->Nc-1].yc; /* inherit the baseline */
	b->Y=FIX; /* fix it */
	if (subscript)
	{
		int *Ncol;		
		/* create a line box for the subscript */
		Ncol=malloc(sizeof(int));
		Ncol[0]=0;
		AddChild(b, B_LINE, (void *)Ncol);		
		/* parse the subscript into this line box */
		ParseStringRecursive(subscript, b->child+b->Nc-1, Font);
		b->S=INIT;

		BoxPos(b);
		
		/* shift the original box up by the height of the posbox */
		xy[0]=0;
		yoff+=b->child[bi].h;
		xy[1]=yoff;
		if (!limits)
			xy[bi*2]=w;
		else
		{
			xy[bi*2]=(w-b->child[bi].w)/2;
			if (xy[bi*2]<0)
			{
				for (i=0;i<bi;i++)
					xy[2*i]=-xy[bi*2];
				xy[bi*2]=0;
				w=b->child[bi].w;
			}
		}
		xy[bi*2+1]=0;
		bi++;
		b->yc+=b->child[b->Nc-1].h;
		
	}
	if (superscript)
	{
		int *Ncol;		
		/* create a line box for the subscript */
		Ncol=malloc(sizeof(int));
		Ncol[0]=0;
		AddChild(b, B_LINE, (void *)Ncol);		
		/* parse the superscript box into this line box */
		ParseStringRecursive(superscript, b->child+b->Nc-1, Font);
		b->S=INIT;

		BoxPos(b);
		/* no need to shift the original box */
		
		if (!limits)
			xy[bi*2]=w;
		else
		{
			xy[bi*2]=(w-b->child[bi].w)/2;
			if (xy[bi*2]<0)
			{
				for (i=0;i<bi;i++)
					xy[2*i]=-xy[bi*2];
				xy[bi*2]=0;
				w=b->child[bi].w;
			}
		}
		xy[bi*2+1]=xy[1]+h;
	}
	b->S=INIT;
	BoxPos(b);
	BoxSetState(b, SIZEKNOWN);
}

/* The following comment line lets the gen_errorflags.sh script generate appropriate error flags and messages */
// ERRORFLAG ERRSCALEDELPOSBOX  "Variable size delimiters need a posbox"
/* scalable Delimiters */
void Brac(box *posbox, int h, int chars[])
/* make regular brackets (a) |a| [a] ‖a‖ */
{
	int *xy;
	int i;
	
	if (posbox->T!=B_POS)
	{		
		AddErr(ERRSCALEDELPOSBOX);
		return;
	}
	if (h<1)
		h=1;
	posbox->content=realloc(posbox->content, (2*(h+posbox->Nc))*sizeof(int));
	xy=(int *)posbox->content;
	xy[0]=0;
	xy[1]=0;		
	if (h==1)
	{
		AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[0])); /* single */
		return;
	}
	
	AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[1])); /* lower */	
	for (i=1;i<h-1;i++)
	{			
		AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[2])); /* extender */
		xy[2*i]=0;
		xy[2*i+1]=i;
	}	
	AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[3])); /* upper */
	xy[2*h-2]=0;
	xy[2*h-1]=h-1;
}

void SymBrac(box *posbox, int h, int chars[])
/* symmetrical bracket with a center char {a}*/
{
	int *xy;
	int i;
	if (posbox->T!=B_POS)
	{
		AddErr(ERRSCALEDELPOSBOX);
		return;
	}
	if (h%2!=1)
		h=h+1;
	posbox->content=realloc(posbox->content, (2*(h+posbox->Nc))*sizeof(int));
	xy=(int *)posbox->content;
	xy[0]=0;
	xy[1]=0;		
	if (h==1)
	{
		AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[0])); /* bracket */
		return;
	}
	AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[1])); // lower
	for (i=1;i<h-1;i++)
	{
		if (i==h/2)
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[2])); // center
		else
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[3])); // extender
		xy[2*i]=0;
		xy[2*i+1]=i;
	}
	AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[4])); // top
	xy[2*h-2]=0;
	xy[2*h-1]=h-1;
}

void AngleBrac(box *posbox, int h, int chars[], char lr)
/* make a scaling angle bracket <a>*/
{
	int *xy;
	int i;
	if (posbox->T!=B_POS)
	{
		AddErr(ERRSCALEDELPOSBOX);
		return;
	}
	if (h%2!=0)
		h=h+1;
	posbox->content=realloc(posbox->content, (2*(h+posbox->Nc))*sizeof(int));
	xy=(int *)posbox->content;
	
	for (i=0;i<h/2;i++)
	{
		xy[2*i+1]=i;
		if (lr=='l')
		{	
			xy[2*i]=h/2-i-1;
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[0]));	
		}
		else
		{
			xy[2*i]=i;
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[1]));
		}
	}
	for (i=h/2;i<h;i++)
	{	
		if (lr=='l')
		{
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[1]));	
			xy[2*i]=i-h/2;
		}
		else
		{
			xy[2*i]=h-1-i;
			AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(chars[0]));	
		}
		xy[2*i+1]=i;
	}
}

void Slash(box *posbox, int h, int slashchar, char fb)
{
	int *xy;
	int i;
	if (posbox->T!=B_POS)
	{
		AddErr(ERRSCALEDELPOSBOX);
		return;
	}
	if (h<1)
		h=1;
	posbox->content=realloc(posbox->content, (2*(h+posbox->Nc))*sizeof(int));
	xy=(int *)posbox->content;
	for (i=0;i<h;i++)
	{
		AddChild(posbox, B_UNIT, (void *)Unicode2Utf8(slashchar));	
		if (fb=='f')
		{
			xy[2*i]=i;
			xy[2*i+1]=i;
		}
		else
		{
			xy[2*i]=h-i-1;
			xy[2*i+1]=i;
		}
	}
}

void DrawScalableDelim(SCALABLE_DELIMITER D, box *b, int h)
{
	switch(D)
	{
		case DEL_LCURL:
			SymBrac(b,h,style->LCURLYCHAR);
			break;
		case DEL_RCURL:
			SymBrac(b,h,style->RCURLYCHAR);
			break;
		case DEL_LSQ:
			Brac(b,h,style->LSQUARECHAR);
			break;
		case DEL_RSQ:
			Brac(b,h,style->RSQUARECHAR);
			break;
		case DEL_L:
			Brac(b,h,style->LBRACKCHAR);
			break;
		case DEL_R:
			Brac(b,h,style->RBRACKCHAR);
			break;
		case DEL_VBAR:
			Brac(b,h,style->VBARCHAR);
			break;
		case DEL_DVBAR:
			Brac(b,h,style->DVBARCHAR);
			break;
		case DEL_LANGLE:
			AngleBrac(b,h,style->ANGLECHAR,'l');
			break;
		case DEL_RANGLE:
			AngleBrac(b,h,style->ANGLECHAR,'r');
			break;
		case DEL_UPARROW:
			Brac(b,h,style->UPARROWCHAR);
			break;
		case DEL_DOWNARROW:
			Brac(b,h,style->DOWNARROWCHAR);
			break;
		case DEL_UPDOWNARROW:
			Brac(b,h,style->UPDOWNARROWCHAR);
			break;
		case DEL_BACKSLASH:
			Slash(b,h,style->BSLASH,'b');
			break;
		case DEL_SLASH:
			Slash(b,h,style->FSLASH,'f');
			break;
		case DEL_DUPARROW:
			Brac(b,h,style->DUPARROWCHAR);
			break;
		case DEL_DDOWNARROW:
			Brac(b,h,style->DDOWNARROWCHAR);
			break;
		case DEL_DUPDOWNARROW:
			Brac(b,h,style->DUPDOWNARROWCHAR);
			break;
		case DEL_LFLOOR:
			Brac(b,h,style->LFLOORCHAR);
			break;
		case DEL_RFLOOR:	
			Brac(b,h,style->RFLOORCHAR);
			break;
		case DEL_LCEIL:
			Brac(b,h,style->LCEILCHAR);
			break;
		case DEL_RCEIL:	
			Brac(b,h,style->RCEILCHAR);
			break;
		default:
			break;
	}
}


void MakeLeftRight(TOKEN *T, box *b, int Font)
/* make a box between brackets for the token T */
{
	int *Ncol, *xy;
	box *B, *B1, *B2;
	int h, hh1, hh2, yc, li=-1, ri=-1, mi=-1, bi1=-1, bi2=-1;	
	SCALABLE_DELIMITER DL, DM, DR;
	
	/* array box for the body */
	Ncol=malloc(sizeof(int));
	Ncol[0]=0;
	/* create a line box for the brackets and body*/
	AddChild(b, B_LINE, (void *)Ncol);
	B=b->child+b->Nc-1;
	
	
	
	DL=LookupDelimiter(T->args[2], NULL); /* opening delimiter */
	
	if (DL!=DEL_DOT)
	{
		/* posbox for the left bracket */
		xy=calloc(2,sizeof(int));		
		AddChild(B, B_POS, (void *)xy);
		li=B->Nc-1;
	}
	
	if (strlen(T->args[0]))
	{
		/* the body, part1 */
		Ncol=malloc(sizeof(int));
		Ncol[0]=0;
		AddChild(B, B_LINE, (void *)Ncol);
		B1=B->child+B->Nc-1;
		
		ParseStringRecursive(T->args[0], B1, Font);
		bi1=B->Nc-1;
	}
	
	DM=LookupDelimiter(T->args[3], NULL); /* middle delimiter */
	
	if (DM!=DEL_DOT)
	{
		/* posbox for the middle delimiter */
		xy=calloc(2,sizeof(int));		
		AddChild(B, B_POS, (void *)xy);
		mi=B->Nc-1;
	}
	
	/* the body, part2 */
	if (strlen(T->args[1]))
	{
		Ncol=malloc(sizeof(int));
		Ncol[0]=0;
		AddChild(B, B_LINE, (void *)Ncol);
		B2=B->child+B->Nc-1;
		ParseStringRecursive(T->args[1], B2, Font);
		bi2=B->Nc-1;
	}
	
	DR=LookupDelimiter(T->args[4], NULL); /* closing delimiter */
	
	if (DR!=DEL_DOT)
	{
		/* posbox for the closing delimiter */
		xy=calloc(2,sizeof(int));		
		AddChild(B, B_POS, (void *)xy);
		ri=B->Nc-1;
	}
	yc=0;
	hh1=0;
	hh2=0;
	if (bi1>=0)
	{
		BoxPos(B->child+bi1);
		BoxSetState(B->child+bi1, SIZEKNOWN);
		yc=B->child[bi1].yc;
		hh1=B->child[bi1].h-B->child[bi1].yc; /* upper half arg1*/
	}
	if (bi2>=0)
	{
		BoxPos(B->child+bi2);
		BoxSetState(B->child+bi2, SIZEKNOWN);
		if (B->child[bi2].yc>yc)
			yc=B->child[bi2].yc;
		hh2=B->child[bi2].h-B->child[bi2].yc; /* upper half arg2*/
	}
	if ((bi1<0)&&(bi2<0))
	{	
		/* The following comment line lets the gen_errorflags.sh script generate appropriate error flags and messages */
		// ERRORFLAG ERRNOBODYINLR  "Missing body argument in \\left ... \\right construct"
		AddErr(ERRNOBODYINLR);
		return;
	}
	
	h=yc;	
	if (hh1>hh2)
		h+=hh1;
	else
		h+=hh2;
		
	/* some brackest need uneven heights, I want all delimiters to have the same height */
	if ((DL==DEL_LCURL)||(DM==DEL_LCURL)||(DR==DEL_LCURL))
		if (h%2!=1)
		{
			h=h+1;
			yc++; // center character needs to align with yc
		}	
	if ((DL==DEL_RCURL)||(DM==DEL_RCURL)||(DR==DEL_RCURL))
		if (h%2!=1)
		{
			h=h+1;	
			yc++; // center character needs to align with yc
		}	
	/* some brackest need even heights, I want all delimiters to have the same height */
	if ((DL==DEL_LANGLE)||(DM==DEL_LANGLE)||(DR==DEL_LANGLE))
		if (h%2!=0)
			h=h+1;	
	if ((DL==DEL_RANGLE)||(DM==DEL_RANGLE)||(DR==DEL_RANGLE))
		if (h%2!=0)
			h=h+1;	
	
	if (li>=0)
	{
		DrawScalableDelim(DL, B->child+li, h);
		B->child[li].yc=yc;
		B->child[li].Y=FIX;
	}
	
	if (mi>=0)
	{
		DrawScalableDelim(DM, B->child+mi, h);
		B->child[mi].yc=yc;
		B->child[mi].Y=FIX;
	}
	
	if (ri>=0)
	{
		DrawScalableDelim(DR, B->child+ri, h);
		B->child[ri].yc=yc;
		B->child[ri].Y=FIX;
	}	
	
	AddScripts(T->sub, T->super, B, T->limits, Font);
}

void AddBraces(char *lbrace, char *rbrace, box *b)
/* this routine also puts things between brackets but works differently from the routine above
 * This routine takes the box b, places a new box around it (i.e. b will be the child of this box)
 * and then places the contents of b between brackets, i.e. this puts an *existing* element between 
 * brackets where the above routine creates a *new* element between brackets 
 * AddBraces only does left and right braces and is used to put arrays between braces */
{

	int *Ncol, *xy;
	int h;
	int li=-1, ri=-1, bi=0;	
	box dummy;
	SCALABLE_DELIMITER DL, DR;
	
	/* check braces */
	DL=LookupDelimiter(lbrace, NULL);
	DR=LookupDelimiter(rbrace, NULL);
	if ((DL==DEL_DOT)&&(DR==DEL_DOT))
		return;
	
	
	/* get the size of box b */
	BoxPos(b);
	h=b->h;
	BoxSetState(b, SIZEKNOWN);
	
	
	/* put box b in a arraybox */
	Ncol=malloc(sizeof(int));
	Ncol[0]=0;
	if (BoxInBox(b, B_LINE, (void *)Ncol))
		return; /* abort BoxInBox failed */
	if (*lbrace!='.')
	{
		/* posbox for the left brace */
		xy=calloc(2,sizeof(int));		
		AddChild(b, B_POS, (void *)xy);
		/* swap first two children of B */
		dummy=b->child[b->Nc-1];
		b->child[b->Nc-1]=b->child[b->Nc-2];
		b->child[b->Nc-2]=dummy;
		li=0;
		bi=1;
	}
	if (*rbrace!='.')
	{
		/* posbox for the right bracket */
		xy=calloc(2,sizeof(int));		
		AddChild(b, B_POS, (void *)xy);
		ri=b->Nc-1;
	}
	/* we now have an array box with the box b surrounded by posboxes for the braces */
	if (li>=0)
	{
		DrawScalableDelim(DL, b->child+li, h);
		b->child[li].yc=b->child[bi].yc;
		b->child[li].Y=FIX;
	}
	if (ri>=0)
	{
		DrawScalableDelim(DR, b->child+ri, h);
		b->child[ri].yc=b->child[bi].yc;
		b->child[ri].Y=FIX;
	}
}

void MakeBox(TOKEN *T, box *b, int Font)
/* just makes and empty box. a bummy box may have any non negative size, i.e. it may be 0 sized 
 * It is useful as a placeholder*/
{
	int *dim;
	dim=malloc(2*sizeof(int));
	dim[0]=atoi(T->args[0]);
	dim[1]=atoi(T->args[1]);
	
	AddChild(b, B_DUMMY, (void*)dim);
	AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
}

void MakeFrac(TOKEN *T, box *b, int Font)
{
	unsigned char *str;
	char *line;
	int n;
	int *Ncol;
	box *frac;
	int i, j,yc;	
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=1;
	/* create a array box and point to it with the box pointer frac */
	AddChild(b, B_ARRAY, (void *)Ncol);
	frac=b->child+b->Nc-1;
		
		
	/* add three boxes to the array box (numerator, denominator, and the horizontal line inbetween) */
	ParseStringInBox(T->args[0], frac, Font); 	/* numerator */ 
	
	str=calloc(1,sizeof(char));		/* add unit box for horizontal bar*/
	AddChild(frac, B_UNIT, str);
	
	
	ParseStringInBox(T->args[1], frac, Font); 	/* denominator */
	
		
	/* change the middle unit box to scale the horizontal bar */
	/* get box sizes */
	BoxPos(frac);
	yc=frac->child[1].ry;
	
	line=Unicode2Utf8(style->FRACLINE);	
	n=NumByte(line);
	/* the width of the box frac is now the desired width for the horizonatal bar */
	/* str=(unsigned char *)frac->child[1].content;*/
	frac->child[1].content=realloc(frac->child[1].content, (n*frac->w+1)*sizeof(char));
	str=(unsigned char *)frac->child[1].content;
	for (i=0;i<frac->w;i++)
	{
		for (j=0;j<n;j++)
			str[n*i+j]=line[j];	
	}
	str[n*frac->w]='\0';
	free(line);
	frac->child[1].w=frac->w;
	frac->child[1].xc=frac->xc;
	frac->S=INIT;
	BoxPos(frac);
	BoxSetState(frac, SIZEKNOWN);
	frac->yc=yc;
	frac->Y=FIX;
	frac->S=SIZEKNOWN;
	
	AddScripts(T->sub, T->super, frac, T->limits, Font);
}

void MakeBinom(TOKEN *T, box *b, int Font)
{
	unsigned char *str;
	int *Ncol;
	box *binom;
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=1;
	/* create a array box and point to it with the box pointer binom */
	AddChild(b, B_ARRAY, (void *)Ncol);
	binom=b->child+b->Nc-1;
		
		
	/* add two boxes to the array box  */
	ParseStringInBox(T->args[0], binom, Font); 	/* n */	
	str=calloc(1,sizeof(char));		/* add unit box for spacing*/
	AddChild(binom, B_UNIT, str);
	ParseStringInBox(T->args[1], binom, Font); 	/* k */
	
	binom->S=INIT;
	BoxPos(binom);
	BoxSetState(binom, SIZEKNOWN);
	binom->yc=binom->child[1].ry;
	binom->Y=FIX;
	binom->S=SIZEKNOWN;
	AddBraces("(", ")", binom);
	AddScripts(T->sub, T->super, binom, T->limits, Font);
}

void MakeOverline(TOKEN *T, box *b, int Font)
{
	unsigned char *str;
	char *line;
	int n;
	int *Ncol;
	box *over;
	int i, j, yc;	
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=1;
	/* create a array box and point to it with the box pointer over */
	AddChild(b, B_ARRAY, (void *)Ncol);
	over=b->child+b->Nc-1;
		
		
	str=calloc(1,sizeof(char));		/* add unit box for horizontal bar*/
	AddChild(over, B_UNIT, str);
	
	
	ParseStringInBox(T->args[0], over, Font); 	/* whatever is overlined */
	
		
	/* scale the horizontal bar */
	/* get box sizes */
	BoxPos(over);
	yc=over->child[1].ry;
		
	line=Unicode2Utf8(style->OVERLINE);	
	n=NumByte(line);	
	/* the width of the box over is now the desired width for the horizonatal bar */
	/* str=(unsigned char *)over->child[1].content;*/
	over->child[0].content=realloc(over->child[0].content, (n*over->w+1)*sizeof(char));
	str=(unsigned char *)over->child[0].content;
	for (i=0;i<over->w;i++)
	{
		for (j=0;j<n;j++)
			str[n*i+j]=line[j];	
	}
	str[n*over->w]='\0';
	over->child[0].w=over->w;
	over->child[0].xc=over->xc;
	over->S=INIT;
	BoxPos(over);
	BoxSetState(over, SIZEKNOWN);
	over->yc=yc;
	over->Y=FIX;
	over->S=SIZEKNOWN;
	
	AddScripts(T->sub, T->super, over, T->limits, Font);
}

void MakeBlock(TOKEN *T, box *b, int Font)
{
	int *Ncol;
	box *block;	
	Ncol=malloc(sizeof(int));
	Ncol[0]=0;
	/* create a array box and point to it with the box pointer over */
	AddChild(b, B_ARRAY, (void *)Ncol);
	block=b->child+b->Nc-1;
	if (strlen(T->args[0])==0)
	{
		/* add a zero sized box */
		int *dim;
		dim=malloc(2*sizeof(int));
		dim[0]=0;
		dim[1]=0;
	
		AddChild(block, B_DUMMY, (void*)dim);
	}
	else
		ParseStringInBox(T->args[0], block, Font); 	/* whatever is in the box */	
	AddScripts(T->sub, T->super, block, T->limits, Font);
}
void MakeUnderline(TOKEN *T, box *b, int Font)
{
	unsigned char *str;
	char *line;
	int n;
	int *Ncol;
	box *under;
	int i, j, yc;	
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=1;
	/* create a array box and point to it with the box pointer under */
	AddChild(b, B_ARRAY, (void *)Ncol);
	under=b->child+b->Nc-1;
		
	ParseStringInBox(T->args[0], under, Font); 	/* whatever is underlined */
		
	str=calloc(1,sizeof(char));		/* add unit box for horizontal bar*/
	AddChild(under, B_UNIT, str);
	
		
	/* scale the horizontal bar */
	/* get box sizes */
	BoxPos(under);
	yc=under->child[0].ry;
		
	line=Unicode2Utf8(style->UNDERLINE);	
	n=NumByte(line);		
	/* the width of the box under is now the desired width for the horizonatal bar */
	/* str=(unsigned char *)under->child[1].content;*/
	under->child[1].content=realloc(under->child[1].content, (n*under->w+1)*sizeof(char));
	str=(unsigned char *)under->child[1].content;
	for (i=0;i<under->w;i++)
	{
		for (j=0;j<n;j++)
			str[n*i+j]=line[j];	
	}
	str[n*under->w]='\0';
	under->child[1].w=under->w;
	under->child[1].xc=under->xc;
	under->S=INIT;
	BoxPos(under);
	BoxSetState(under, SIZEKNOWN);
	under->yc=yc;
	under->Y=FIX;
	under->S=SIZEKNOWN;
	
	AddScripts(T->sub, T->super, under, T->limits, Font);
}
void MakeSqrt(TOKEN *T, box *b, int Font)
{
	int *xy;
	int i;
	int wo,  w, h, xoff=0, ioff=0;
	box *sqrt;
	int Nc=1;

	Nc+=(T->opt!=NULL);

	xy=malloc(Nc*2*sizeof(int));
	xy[0]=0;
	xy[1]=0;
	/* add a posbox */
	AddChild(b, B_POS, (void *)xy);
	sqrt=b->child+b->Nc-1;
	
	if (T->opt)
	{
		ParseStringInBox(T->opt[0], sqrt, Font);
		BoxPos(sqrt->child);
		wo=sqrt->child->w;		
		/* xoff will contain an x offset in case the index block is large w.r.t. the size of the radical sign */
		xoff=wo-1;
		/* index offset for the box indices to accomodate for the extra index box */
		ioff=1;	
	}
	
	
	ParseStringInBox(T->args[0], sqrt, Font);/* adds a box for the radicant */
	/* now we have to draw the radical sign */
	/* first get the get box sizes */
	BoxPos(sqrt->child+ioff);
	w=sqrt->child[ioff].w;
	h=sqrt->child[ioff].h;
	
	/* we will add many unit boxes to the posbox to draw the radical sign, allocate the offset coordinate array of the posbox */
	
	sqrt->content=realloc(sqrt->content, (2*(h+(h/2+1)+3+w)+sqrt->Nc)*sizeof(int));
	xy=(int *)sqrt->content;
	if (ioff)
	{
		xy[0]=0;
		xy[1]=h/2+1;
	}
	
	xy[2*ioff]=h/2+2+xoff; /* shift main box to make room for the sqrt sign */
	xy[2*ioff+1]=0; /* shift main box to make room for the sqrt sign */
	for (i=0;i<h;i++)
	{				
		AddChild(sqrt, B_UNIT, (void *)Unicode2Utf8(style->SQRTCHAR[1])); // upward vertical
		xy[2*(i+1+ioff)]=h/2+xoff+1;
		xy[2*(i+1+ioff)+1]=i;
	}
		
	for (i=0;i<h/2+1;i++)
	{
		AddChild(sqrt, B_UNIT, (void *)Unicode2Utf8(style->SQRTCHAR[0])); // downward diagonal
		xy[2*(i+1+h+ioff)]=i+xoff;
		xy[2*(i+1+h+ioff)+1]=h/2-i;
	}
	
	AddChild(sqrt, B_UNIT, (void *)Unicode2Utf8(style->SQRTCHAR[2])); // left top corner
	xy[2*(sqrt->Nc-1)]=h/2+1+xoff;
	xy[2*(sqrt->Nc-1)+1]=h;
	for (i=0;i<w;i++) // horizontal
	{
		AddChild(sqrt, B_UNIT, (void *)Unicode2Utf8(style->SQRTCHAR[3])); // left top corner
		xy[2*(sqrt->Nc-1)]=h/2+2+xoff+i;
		xy[2*(sqrt->Nc-1)+1]=h;
	}
	AddChild(sqrt, B_UNIT, (void *)Unicode2Utf8(style->SQRTCHAR[4])); // right top corner
	xy[2*(sqrt->Nc-1)]=h/2+2+xoff+w;
	xy[2*(sqrt->Nc-1)+1]=h;
	
	BoxSetState(sqrt, RELPOSKNOWN);	
	sqrt->S=INIT;
	/* inherit baseline from contents */
	sqrt->yc=(sqrt->child+ioff)->yc;
	sqrt->Y=FIX;	
	AddScripts(T->sub, T->super, sqrt, T->limits, Font);			
}

void DrawInt(box *b, int n, int size)
{
	int *xy;
	int i,j,k;
	box *integ;
	xy=malloc(2*sizeof(int));
	xy[0]=0;
	xy[1]=0;
	/* add a posbox */
	AddChild(b, B_POS, (void *)xy);
	integ=b->child+b->Nc-1;
	/* draw the integral sign */
	if (size<=1)
	{
		switch(n)
		{
			case 2:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[1]));
				xy[0]=0;
				xy[1]=0;	
				break;
			case 3:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[2]));
				xy[0]=0;
				xy[1]=0;	
				break;
			case 4:
				integ->content=realloc(integ->content, (8*sizeof(int)));
				xy=(int *)integ->content;
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				xy[2]=1;
				xy[3]=0;		
				xy[4]=2;
				xy[5]=0;		
				xy[6]=3;
				xy[7]=0;	
				break;
			case 5:
				integ->content=realloc(integ->content, (6*sizeof(int)));
				xy=(int *)integ->content;
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[3]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				xy[2]=1;
				xy[3]=0;		
				xy[4]=2;
				xy[5]=0;	
				break;
			case 1:
			default:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				break;
		}
	}
	else
	{
		/* we will add many unit boxes to the posbox to draw the integral sign, allocate the offset coordinate array of the posbox */
		if (n>4)
		{
			integ->content=realloc(integ->content, (2*(2*size+integ->Nc+1)*sizeof(int)));
			xy=(int *)integ->content;
			j=0;
			for (k=0;k<2;k++) // two integral signs
			{
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[0]));// bottom
				xy[2*j]=2*k;
				xy[2*j+1]=0;		
				j++;
				for (i=1;i<size-1;i++)
				{	
					AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[1]));// extender
					xy[2*j]=2*k;
					xy[2*j+1]=i;	
					j++;
				}
			
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[2]));// top
				xy[2*j]=2*k;
				xy[2*j+1]=size-1;
				j++;
			}
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->IINTCHAR[3])); // dots inbetween
			xy[2*j]=1;
			xy[2*j+1]=size/2;		
				
		}
		else
		{
			integ->content=realloc(integ->content, (2*(n*size+integ->Nc)*sizeof(int)));
			xy=(int *)integ->content;
			j=0;
			for (k=0;k<n;k++)
			{
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[0]));// bottom
				xy[2*j]=k;
				xy[2*j+1]=0;		
				j++;
				for (i=1;i<size-1;i++)
				{	
					AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[1]));// extender
					xy[2*j]=k;
					xy[2*j+1]=i;	
					j++;
				}
			
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[2]));// top
				xy[2*j]=k;
				xy[2*j+1]=size-1;
				j++;
			}
		}
	}
	integ->yc=(size-1)/2;
	integ->Y=FIX;
}

void DrawOInt(box *b, int n, int size)
{
	int *xy;
	int i,j,k;
	box *integ;
	xy=malloc(2*sizeof(int));
	xy[0]=0;
	xy[1]=0;
	/* add a posbox */
	AddChild(b, B_POS, (void *)xy);
	integ=b->child+b->Nc-1;
	/* draw the integral sign */
	if (size<=1)
	{
		switch(n)
		{
			case 2:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[1]));
				xy[0]=0;
				xy[1]=0;	
				break;
			case 3:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[2]));
				xy[0]=0;
				xy[1]=0;	
				break;
			case 4:
				/* there is no pretty solution I can think of */
				integ->content=realloc(integ->content, (8*sizeof(int)));
				xy=(int *)integ->content;
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				xy[2]=1;
				xy[3]=0;		
				xy[4]=2;
				xy[5]=0;		
				xy[6]=3;
				xy[7]=0;	
				break;
			case 5:
				integ->content=realloc(integ->content, (6*sizeof(int)));
				xy=(int *)integ->content;
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[3]));
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				xy[2]=1;
				xy[3]=0;		
				xy[4]=2;
				xy[5]=0;	
				break;
			case 1:
			default:
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[0]));
				xy[0]=0;
				xy[1]=0;	
				break;
		}
	}
	else
	{
		/* we will add many unit boxes to the posbox to draw the integral sign, allocate the offset coordinate array of the posbox */
		if (n>4)
		{
			integ->content=realloc(integ->content, (2*(2*size+integ->Nc+3)*sizeof(int)));
			xy=(int *)integ->content;
			j=0;
			for (k=0;k<2;k++)
			{
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[0]));// bottom
				xy[2*j]=2*k+1;
				xy[2*j+1]=0;		
				j++;
				for (i=1;i<size-1;i++)
				{	
					AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[1]));// extender
					xy[2*j]=2*k+1;
					xy[2*j+1]=i;	
					j++;
				}
			
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[2]));// top
				xy[2*j]=2*k+1;
				xy[2*j+1]=size-1;
				j++;
			}
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OIINTCHAR[3]));
			xy[2*j]=2;
			xy[2*j+1]=size/2;	
			j++;	
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OINTCHAR[0]));
			xy[2*j]=0;
			xy[2*j+1]=size/2;	
			j++;		
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OINTCHAR[1]));
			xy[2*j]=4;
			xy[2*j+1]=size/2;		
				
		}
		else
		{
			integ->content=realloc(integ->content, (2*(n*size+integ->Nc+2)*sizeof(int)));
			xy=(int *)integ->content;
			j=0;
			for (k=0;k<n;k++)
			{
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[0]));// bottom
				xy[2*j]=k+1;
				xy[2*j+1]=0;		
				j++;
				for (i=1;i<size-1;i++)
				{	
					AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[1]));// extender
					xy[2*j]=k+1;
					xy[2*j+1]=i;	
					j++;
				}
			
				AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->INTCHAR[2]));// top
				xy[2*j]=k+1;
				xy[2*j+1]=size-1;
				j++;
			}
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OINTCHAR[0]));
			xy[2*j]=0;
			xy[2*j+1]=size/2;	
			j++;		
			AddChild(integ, B_UNIT, (void *)Unicode2Utf8(style->OINTCHAR[1]));
			xy[2*j]=n+1;
			xy[2*j+1]=size/2;	
			
			
		}
	}
	integ->yc=(size-1)/2;
	integ->Y=FIX;
}
void MakeScaleInt(TOKEN *T, box *b, int n, int o, int Font)
/* scale the int sign to its contrents */
{
	char *p, c='\0';
	int *Ncol;
	int *xy;
	int h;
	box *integ;
	box *next;

	xy=malloc(2*sizeof(int));
	xy[0]=0;
	xy[1]=0;
	/* add a posbox */
	AddChild(b, B_POS, (void *)xy);
	
	
	
	/* add a new rowbox to contain all to the right of the integral sign */
	Ncol=malloc(sizeof(int));
	Ncol[0]=0;
	AddChild(b, B_ARRAY, (void *)Ncol);
	next=b->child+b->Nc-1;
	integ=b->child+b->Nc-2;
	
	
	/* we take the whole right hand side up to a possible '=' sign */
	p=T->next;
	while (*p&&(*p!='='))
		p++;
	if (*p=='=')
	{
		*p=c;
		c='=';
	}
	
	ParseStringInBox(T->next, next, Font); /* add the the remainder of the line to it */
	T->next+=strlen(T->next); /* scroll to the end as we finish the remainder here */
	
	/* resore the '=' sign if it was there */
	if (c)
		*p=c;
		
	BoxPos(next);
	h=next->h;
	BoxSetState(next, RELPOSKNOWN);	
	if (o)
		DrawOInt(integ, n, h);
	else
		DrawInt(integ, n, h);
	
	integ->yc=next->yc;
	integ->Y=FIX;
	AddScripts(T->sub, T->super, integ, (T->limits||(n>1)), Font);
}
void MakeFixInt(TOKEN *T, box *b, int n, int o, int Font)
/* just dump an int sign of size 3, regardless of the size of its argument (how LaTeX typically does it) */
{
	int *xy;
	box *integ;

	xy=malloc(2*sizeof(int));
	xy[0]=0;
	xy[1]=0;
	/* add a posbox */
	AddChild(b, B_POS, (void *)xy);
	integ=b->child+b->Nc-1;
	if (o)
		DrawOInt(integ, n, 3);
	else
		DrawInt(integ, n, 3);
	

	AddScripts(T->sub, T->super, integ, (T->limits||(n>1)), Font);
}

void MakeInt(TOKEN *T, box *b, int n, int o, int Font)
{
	if (T->Nopt)
		if (T->opt[0][0]=='S')
		{
			MakeScaleInt(T,b, n, o, Font);
			return;
		}
	MakeFixInt(T,b, n, o, Font);	
}


void DrawSymbol(box *b, int chars[])
{
	int *xy;
	box *c;
	int i,j;
	xy=malloc(2*chars[0]*chars[1]*sizeof(int));
	for (i=0;i<chars[1];i++)
		for (j=0;j<chars[0];j++)
		{
			xy[2*(chars[0]*i+j)]=j;
			xy[2*(chars[0]*i+j)+1]=i;
		}
	AddChild(b, B_POS, (void *)xy);
	c=b->child+b->Nc-1;
	
	/* draw the symbol */
	for (i=0;i<chars[0]*chars[1];i++)
		AddChild(c, B_UNIT, (void *)Unicode2Utf8(chars[i+2]));
	b->yc=chars[1]/2;
}


void MakeSum(TOKEN *T, box *b, int Font)
/* 
 * Draws Sum Symbol
 */
{
	box *c;
	
	DrawSymbol(b, style->SUMCHAR);	
	c=b->child+b->Nc-1;
	
	AddScripts(T->sub, T->super, c, 1, Font);
}

void MakeProd(TOKEN *T, box *b, int Font)
/* Makes a product sign
*/
{
	box *c;
	
	DrawSymbol(b, style->PRODCHAR);	
	c=b->child+b->Nc-1;
	
	AddScripts(T->sub, T->super, c, 1, Font);
}

int AZToFontUnicode(int base, char c)
{
	int u;
	if ((c>='A')&&(c<='Z'))
		u=base+(int)(c-'A');
	else
		return 0;
	return u;
}
int azToFontUnicode(int base, char c)
{
	int u;
	if ((c>='a')&&(c<='z'))
		u=base+(int)(c-'a');
	else
		return 0;
	return u;
}
int NumToFontUnicode(int base, char c)
{
	int u;
	if ((c>='0')&&(c<='9'))
		u=base+(int)(c-'0');
	else
		return 0;
	return u;
}

/* map unicode character to other unicode character using the tables in mapunicode.h */
int UnicodeToFontUnicode(const MapUnicode *T, char *p, int *n)
{
	MapUnicode *i;
	int u;
	u=Unicode(p, n);
	i=(MapUnicode *)T;
	while (i->in>0)
	{
		if (u==i->in)
			return i->out;
		i++;
	}
	return 0;
}
void MakeSymbol(TOKEN *T, box *b, int Font)
{
	unsigned char * str;
	char *tmp;
	int u;
	char *p, *t, *d;
	int l, skip;
	l=strlen(T->args[0]);
	/*if (!Font)
	{
		str=malloc((l+1)*sizeof(char));
		strncpy((char *)str,T->args[0],l+1);
		AddChild(b, B_UNIT, (void *)str);
		AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
		return;
	}*/
	str=malloc((4*l+1)*sizeof(char));
	d=(char *)str;
	p=T->args[0];
	if (T->F!=F_NOFONT) /* if the token specifies the font it is a \it \rm of \bf command and we set the font for the current block, from this point onwards */
	{				  /* otherwise we will use the inherited font from the box above */
					  /* note that this is somewhat of a dirty hack
					   * if the token has a font I set the Font variable to something corresponding to italic roman for bold
					   * otherwise, for the commands like \text{..} \mathbfit{..}, etc, the token has no font set!
					   * then we only inherit fonts and the command itself triggers the creation of a box with the PRSDEF as font value
					   * This is a bad construct in thorough need of fixin... */
		switch((FONT)T->F)
		{
			case F_ITALIC:
				Font=PD_MATHSFIT;
				break;
			case F_ROMAN:
				Font=PD_TEXT;
				break;
			case F_BOLD:
				Font=PD_MATHBF;
				break;
			default:
				Font=RootFont; /* is this better, I do not understand my own poorly written comment */
				break;
		}				
	}
	while (*p)
	{
		switch((PRSDEF)Font) 
		{
			case PD_MATHBF:
				u=AZToFontUnicode(0x1D400, *p); /* map capital letters */
				if (!u)
					u=azToFontUnicode(0x1D41A, *p); /* if that did not work map small letters */
				if (!u)
					u=NumToFontUnicode(0x1D7CE, *p); /* if that did not work map numbers */
				if (!u)
				{
					u=UnicodeToFontUnicode(GreekBFTable, p, &skip); /* if that did not work symbols*/
					if (u)
						p+=skip-1; /* as the character is a symbol we need to skip till the end of the utf character */
				}
				break;
			case PD_MATHBFIT:
				u=AZToFontUnicode(0x1D468, *p);
				if (!u)
					u=azToFontUnicode(0x1D482, *p);
				if (!u)
				{
					u=UnicodeToFontUnicode(GreekBFITTable, p, &skip);
					if (u)
						p+=skip-1;
				}
				break;
			case PD_MATHCAL:
				u=AZToFontUnicode(0x1D49C, *p);
				if (!u)
					u=azToFontUnicode(0x1D4B6, *p);
				break;
			case PD_MATHSCR:
				u=AZToFontUnicode(0x1D4D0, *p);
				if (!u)
					u=azToFontUnicode(0x1D4EA, *p);
				break;
			case PD_MATHFRAK:
				u=AZToFontUnicode(0x1D504, *p);
				if (!u)
					u=azToFontUnicode(0x1D51E, *p);
				break;
			case PD_MATHBB:
				u=AZToFontUnicode(0x1D538, *p);
				if (!u)
					u=azToFontUnicode(0x1D552, *p);
				if (!u)
					u=NumToFontUnicode(0x1D7D8, *p);
				break;
			case PD_MATHSF:
				u=AZToFontUnicode(0x1D5A0, *p);
				if (!u)
					u=azToFontUnicode(0x1D5BA, *p);
				if (!u)
					u=NumToFontUnicode(0x1D7E2, *p);
				break;
			case PD_MATHSFBF:
				u=AZToFontUnicode(0x1D5D4, *p);
				if (!u)
					u=azToFontUnicode(0x1D5EE, *p);
				if (!u)
					u=NumToFontUnicode(0x1D7EC, *p);
				if (!u)
				{
					u=UnicodeToFontUnicode(GreekSFBFTable, p, &skip);
					if (u)
						p+=skip-1;
				}
				break;
			case PD_MATHSFIT:
				u=AZToFontUnicode(0x1D608, *p);
				if (!u)
					u=azToFontUnicode(0x1D622, *p);
				if (!u)
				{
					u=UnicodeToFontUnicode(GreekSFITTable, p, &skip);
					if (u)
						p+=skip-1;
				}
				break;
			case PD_MATHSFBFIT:
				u=AZToFontUnicode(0x1D63C, *p);
				if (!u)
					u=azToFontUnicode(0x1D656, *p);
				if (!u)
				{
					u=UnicodeToFontUnicode(GreekSFBFITTable, p, &skip);
					if (u)
						p+=skip-1;
				}
				break;
			case PD_MATHTT: /* note that this is not all that useful as we require fixed size fonts anyway */
				u=AZToFontUnicode(0x1D670, *p);
				if (!u)
					u=azToFontUnicode(0x1D68A, *p);
				if (!u)
					u=NumToFontUnicode(0x1D7F6, *p);
				break;
			case PD_TEXT:
				u=0;
				break;
			case PD_MATHNORMAL:
			default:
				u=AZToFontUnicode(0x1D434, *p);
				if (!u)
					u=azToFontUnicode(0x1D44E, *p);
				if (!u)
					u=0;
		}
		if (u)
			tmp=Unicode2Utf8(u);
		else
		{
			/* we do not have this char in this font, just output the standard */
			tmp=malloc(2*sizeof(char));
			tmp[0]=*p;
			tmp[1]='\0';
		}
		t=tmp;
		while (*t)
		{
			*d=*t;
			d++;
			t++;
		}
		free(tmp);
		p++;
	}	
	*d='\0';
	AddChild(b, B_UNIT, (void *)str);
	AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
}
void MathFont(TOKEN *T, box *b, int Font)
{	
	ParseStringInBox(T->args[0], b, (int)T->P);
	AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
}

void RaiseBox(TOKEN *T, box *b, int Font)
{
	/* raise the contents w.r.t. the baseline (yc)
	 * Note that with sub and super scripts this just moves them along 
	 * as sub and superscripts attach themselves to the content and 
	 * inherit the baseline from it. This is probably different from TeX*/	
	ParseStringRecursive(T->args[1], b, Font);	
	BoxPos(b);
	b->yc-=atoi(T->args[0]);
	b->Y=FIX;
	AddScripts(T->sub, T->super, b, T->limits, Font);
}

void InitVsep(box *b, int h)
{
	/* create vertical seperator of height h */
	int *xy;
	box *vsep;
	int i;
	if (h<1)
		return;
		
	xy=malloc(2*h*sizeof(int));
	for (i=0;i<h;i++)
	{
		xy[2*i]=0;
		xy[2*i+1]=i;
	}
	AddChild(b, B_POS, (void *)xy);
	vsep=b->child+b->Nc-1;
	for (i=0;i<h;i++)
		AddChild(vsep, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[0]));
}

void RescaleVsep(box *vsep, int h)
{
	/* create vertical seperator of height h */
	int *xy;
	int i;
	if (vsep->T!=B_POS)
	{		
		/* The following comment line lets the gen_errorflags.sh script generate appropriate error flags and messages */
		// ERRORFLAG ERRSCALEVPOSBOX  "RescaleVsep should only be used on a posbox"
		AddErr(ERRSCALEVPOSBOX);
		return;
	}
	if (h<1)
		return;
	if (vsep->Nc==h)
		return;
		
	xy=(int *)vsep->content;
	xy=realloc(xy,2*h*sizeof(int));
	vsep->content=xy;
	for (i=0;i<h;i++)
	{
		xy[2*i]=0;
		xy[2*i+1]=i;
	}
	
	if (vsep->Nc<h)
	{
		for (i=vsep->Nc;i<h;i++)
			AddChild(vsep, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[0]));
	}
	else
	{
		for (i=vsep->Nc;i>=h;i--)
		{
			FreeBox(vsep->child+i);
			vsep->Nc--;
		}
	}
	vsep->S=INIT;
}

void InitHsep(box *b, int w)
{
	/* create horizontal seperator of height h */
	int *xy;
	box *hsep;
	int i;
	if (w<1)
		return;
		
	xy=malloc(2*w*sizeof(int));
	for (i=0;i<w;i++)
	{
		xy[2*i]=i;
		xy[2*i+1]=0;
	}
	AddChild(b, B_POS, (void *)xy);
	hsep=b->child+b->Nc-1;
	for (i=0;i<w;i++)
		AddChild(hsep, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[1]));
}
void RescaleHsep(box *hsep, int w)
{
	/* create horizontal seperator of width w */
	int *xy;
	int i;
	if (hsep->T!=B_POS)
	{	
		/* The following comment line lets the gen_errorflags.sh script generate appropriate error flags and messages */
		// ERRORFLAG ERRSCALEHPOSBOX  "RescaleHsep should only be used on a posbox"
		AddErr(ERRSCALEHPOSBOX);
		return;
	}
	if (w<1)
		return;
	if (hsep->Nc==w)
		return;
		
	xy=(int *)hsep->content;
	xy=realloc(xy,2*w*sizeof(int));
	hsep->content=xy;
	for (i=0;i<w;i++)
	{
		xy[2*i]=i;
		xy[2*i+1]=0;
	}
	
	if (hsep->Nc<w)
	{
		for (i=hsep->Nc;i<w;i++)
			AddChild(hsep, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[1]));
	}
	else
	{
		for (i=hsep->Nc;i>=w;i--)
		{
			FreeBox(hsep->child+i);
			hsep->Nc--;
		}
	}
	hsep->S=INIT;
}

void MakeArrayBody(TOKEN *T, box *b, int Font)
{
	int Nc, *Ncol, r, c;
	box *array;
	int i, j=0, k;
	int *w, *h, *yc, *xc;
	char *f, *g;	
	
	Nc=strlen(T->opt[1]);
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=Nc;
	
	/* create a array box and point to it with the box pointer array */
	AddChild(b, B_ARRAY, (void *)Ncol);
	array=b->child+b->Nc-1;

	f=T->opt[1];
	g=T->opt[2];
	i=0;
	while(i<T->Nargs)
	{
		if (g[j/Nc]=='-') /* add a horizontal line, creates a complete row */
		{
			for (k=0;k<Nc;k++)
			{
				if (f[k]=='|') /* junction of lines */
				{
						if (j/Nc==0)
						{
							/* top row junction */
							if (k==0) /* upper left corner */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[2]));	
							else if (k==Nc-1) /* upper right corner */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[4]));
							else /* T junction */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[3]));
						}
						else
						{
							/* middle row junction */
							if (k==0)/* left T */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[5]));	
							else if (k==Nc-1)/* Right T */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[7]));								
							else /* + junction */
								AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[6]));
						}
				}
				else
					InitHsep(array,1);
				switch(f[k]) /* adapt alignment to the other elements in the column */
				{
					case 'r':
						(array->child+array->Nc-1)->X=MAX;
						break;
					case 'l':
						(array->child+array->Nc-1)->X=MIN;
						break;
					case 'c':
					default:
						break;
				}
				j++;
			}
		}
		/* we are certain we have no horizontal line, now add a complete row of things */
		for (k=0;k<Nc;k++)
		{
			if (f[k]=='|') /* add a vertical line at the appropriate places */
			{
				InitVsep(array,1);
				switch(g[j/Nc]) /* adapt alignment to the other elements in the row */
				{
					case 't':
						(array->child+array->Nc-1)->Y=MAX;
						break;
					case 'b':
						(array->child+array->Nc-1)->Y=MIN;
						break;
					case 'c':
					default:
						break;
				}	
			}
			else
			{
				ParseStringInBox(T->args[i], array, Font); /* add a cell */
				i++; /* go to next argument */
				switch(f[k])/* adapt alignment to the other elements in the column */
				{
					case 'r':
						(array->child+array->Nc-1)->X=MAX;
						break;
					case 'l':
						(array->child+array->Nc-1)->X=MIN;
						break;
					case 'c':
					default:
						break;
				}
				switch(g[j/Nc])/* adapt alignment to the other elements in the row */
				{
					case 't':
						(array->child+array->Nc-1)->Y=MAX;
						break;
					case 'b':
						(array->child+array->Nc-1)->Y=MIN;
						break;
					case 'c':
					default:
						break;
				}	
			}
			j++;
		}
	}
	if (g[j/Nc]=='-')
	{
		for (k=0;k<Nc;k++)
		{
			if (f[k]=='|')
			{
				/* bottom row junction */
				if (k==0) /* bottom left corner */
					AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[8]));	
				else if (k==Nc-1) /* bottom right corner */
					AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[10]));
				else /* upside down T junction */
					AddChild(array, B_UNIT, (void *)Unicode2Utf8(style->ARRAYCHAR[9]));
			}
			else
				InitHsep(array,1);
			switch(f[j%Nc])
			{
				case 'r':
					(array->child+array->Nc-1)->X=MAX;
					break;
				case 'l':
					(array->child+array->Nc-1)->X=MIN;
					break;
				case 'c':
				default:
					break;
			}
			j++;
		}
	}	
	/* now compute the sizes and rescale any separator box we may have */
	BoxPos(array);
	w=calloc(strlen(f),sizeof(int));
	h=calloc(strlen(g),sizeof(int));
	xc=calloc(strlen(f),sizeof(int));
	yc=calloc(strlen(g),sizeof(int));
	for (i=0;i<array->Nc;i++)
	{
		int m;
		c=i%Nc;
		r=i/Nc;
		
		/* upper half of the box */
		m=(array->child[i].h-array->child[i].yc);
		if (m>h[r]-yc[r])
			h[r]+=m-h[r]+yc[r];
			
			
		/* lower half of the box */
		m=(array->child[i].yc);
		if (m>yc[r])
		{
			/* height increases along with the baseline */
			h[r]+=m-yc[r];
			yc[r]+=m-yc[r];
		}
		
		/* right half of the box */
		m=(array->child[i].w-array->child[i].xc);
		if (m>w[c]-xc[c])
			w[c]+=m-w[c]+xc[c];
			
			
		/* left half of the box */
		m=(array->child[i].xc);
		if (m>xc[c])
		{
			/* height increases along with the baseline */
			w[c]+=m-xc[c];
			xc[c]+=m-xc[c];
		}
	}
	for (i=0;i<array->Nc;i++)
	{
		if (g[i/Nc]=='-')
		{
			if (f[i%Nc]!='|')
			{
				RescaleHsep(array->child+i, w[i%Nc]);
			}
		}
		else
			if (f[i%Nc]=='|')
				RescaleVsep(array->child+i, h[i/Nc]);
				
	}
	free(h);
	free(w);
	array->S=INIT;
}

void MakeArray(TOKEN *T, box *b, int Font)
{
	MakeArrayBody(T, b, Font);
	AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
}
void MakeArrayBrace(TOKEN *T, box *b, char *lbrace, char *rbrace, int Font)
{
	MakeArrayBody(T, b, Font);
	AddBraces(lbrace, rbrace, b->child+b->Nc-1);
	AddScripts(T->sub, T->super, b->child+b->Nc-1, T->limits, Font);
}


void ParseStringInBox(char *B, box *parent, int Font)
{
	int *Nc;
	box *b;
	Nc=malloc(sizeof(int));
	Nc[0]=0;
	AddChild(parent, B_LINE, (void *)Nc);
	b=parent->child+parent->Nc-1;
	ParseStringRecursive(B, b, Font);
}
void ParseStringRecursive(char *B, box *parent, int Font)
{
	int *Ncol, n;
	TOKEN T;
	box *b;
	FONT F=F_NOFONT;
	
	
	while (*B)
	{
		/* add a box for the next token */
		Ncol=malloc(sizeof(int));
		Ncol[0]=0;
		AddChild(parent, B_LINE, (void *)Ncol);
		b=parent->child+(parent->Nc-1);
		
		/* scan the begin for a token */
		T=Lexer(B, F);
		F=T.F; /* keep track of the current fonts */
		//PrintToken(T);
		n=1;
		switch (T.P)
		{
			case PD_RAISEBOX:
				RaiseBox(&T, b, Font);
				break;
			case PD_OVERLINE:
				MakeOverline(&T, b, Font);
				break;
			case PD_UNDERLINE:
				MakeUnderline(&T, b, Font);
				break;
			case PD_FRAC: 
				MakeFrac(&T, b, Font);
				break;
			case PD_BINOM: 
				MakeBinom(&T, b, Font);
				break;
			case PD_SQRT: 
				MakeSqrt(&T, b, Font);
				break;
			case PD_IDOTSINT: 
				n++;
			case PD_IIIINT: 
				n++;
			case PD_IIINT: 
				n++;
			case PD_IINT: 
				n++;
			case PD_INT: 
				MakeInt(&T, b, n, 0, Font);
				break;
			case PD_OIDOTSINT: 
				n++;
			case PD_OIIIINT: 
				n++;
			case PD_OIIINT: 
				n++;
			case PD_OIINT: 
				n++;
			case PD_OINT: 
				MakeInt(&T, b, n, 1, Font);
				break;
			case PD_SUM: 
				MakeSum(&T, b, Font);
				break;
			case PD_PROD: 
				MakeProd(&T, b, Font);
				break;
			case PD_BACKSLASH:
				T.args=malloc(sizeof(char *));
				T.Nargs=1;
				T.args[0]=malloc(2*sizeof(char));
				T.args[0][0]='\\';
				T.args[0][1]='\0';
			case PD_SYMBOL:
				MakeSymbol(&T, b, Font);
				break;
			case PD_LEFTRIGHT:
				MakeLeftRight(&T, b, Font);
				break;
			case PD_ARRAY:
				MakeArray(&T, b, Font);
				break;
			case PD_CASES:
				MakeArrayBrace(&T, b, "{", ".", Font);
				break;
			case PD_PMATRIX:
				MakeArrayBrace(&T, b, "(", ")", Font);
				break;
			case PD_BMATRIX:
				MakeArrayBrace(&T, b, "[", "]", Font);
				break;
			case PD_BBMATRIX:
				MakeArrayBrace(&T, b, "{", "}", Font);
				break;
			case PD_VMATRIX:
				MakeArrayBrace(&T, b, "|", "|", Font);
				break;
			case PD_MATRIX:
				MakeArrayBrace(&T, b, ".", ".", Font);
				//MakeArrayBrace(&T, b, '(', '.');
				//MakeArrayBrace(&T, b, '[', ')');
				break;
			case PD_BOX: 
				MakeBox(&T, b, Font);
				break;
			case PD_BLOCK:
				MakeBlock(&T, b, Font);
				break;
			case PD_MATHBF:
			case PD_MATHBFIT:
			case PD_MATHCAL:
			case PD_MATHFRAK:
			case PD_MATHBB:
			case PD_MATHSF:
			case PD_MATHSFBF:
			case PD_MATHSFIT:
			case PD_MATHSFBFIT:
			case PD_MATHTT:
			case PD_MATHNORMAL:
			case PD_TEXT:
			case PD_MATHSCR:
				MathFont(&T, b, Font);
				break;
			case PD_ENDLINE:
				b->T=B_ENDLINE; /* change the box type */
				b->w=0;
				b->h=0;
				b->S=SIZEKNOWN;
				break;
			case PD_NONE:
				/* serious trouble, give up immediately */
				FreeToken(T);
				return;
			case PD_TSPACE:
				T.args=malloc(sizeof(char *));
				T.Nargs=1;
				T.args[0]=malloc(4*sizeof(char));
				T.args[0][0]=' ';
				T.args[0][1]=' ';
				T.args[0][2]=' ';
				T.args[0][3]='\0';
				MakeSymbol(&T, b, Font);
				break;
			case PD_DSPACE:
				T.args=malloc(sizeof(char *));
				T.Nargs=1;
				T.args[0]=malloc(3*sizeof(char));
				T.args[0][0]=' ';
				T.args[0][1]=' ';
				T.args[0][2]='\0';
				MakeSymbol(&T, b, Font);
				break;
			case PD_SPACE:
				T.args=malloc(sizeof(char *));
				T.Nargs=1;
				T.args[0]=malloc(2*sizeof(char));
				T.args[0][0]=' ';
				T.args[0][1]='\0';
				MakeSymbol(&T, b, Font);
				break;
			case PD_NSPACE:
				break;
			default:
				break;
		
		}
		FreeToken(T);
		B=T.next;
	}
	
}
	
box ParseString(char *string, int LW, char *font)
{
	char *B;
	int *Ncol;
	box root;
	B=PreProcessor(string);
	//printf("preprosessor: %s\n", B);
	
	Ncol=malloc(sizeof(int));
	Ncol[0]=LW;
	root=InitBox(NULL, B_LINE, (void *)Ncol);
	RootFont=LookupFont(font);
	ParseStringRecursive(B, &root, RootFont);
	/* BoxSetState(&root, INIT);*/
	free(B);
	return root;
}
