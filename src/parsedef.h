
typedef struct {
	char           *name;
	PRSDEF          P; /* the PRSDEF enummerator type is declared in lexer.h */
	int 			Nargs;
	int 			Nopt;
} KEYWORD;
/* base context keywords */
const KEYWORD   Keys[] = {
	{"\\raisebox",  PD_RAISEBOX   	, 2, 0},
	{"\\int",  		PD_INT     	, 0, 1},
	{"\\iint",  	PD_IINT     	, 0, 1},
	{"\\iiint",  	PD_IIINT     	, 0, 1},
	{"\\iiiint",  	PD_IIIINT     	, 0, 1},
	{"\\idotsint",  PD_IDOTSINT   	, 0, 1},
	{"\\oint",  	PD_OINT     	, 0, 1},
	{"\\oiint",  	PD_OIINT     	, 0, 1},
	{"\\oiiint",  	PD_OIIINT     	, 0, 1},
	{"\\oiiiint",  	PD_OIIIINT    	, 0, 1},
	{"\\oidotsint", PD_OIDOTSINT  	, 0, 1},
	{"\\overline",  PD_OVERLINE    , 1, 0},
	{"\\underline", PD_UNDERLINE   , 1, 0},
	{"\\mathsfbfit",PD_MATHSFBFIT	, 1, 0},
	{"\\mathsfbf",  PD_MATHSFBF	, 1, 0},
	{"\\mathfrak",  PD_MATHFRAK	, 1, 0},
	{"\\mathbfit",  PD_MATHBFIT	, 1, 0},
	{"\\mathsfit",  PD_MATHSFIT	, 1, 0},
	{"\\mathcal",  	PD_MATHCAL		, 1, 0},
	{"\\mathscr",  	PD_MATHSCR		, 1, 0},
	{"\\mathbf",  	PD_MATHBF		, 1, 0},
	{"\\mathbb",  	PD_MATHBB		, 1, 0},
	{"\\mathsf",  	PD_MATHSF		, 1, 0},
	{"\\mathtt",  	PD_MATHTT		, 1, 0},
	{"\\mathnormal",PD_MATHNORMAL	, 1, 0},
	{"\\text",		PD_TEXT		, 1, 0},
	{"\\backslash", PD_BACKSLASH	, 0, 0},
	{"\\begin", 	PD_BEGIN   	, 1, 0},
	{"\\frac", 		PD_FRAC    	, 2, 0},
	{"\\binom", 	PD_BINOM   	, 2, 0},
	{"\\sqrt", 		PD_SQRT    	, 1, 1},
	{"\\left", 		PD_LEFTRIGHT   , 0, 0},
	{"\\prod",  	PD_PROD    	, 0, 0},
	{"\\sum",  		PD_SUM     	, 0, 0},
	{"\\bar",  		PD_OVERLINE    , 1, 0},
	{"\\box",  		PD_BOX     	, 2, 0},
	{"\\limits",  	PD_LIMITS      , 1, 0},
	{"\\lim",  		PD_LIM   		, 0, 0},
	{"\\over", 		PD_OVER   		, 0, 0},
	{"\\exp",  		PD_FUNCTION   	, 0, 0},
	{"\\ln",  		PD_FUNCTION   	, 0, 0},
	{"\\log",  		PD_FUNCTION   	, 0, 0},
	{"\\min",  		PD_FUNCTION   	, 0, 0},
	{"\\max",  		PD_FUNCTION   	, 0, 0},
	{"\\sin",  		PD_FUNCTION   	, 0, 0},
	{"\\cos",  		PD_FUNCTION   	, 0, 0},
	{"\\tan",  		PD_FUNCTION   	, 0, 0},
	{"\\cot",  		PD_FUNCTION   	, 0, 0},
	{"\\arcsin",	PD_FUNCTION   	, 0, 0},
	{"\\arccos",	PD_FUNCTION   	, 0, 0},
	{"\\arctan",	PD_FUNCTION   	, 0, 0},
	{"\\arccot",	PD_FUNCTION   	, 0, 0},
	{"\\sinh", 		PD_FUNCTION   	, 0, 0},
	{"\\cosh", 		PD_FUNCTION   	, 0, 0},
	{"\\tanh", 		PD_FUNCTION   	, 0, 0},
	{"\\coth", 		PD_FUNCTION   	, 0, 0},
	{"\\sec",  		PD_FUNCTION   	, 0, 0},
	{"\\csc",  		PD_FUNCTION   	, 0, 0},
	{"\\it",		PD_SETITALIC	, 0, 0},
	{"\\bf",  		PD_SETBOLD		, 0, 0},
	{"\\rm",  		PD_SETROMAN	, 0, 0},
	{"\\mathrm",	PD_TEXT		, 1, 0},
	{"^",      		PD_SUPER   	, 2, 0},
	{"_",      		PD_SUB     	, 2, 0},
	{"\\\\",      	PD_ENDLINE    	, 0, 0},
	{"\\ ",      	PD_SPACE    	, 0, 0}, /* in monospace fonts small spacing is a minimal one space wide */
	{"\\,",      	PD_NSPACE    	, 0, 0}, /* dummy for no space */
	{"\\-",      	PD_NSPACE    	, 0, 0}, /* what is \- in latex math mode. with me it does not through an arror and I see no change */
	{"\\;",      	PD_SPACE    	, 0, 0},
	{"\\:",      	PD_SPACE    	, 0, 0},
	{"\\quad",      PD_DSPACE    	, 0, 0},
	{"\\qquad",     PD_TSPACE    	, 0, 0},
	{NULL, 			PD_NONE 		, 0, 0},
};

/* context dependent keywords */
const KEYWORD   Envs[] = {
	{"array",  		PD_ARRAY     	, 1, 1},
	{"cases*",  	PD_CASES    	, 0, 1},
	{"cases",  		PD_CASES    	, 0, 1},
	{"pmatrix*",  	PD_PMATRIX    	, 0, 1},
	{"pmatrix",  	PD_PMATRIX    	, 0, 1},
	{"bmatrix*",  	PD_BMATRIX    	, 0, 1},
	{"bmatrix",  	PD_BMATRIX    	, 0, 1},
	{"Bmatrix*",  	PD_BBMATRIX    , 0, 1},
	{"Bmatrix",  	PD_BBMATRIX    , 0, 1},
	{"vmatrix*",  	PD_VMATRIX    	, 0, 1},
	{"vmatrix",  	PD_VMATRIX    	, 0, 1},
	{"matrix*",  	PD_MATRIX    	, 0, 1},
	{"matrix",  	PD_MATRIX    	, 0, 1},
	{"\\begin", 	PD_BEGIN   	, 0, 0},
	{"\\end", 		PD_END   		, 0, 0},
	{"\\hline",  	PD_HLINE     	, 0, 0},
	{NULL, 			PD_NONE		, 0, 0},
};


typedef struct {
	char *name;
	SCALABLE_DELIMITER D;
} DELIMITER;


const DELIMITER   DelTable[] = {
	{"(", DEL_L},
	{")", DEL_R},
	{"[", DEL_LSQ},
	{"]", DEL_RSQ},
	{"{", DEL_LCURL},
	{"}", DEL_RCURL},
	{"<", DEL_LANGLE},
	{">", DEL_RANGLE},
	{"⌈", DEL_LCEIL}, /* note some strings in this table are UTF-8 encoded */
	{"⌉", DEL_RCEIL},
	{"⌊", DEL_LFLOOR},
	{"⌋", DEL_RFLOOR},	
	{"|", DEL_VBAR},
	{"‖", DEL_DVBAR},
	{".", DEL_DOT},
	{"↑", DEL_UPARROW},
	{"↓", DEL_DOWNARROW},
	{"↕", DEL_UPDOWNARROW},
	{"⇑", DEL_DUPARROW},
	{"⇓", DEL_DDOWNARROW},
	{"⇕", DEL_DUPDOWNARROW},
	{"/", DEL_SLASH},
	{"\\backslash", DEL_BACKSLASH}, /* backslash is not substituted by the preprocessor as would collide with the use as an escape character
									 * thus the whole string \backslash remains and needs to be matched */
	{NULL, DEL_NONE}
};

typedef struct {
	char *name;
	unsigned int unicode;
} Symbol;

/* note symbols take presedence over keywords */

const Symbol  Symbols[] = {
/* basic latin */
//	{"\\,",                    0x00020}, /* take spacing out of the preprocessor */
//	{"\\;",                    0x00020}, /* take spacing out of the preprocessor */
	{"\\_",                    0x0005F},
	{"\\{",                    0x0007B},
	{"\\}",                    0x0007D},
	{"\\lbrac",                0x0005B},
//	{"\\backslash",            0x0005C}, /* this cannot work as this table is for the pre-processor, it is defined as an argument-less command */
	{"\\rbrac",                0x0005D},
	{"\\sphat",                0x0005E},
	{"\\sptilde",              0x0007E},
/* latin supplement*/
	{"\\cent",                 0x000A2},
	{"\\pounds",               0x000A3},
	{"\\yen",                  0x000A5},
	{"\\neg",                  0x000AC},
	{"\\circledR",             0x000AE},
	{"\\pm",                   0x000B1},
	{"\\Micro",                0x000B5},
	{"\\times",                0x000D7},
	{"\\eth",                  0x000F0},
	{"\\div",                  0x000F7},
/* latin extended A & B*/
	{"\\imath",                0x00131},
	{"\\jmath",                0x00237},
/* combining diacritical marks*/
	{"\\grave",                0x00300},
	{"\\`",                    0x00300},
	{"\\acute",                0x00301},
	{"\\'",                    0x00301},
	{"\\hat",                  0x00302},
	{"\\^",                    0x00302},
	{"\\tilde",                0x00303},
	{"\\~",                    0x00303},
	{"\\utfbar",               0x00304}, 
	{"\\utfoverline",          0x00305},
	{"\\breve",                0x00306},
	{"\\dot",                  0x00307}, 
	{"\\ddot",                 0x00308}, 
	{"\\\"",                   0x00308}, 
	{"\\mathring",             0x0030A}, 
	{"\\H",                    0x0030B},
	{"\\check",                0x0030C},
	{"\\c", 				   0x00327}, 
	{"\\k", 				   0x00328}, 
	{"\\utilde",               0x00330},
	{"\\utfunderbar",          0x00331},
	{"\\utfunderline",         0x00332}, 
	{"\\l",                    0x00337}, 
	{"\\not",                  0x00338}, 
/* hat and bar are made scalable */
/* greek symbols */
	/* upper case */
	{"\\Gamma",                0x00393},
	{"\\Delta",                0x00394},
	{"\\Theta",                0x00398},
	{"\\Lambda",               0x0039B},	
	{"\\Xi",                   0x0039E},
	{"\\Pi",                   0x003A0},
	{"\\Sigma",                0x003A3},
	{"\\Upsilon",              0x003A5},
	{"\\Phi",                  0x003A6},
	{"\\Psi",                  0x003A8},
	{"\\Omega",                0x003A9},
	
	/* lower case */
	{"\\alpha",                0x003B1},
	{"\\beta",                 0x003B2},
	{"\\gamma",                0x003B3},
	{"\\delta",                0x003B4},
	{"\\varepsilon",           0x003B5},
	{"\\epsilon",              0x003F5},
	{"\\backepsilon",          0x003F6},
	{"\\zeta",                 0x003B6},
	{"\\eta",                  0x003B7},
	{"\\theta",                0x003B8},
	{"\\iota",                 0x003B9},
	{"\\kappa",                0x003BA},
	{"\\lambda",               0x003BB},
	{"\\mu",                   0x003BC},
	{"\\nu",                   0x003BD},
	{"\\Nu",                   0x0039D},
	{"\\xi",                   0x003BE},
	{"\\pi",                   0x003C0},
	{"\\rho",                  0x003C1},
	{"\\varrho",               0x003F1},
	{"\\sigma",                0x003C3},
	{"\\varsigma",             0x003C2},
	{"\\tau",                  0x003C4},
	{"\\upsilon",              0x003C5},
	{"\\varphi",               0x1D711},
	{"\\chi",                  0x003C7},
	{"\\psi",                  0x003C8},
	{"\\omega",                0x003C9},
	{"\\varbeta",              0x003D0},
	{"\\vartheta",             0x003D1},
	{"\\phi",                  0x003D5},
	{"\\varpi",                0x003D6},
	{"\\Qoppa",                0x003D8},
	{"\\qoppa",                0x003D9},
	{"\\Stigma",               0x003DA},
	{"\\stigma",               0x003DB},
	{"\\Digamma",              0x003DC},
	{"\\digamma",              0x003DD},
	{"\\Koppa",                0x003DE},
	{"\\koppa",                0x003DF},
	{"\\Sampi",                0x003E0},
	{"\\sampi",                0x003E1},
/* general punktuation */
//	{"\\quad",                 0x02001},
	{"\\|",                    0x02016},
	{"\\dagger",               0x02020},
	{"\\ddagger",              0x02021},
	{"\\ldots",                0x02026},
	{"\\prime",                0x02032},
	{"\\second",               0x02033},
	{"\\third",                0x02034},
	{"\\backprime",            0x02035},
	{"\\cat",                  0x02040},
	{"\\fourth",               0x02057},
//	{"\\:",                    0x02001}, /* this should be medspace U0x0205F, however, I need fixed spaced fonts so we make it a full space */
//	{"\\ ",                    0x02001}, 
/* combining diacritical marks for symbols, it seems with me these symbols are treated as full chacaters and not combining marks as should be */
	{"\\lvec",                 0x020D0},
	{"\\Lvec",                 0x020D6},
	{"\\vec",                  0x020D7},
	{"\\dddot",                0x020DB}, 
	{"\\ddddot",               0x020DC}, 
	{"\\overleftrightarrow",   0x020E1}, 
/* Letterlike Symbols */
/*some symbols require a latex command structure, those I leave out here */
	{"\\Euler",   			   0x02107}, 
	{"\\hslash",   			   0x0210F}, 
	{"\\Im",  	 			   0x02111}, 
	{"\\ell",  	 			   0x02113}, 
	{"\\wp",  	 			   0x02118}, 
	{"\\Re",  	 			   0x0211C}, 
	{"\\tcohm",  	 		   0x02126}, 
	{"\\mho",	  	 		   0x02127}, 
	{"\\Angstroem",	 		   0x0212B}, 
	{"\\Finv",	  	 		   0x02132},  
	{"\\aleph",  	 		   0x02135},  
	{"\\beth",  	 		   0x02136},  
	{"\\gimel",  	 		   0x02137},  
	{"\\daleth",  	 		   0x02138},  
	{"\\Yup",  	 			   0x02144},  
	{"\\CapitalDifferentialD", 0x02145}, 
	{"\\DifferentialD",		   0x02146},  
	{"\\ExponetialE",		   0x02147},  
	{"\\ComplexI",			   0x02148},  
	{"\\ComplexJ",			   0x02149}, 
	{"\\invamp",			   0x0214B}, 
	
/* arrows */
	{"\\leftarrow",            0x02190},
	{"\\uparrow",              0x02191},
	{"\\to",           		   0x02192}, 
	{"\\rightarrow",           0x02192},
	{"\\downarrow",            0x02193},
	{"\\leftrightarrow",       0x02194},
	{"\\updownarrow",          0x02195},
	{"\\nwarrow",              0x02196},
	{"\\nearrow",              0x02197},
	{"\\searrow",              0x02198},
	{"\\swarrow",              0x02199},
	{"\\nleftarrow",           0x0219A},
	{"\\nrightarrow",          0x0219B},
	{"\\twoheadleftarrow",     0x0219E},
	{"\\twoheadrightarrow",    0x021A0},
	{"\\leftarrowtail",        0x021A2},
	{"\\rightarrowtail",       0x021A3},
	{"\\mapsfrom",             0x021A4},
	{"\\MapsUp",               0x021A5},
	{"\\mapsto",               0x021A6},
	{"\\MapsDown",             0x021A7},
	{"\\hookleftarrow", 0x021A9},
	{"\\hookrightarrow", 0x021AA},
	{"\\looparrowleft", 0x021AB},
	{"\\looparrowright", 0x021AC},
	{"\\leftrightsquigarrow", 0x021AD},
	{"\\nleftrightarrow", 0x021AE},
	{"\\lightning", 0x021AF},
	{"\\Lsh", 0x021B0},
	{"\\Rsh", 0x021B1},
	{"\\dlsh", 0x021B2},
	{"\\drsh", 0x021B3},
	{"\\curvearrowleft", 0x021B6},
	{"\\curvearrowright", 0x021B7},
	{"\\circlearrowleft", 0x021BA},
	{"\\circlearrowright", 0x021BB},
	{"\\leftharpoonup", 0x021BC},
	{"\\leftharpoondown", 0x021BD},
	{"\\upharpoonright", 0x021BE},
	{"\\upharpoonleft", 0x021BF},
	{"\\rightharpoonup", 0x021C0},
	{"\\rightharpoondown", 0x021C1},
	{"\\downharpoonright", 0x021C2},
	{"\\downharpoonleft", 0x021C3},
	{"\\rightleftarrows", 0x021C4},
	{"\\updownarrows", 0x021C5},
	{"\\leftrightarrows", 0x021C6},
	{"\\leftleftarrows", 0x021C7},
	{"\\upuparrows", 0x021C8},
	{"\\rightrightarrows", 0x021C9},
	{"\\downdownarrows", 0x021CA},
	{"\\leftrightharpoons", 0x021CB},
	{"\\rightleftharpoons", 0x021CC},
	{"\\nLeftarrow", 0x021CD},
	{"\\nLeftrightarrow", 0x021CE},
	{"\\nRightarrow", 0x021CF},
	{"\\Leftarrow", 0x021D0},
	{"\\Uparrow", 0x021D1},
	{"\\Rightarrow", 0x021D2},
	{"\\Downarrow", 0x021D3},
	{"\\Leftrightarrow", 0x021D4},
	{"\\Updownarrow", 0x021D5},
	{"\\Nwarrow", 0x021D6},
	{"\\Nearrow", 0x021D7},
	{"\\Searrow", 0x021D8},
	{"\\Swarrow", 0x021D9},
	{"\\Lleftarrow", 0x021DA},
	{"\\Rrightarrow", 0x021DB},
	{"\\leftsquigarrow", 0x021DC},
	{"\\rightsquigarrow", 0x021DD},
	{"\\dashleftarrow", 0x021E0},
	{"\\dashrightarrow", 0x021E2},
	{"\\LeftArrowBar", 0x021E4},
	{"\\RightArrowBar", 0x021E5},
	{"\\downuparrows", 0x021F5},
	{"\\pfun", 0x021F8},
	{"\\ffun", 0x021FB},
	{"\\leftarrowtriangle", 0x021FD},
	{"\\rightarrowtriangle", 0x021FE},
	{"\\leftrightarrowtriangle", 0x021FF},	/* to be continued */
	
	/* mathematical operators */
	{"\\forall", 0x02200},
	{"\\complement", 0x02201},
	{"\\partialup", 0x02202},
	{"\\exists", 0x02203},
	{"\\nexists", 0x02204},
	{"\\varnothing", 0x02205},
	{"\\nabla", 0x02207},
	{"\\in", 0x02208},
	{"\\notin", 0x02209},
	{"\\ni", 0x0220B},
	{"\\nni", 0x0220C},
	{"\\utfprod", 0x0220F},
	{"\\coprod", 0x02210},
	{"\\utfsum", 0x02211},
	{"\\mp", 0x02213},
	{"\\dotplus", 0x02214},
	{"\\slash", 0x02215},
	{"\\smallsetminus", 0x02216},
	{"\\ast", 0x02217},
	{"\\circ", 0x02218},
	{"\\bullet", 0x02219},	
	{"\\utfsqrt", 0x0221A},
	{"\\utfsqrt[3]", 0x0221B},
	{"\\utfsqrt[4]", 0x0221C},
	{"\\propto", 0x0221D},
	{"\\infty", 0x0221E},
	{"\\rightangle", 0x0221F},
	{"\\angle", 0x02220},
	{"\\measuredangle", 0x02221},
	{"\\sphericalangle", 0x02222},
	{"\\mid", 0x02223},
	{"\\nmid", 0x02224},
	{"\\parallel", 0x02225},
	{"\\nparallel", 0x02226},
	{"\\wedge", 0x02227},
	{"\\vee", 0x02228},
	{"\\cap", 0x02229},
	{"\\cup", 0x0222A},
	{"\\utfint", 0x0222B},
	{"\\utfiint", 0x0222C},
	{"\\utfiiint", 0x0222D},
	{"\\utfoint", 0x0222E},
	{"\\utfoiint", 0x0222F},
	{"\\utfoiiint", 0x02230},
	{"\\varointclockwise", 0x02232},
	{"\\ointctrclockwise", 0x02233},
	{"\\therefore", 0x02234},
	{"\\because", 0x02235},
	{"\\Proportion", 0x02237},
	{"\\eqcolon", 0x02239},
	{"\\sim", 0x0223C},
	{"\\backsim", 0x0223D},
	{"\\AC", 0x0223F},
	{"\\wr", 0x02240},
	{"\\nsim", 0x02241},
	{"\\eqsim", 0x02242},
	{"\\simeq", 0x02243},
	{"\\nsimeq", 0x02244},
	{"\\cong", 0x02245},
	{"\\ncong", 0x02247},
	{"\\approx", 0x02248},
	{"\\napprox", 0x02249},
	{"\\approxeq", 0x0224A},
	{"\\asymp", 0x0224D},
	{"\\Bumpeq", 0x0224E},
	{"\\bumpeq", 0x0224F},
	{"\\doteq", 0x02250},
	{"\\Doteq", 0x02251},
	{"\\fallingdotseq", 0x02252},
	{"\\risingdotseq", 0x02253},
	{"\\coloneq", 0x02254},
	{"\\eqcolon", 0x02255},
	{"\\eqcirc", 0x02256},
	{"\\circeq", 0x02257},
	{"\\corresponds", 0x02259},
	{"\\triangleq", 0x0225C},
	{"\\neq", 0x02260},
	{"\\equiv", 0x02261},
	{"\\nequiv", 0x02262},
	{"\\leq", 0x02264},
	{"\\geq", 0x02265},
	{"\\leqq", 0x02266},
	{"\\geqq", 0x02267},
	{"\\lneqq", 0x02268},
	{"\\gneqq", 0x02269},
	{"\\ll", 0x0226A},
	{"\\gg", 0x0226B},
	{"\\between", 0x0226C},
	{"\\notasymp", 0x0226D},
	{"\\nless", 0x0226E},
	{"\\ngtr", 0x0226F},
	{"\\nleq", 0x02270},
	{"\\ngeq", 0x02271},
	{"\\lesssim", 0x02272},
	{"\\gtrsim", 0x02273},
	{"\\NotLessTilde", 0x02274},
	{"\\NotGreaterTilde", 0x02275},
	{"\\lessgtr", 0x02276},
	{"\\gtrless", 0x02277},
	{"\\NotGreaterLess", 0x02279},
	{"\\prec", 0x0227A},
	{"\\succ", 0x0227B},
	{"\\preccurlyeq", 0x0227C},
	{"\\succcurlyeq", 0x0227D},
	{"\\precsim", 0x0227E},
	{"\\succsim", 0x0227F},
	{"\\nprec", 0x02280},
	{"\\nsucc", 0x02281},
	{"\\subset", 0x02282},
	{"\\supset", 0x02283},
	{"\\nsubset", 0x02284},
	{"\\nsupset", 0x02285},
	{"\\subseteq", 0x02286},
	{"\\supseteq", 0x02287},
	{"\\nsubseteq", 0x02288},
	{"\\nsupseteq", 0x02289},
	{"\\subsetneq", 0x0228A},
	{"\\supsetneq", 0x0228B},
	{"\\uplus", 0x0228E},
	{"\\sqsubset", 0x0228F},
	{"\\sqsupset", 0x02290},
	{"\\sqsubseteq", 0x02291},
	{"\\sqsupseteq", 0x02292},
	{"\\sqcap", 0x02293},
	{"\\sqcup", 0x02294},
	{"\\oplus", 0x02295},
	{"\\ominus", 0x02296},
	{"\\otimes", 0x02297},
	{"\\oslash", 0x02298},
	{"\\odot", 0x02299},
	{"\\circledcirc", 0x0229A},
	{"\\circledast", 0x0229B},
	{"\\circleddash", 0x0229D},
	{"\\boxplus", 0x0229E},
	{"\\boxminus", 0x0229F},
	{"\\boxtimes", 0x022A0},
	{"\\boxdot", 0x022A1},
	{"\\vdash", 0x022A2},
	{"\\dashv", 0x022A3},
	{"\\top", 0x022A4},
	{"\\bot", 0x022A5},
	{"\\models", 0x022A7},
	{"\\vDash", 0x022A8},
	{"\\Vdash", 0x022A9},
	{"\\Vvdash", 0x022AA},
	{"\\VDash", 0x022AB},
	{"\\nvdash", 0x022AC},
	{"\\nvDash", 0x022AD},
	{"\\nVdash", 0x022AE},
	{"\\nVDash", 0x022AF},
	{"\\vartriangleleft", 0x022B2},
	{"\\vartriangleright", 0x022B3},
	{"\\trianglelefteq", 0x022B4},
	{"\\trianglerighteq", 0x022B5},
	{"\\multimapdotbothA", 0x022B6},
	{"\\multimapdotbothB", 0x022B7},
	{"\\multimap", 0x022B8},
	{"\\intercal", 0x022BA},
	{"\\veebar", 0x022BB},
	{"\\barwedge", 0x022BC},
	{"\\bigwedge", 0x022C0},
	{"\\bigvee", 0x022C1},
	{"\\bigcap", 0x022C2},
	{"\\bigcup", 0x022C3},
	{"\\diamond", 0x022C4},
	{"\\cdot", 0x022C5},
	{"\\star", 0x022C6},
	{"\\divideontimes", 0x022C7},
	{"\\bowtie", 0x022C8},
	{"\\ltimes", 0x022C9},
	{"\\rtimes", 0x022CA},
	{"\\leftthreetimes", 0x022CB},
	{"\\rightthreetimes", 0x022CC},
	{"\\backsimeq", 0x022CD},
	{"\\curlyvee", 0x022CE},
	{"\\curlywedge", 0x022CF},
	{"\\Subset", 0x022D0},
	{"\\Supset", 0x022D1},
	{"\\Cap", 0x022D2},
	{"\\Cup", 0x022D3},
	{"\\pitchfork", 0x022D4},
	{"\\hash", 0x022D5},
	{"\\lessdot", 0x022D6},
	{"\\gtrdot", 0x022D7},
	{"\\lll", 0x022D8},
	{"\\ggg", 0x022D9},
	{"\\lesseqgtr", 0x022DA},
	{"\\gtreqless", 0x022DB},
	{"\\curlyeqprec", 0x022DE},
	{"\\curlyeqsucc", 0x022DF},
	{"\\npreceq", 0x022E0},
	{"\\nsucceq", 0x022E1},
	{"\\nsqsubseteq", 0x022E2},
	{"\\nsqsupseteq", 0x022E3},
	{"\\lnsim", 0x022E6},
	{"\\gnsim", 0x022E7},
	{"\\precnsim", 0x022E8},
	{"\\succnsim", 0x022E9},
	{"\\ntriangleleft", 0x022EA},
	{"\\ntriangleright", 0x022EB},
	{"\\ntrianglelefteq", 0x022EC},
	{"\\ntrianglerighteq", 0x022ED},
	{"\\vdots", 0x022EE},
	{"\\cdots", 0x022EF},
	{"\\iddots", 0x022F0},
	{"\\ddots", 0x022F1},
	{"\\barin", 0x022F6},	
	/* misc technical */
	{"\\diameter", 0x02300},
	{"\\lceil", 0x02308},
	{"\\rceil", 0x02309},
	{"\\lfloor", 0x0230A},
	{"\\rfloor", 0x0230B},
	{"\\invneg", 0x02310},
	{"\\wasylozenge", 0x02311},
	{"\\ulcorner", 0x0231C},
	{"\\urcorner", 0x0231D},
	{"\\llcorner", 0x0231E},
	{"\\lrcorner", 0x0231F},
	{"\\frown", 0x02322},
	{"\\smile", 0x02323},
	{"\\APLinv", 0x02339},
	{"\\notslash", 0x0233F},
	{"\\notbackslash", 0x02340},
	{"\\APLleftarrowbox", 0x02347},
	{"\\APLrightarrowbox", 0x02348},
	{"\\APLuparrowbox", 0x02350},
	{"\\APLdownarrowbox", 0x02357},
	{"\\APLcomment", 0x0235D},
	{"\\APLinput", 0x0235E},
	{"\\APLlog", 0x0235F},
	{"\\overparen", 0x023DC},
	{"\\underparen", 0x023DD},
	{"\\overbrace", 0x023DE},
	{"\\underbrace", 0x023DF},	
	/* geometric shapes */
	{"\\bigtriangleup", 0x025B3},
	{"\\blacktriangleup", 0x025B4},
	{"\\smalltriangleup", 0x025B5},
	{"\\RHD", 0x025B6},
	{"\\rhd", 0x025B7},
	{"\\blacktriangleright", 0x025B8},
	{"\\smalltriangleright", 0x025B9},
	{"\\bigtriangledown", 0x025BD},
	{"\\blacktriangledown", 0x025BE},
	{"\\smalltriangledown", 0x025BF},
	{"\\LHD", 0x025C0},
	{"\\lhd", 0x025C1},
	{"\\blacktriangleleft", 0x025C2},
	{"\\smalltriangleleft", 0x025C3},
	{"\\Diamondblack", 0x025C6},
	{"\\Diamond", 0x025C7},
	{"\\lozenge", 0x025CA},
	{"\\Circle", 0x025CB},
	{"\\CIRCLE", 0x025CF},
	{"\\LEFTcircle", 0x025D0},
	{"\\RIGHTcircle", 0x025D1},
	{"\\LEFTCIRCLE", 0x025D6},
	{"\\RIGHTCIRCLE", 0x025D7},
	{"\\boxbar", 0x025EB},
	{"\\square", 0x025FB},
	{"\\blacksquare", 0x025FC},
	/* Misc. Symbols */
	{"\\bigstar", 0x02605},
	{"\\Sun", 0x02609},
	{"\\Square", 0x02610},
	{"\\CheckedBox", 0x02611},
	{"\\XBox", 0x02612},
	{"\\steaming", 0x02615},
	{"\\pointright", 0x0261E},
	{"\\skull", 0x02620},
	{"\\radiation", 0x02622},
	{"\\biohazard", 0x02623},
	{"\\yinyang", 0x0262F},
	{"\\frownie", 0x02639},
	{"\\smiley", 0x0263A},
	{"\\blacksmiley", 0x0263B},
	{"\\sun", 0x0263C},
	{"\\rightmoon", 0x0263D},
	{"\\leftmoon", 0x0263E},
	{"\\mercury", 0x0263F},
	{"\\female", 0x02640},
	{"\\earth", 0x02641},
	{"\\male", 0x02642},
	{"\\jupiter", 0x02643},
	{"\\saturn", 0x02644},
	{"\\uranus", 0x02645},
	{"\\neptune", 0x02646},
	{"\\pluto", 0x02647},
	{"\\aries", 0x02648},
	{"\\taurus", 0x02649},
	{"\\gemini", 0x0264A},
	{"\\cancer", 0x0264B},
	{"\\leo", 0x0264C},
	{"\\virgo", 0x0264D},
	{"\\libra", 0x0264E},
	{"\\scorpio", 0x0264F},
	{"\\sagittarius", 0x02650},
	{"\\capricornus", 0x02651},
	{"\\aquarius", 0x02652},
	{"\\pisces", 0x02653},
	{"\\spadesuit", 0x02660},
	{"\\heartsuit", 0x02661},
	{"\\diamondsuit", 0x02662},
	{"\\clubsuit", 0x02663},
	{"\\varspadesuit", 0x02664},
	{"\\varheartsuit", 0x02665},
	{"\\vardiamondsuit", 0x02666},
	{"\\varclubsuit", 0x02667},
	{"\\quarternote", 0x02669},
	{"\\eighthnote", 0x0266A},
	{"\\twonotes", 0x0266B},
	{"\\sixteenthnote", 0x0266C},
	{"\\flat", 0x0266D},
	{"\\natural", 0x0266E},
	{"\\sharp", 0x0266F},
	{"\\recycle", 0x0267B},
	{"\\anchor", 0x02693},
	{"\\swords", 0x02694},
	{"\\warning", 0x026A0},
	{"\\medcirc", 0x026AA},
	{"\\medbullet", 0x026AB},
	/* dingbats */
	{"\\pencil", 0x0270E},
	{"\\checkmark", 0x02713},
	{"\\ballotx", 0x02717},
	{"\\maltese", 0x02720},
	{"\\arrowbullet", 0x027A2},
	/* Misc. Mathematical symbols-A */
	{"\\perp", 0x027C2},
	{"\\Lbag", 0x027C5},
	{"\\Rbag", 0x027C6},
	{"\\Diamonddot", 0x027D0},
	{"\\multimapinv", 0x027DC},
	{"\\llbracket", 0x027E6},
	{"\\rrbracket", 0x027E7},
	{"\\langle", 0x027E8},
	{"\\rangle", 0x027E9},
	{"\\lang", 0x027EA},
	{"\\rang", 0x027EB},
	{"\\lgroup", 0x027EE},
	{"\\rgroup", 0x027EF},
	/* Suppl. Arrows-A*/
	{"\\longleftarrow", 0x027F5},
	{"\\longrightarrow", 0x027F6},
	{"\\longleftrightarrow", 0x027F7},
	{"\\Longleftarrow", 0x027F8},
	{"\\Longrightarrow", 0x027F9},
	{"\\Longleftrightarrow", 0x027FA},
	{"\\longmapsfrom", 0x027FB},
	{"\\longmapsto", 0x027FC},
	{"\\Longmapsfrom", 0x027FD},
	{"\\Longmapsto", 0x027FE},
	/* Suppl. Arrows-B*/
	{"\\psur", 0x02900},
	{"\\Mapsfrom", 0x02906},
	{"\\Mapsto", 0x02907},
	{"\\UpArrowBar", 0x02912},
	{"\\DownArrowBar", 0x02913},
	{"\\pinj", 0x02914},
	{"\\finj", 0x02915},
	{"\\bij", 0x02916},
	{"\\leadsto", 0x02933},
	{"\\leftrightharpoon", 0x0294A},
	{"\\rightleftharpoon", 0x0294B},
	{"\\leftrightharpoonup", 0x0294E},
	{"\\rightupdownharpoon", 0x0294F},
	{"\\leftrightharpoondown", 0x02950},
	{"\\leftupdownharpoon", 0x02951},
	{"\\LeftVectorBar", 0x02952},
	{"\\RightVectorBar", 0x02953},
	{"\\RightUpVectorBar", 0x02954},
	{"\\RightDownVectorBar", 0x02955},
	{"\\DownLeftVectorBar", 0x02956},
	{"\\DownRightVectorBar", 0x02957},
	{"\\LeftUpVectorBar", 0x02958},
	{"\\LeftDownVectorBar", 0x02959},
	{"\\LeftTeeVector", 0x0295A},
	{"\\RightTeeVector", 0x0295B},
	{"\\RightUpTeeVector", 0x0295C},
	{"\\RightDownTeeVector", 0x0295D},
	{"\\DownLeftTeeVector", 0x0295E},
	{"\\DownRightTeeVector", 0x0295F},
	{"\\LeftUpTeeVector", 0x02960},
	{"\\LeftDownTeeVector", 0x02961},
	{"\\leftleftharpoons", 0x02962},
	{"\\upupharpoons", 0x02963},
	{"\\rightrightharpoons", 0x02964},
	{"\\downdownharpoons", 0x02965},
	{"\\leftbarharpoon", 0x0296A},
	{"\\barleftharpoon", 0x0296B},
	{"\\rightbarharpoon", 0x0296C},
	{"\\barrightharpoon", 0x0296D},
	{"\\updownharpoons", 0x0296E},
	{"\\downupharpoons", 0x0296F},
	{"\\strictfi", 0x0297C},
	{"\\strictif", 0x0297D},
	/* Misc. Mathematical symbols-B */
	{"\\VERT", 0x02980},
	{"\\spot", 0x02981},
	{"\\Lparen", 0x02985},
	{"\\Rparen", 0x02986},
	{"\\limg", 0x02987},
	{"\\rimg", 0x02988},
	{"\\lblot", 0x02989},
	{"\\rblot", 0x0298A},
	{"\\circledbslash", 0x029B8},
	{"\\circledless", 0x029C0},
	{"\\circledgtr", 0x029C1},
	{"\\boxslash", 0x029C4},
	{"\\boxbslash", 0x029C5},
	{"\\boxast", 0x029C6},
	{"\\boxcircle", 0x029C7},
	{"\\boxbox", 0x029C8},
	{"\\LeftTriangleBar", 0x029CF},
	{"\\RightTriangleBar", 0x029D0},
	{"\\multimapboth", 0x029DF},
	{"\\blacklozenge", 0x029EB},
	{"\\setminus", 0x029F5},
	{"\\zhide", 0x029F9},
	/* Suppl. Mathematical operators */{"\\bigodot", 0x02A00},
	{"\\bigoplus", 0x02A01},
	{"\\bigotimes", 0x02A02},
	{"\\biguplus", 0x02A04},
	{"\\bigsqcap", 0x02A05},
	{"\\bigsqcup", 0x02A06},
	{"\\varprod", 0x02A09},
	{"\\utfiiiint", 0x02A0C},
	{"\\utffint", 0x02A0F},
	{"\\utfsqint", 0x02A16},
	{"\\Join", 0x02A1D},
	{"\\zcmp", 0x02A1F},
	{"\\zpipe", 0x02A20},
	{"\\zproject", 0x02A21},
	{"\\fcmp", 0x02A3E},
	{"\\amalg", 0x02A3F},
	{"\\doublebarwedge", 0x02A5E},
	{"\\dsub", 0x02A64},
	{"\\rsub", 0x02A65},
	{"\\Coloneqq", 0x02A74},
	{"\\Equal", 0x02A75},
	{"\\Same", 0x02A76},
	{"\\leqslant", 0x02A7D},
	{"\\geqslant", 0x02A7E},
	{"\\lessapprox", 0x02A85},
	{"\\gtrapprox", 0x02A86},
	{"\\lneq", 0x02A87},
	{"\\gneq", 0x02A88},
	{"\\lnapprox", 0x02A89},
	{"\\gnapprox", 0x02A8A},
	{"\\lesseqqgtr", 0x02A8B},
	{"\\gtreqqless", 0x02A8C},
	{"\\eqslantless", 0x02A95},
	{"\\eqslantgtr", 0x02A96},
	{"\\NestedLessLess", 0x02AA1},
	{"\\NestedGreaterGreater", 0x02AA2},
	{"\\leftslice", 0x02AA6},
	{"\\rightslice", 0x02AA7},
	{"\\preceq", 0x02AAF},
	{"\\succeq", 0x02AB0},
	{"\\preceqq", 0x02AB3},
	{"\\succeqq", 0x02AB4},
	{"\\precapprox", 0x02AB7},
	{"\\succapprox", 0x02AB8},
	{"\\precnapprox", 0x02AB9},
	{"\\succnapprox", 0x02ABA},
	{"\\llcurly", 0x02ABB},
	{"\\ggcurly", 0x02ABC},
	{"\\subseteqq", 0x02AC5},
	{"\\supseteqq", 0x02AC6},
	{"\\subsetneqq", 0x02ACB},
	{"\\supsetneqq", 0x02ACC},
	{"\\Top", 0x02AEA},
	{"\\Bot", 0x02AEB},
	{"\\interleave", 0x02AF4},
	{"\\biginterleave", 0x02AFC},
	{"\\sslash", 0x02AFD},
	{"\\talloblong", 0x02AFE},
	/* misc symbols & arrows */
	{"\\blacksquare", 0x02B1B},
	{"\\square", 0x02B1C},
	/* mathematical alphanumeric symbols */
	{"\\partial", 0x1D715},
	/* terminate the table */
	/* modify some emojic characters to full blown emojis , e.g. ☠ → ☠️ (\skull  \rightarrow  \emojify \skull)*/
	{"\\emojify", 0x0FE0F},	
	{NULL,                     0x00000},
};
