/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// CompilerProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "y.tab.h"
#include "dirent.h"
#include "compilerLibrary.h"
extern int yylineno;

struct SCmdLineInfos {
public :
	const char*		userPath;
	const char*		frameworkPath;
	const char*		outputPath;
	const char*		parsedFiles[50];
	int				parsedFileCount;
	bool			compileFramework;
	bool			ignoreMode;

	SCmdLineInfos()
		:userPath			(NULL)
		,frameworkPath		(NULL)
		,outputPath			(NULL)
		,parsedFileCount	(0)
		,compileFramework	(false)
		,ignoreMode			(false)
	{
	}
};

bool contains(const char** nameArray, int size, const char* name)
{
	if(nameArray && name)
	{
		for(int i=0 ; i<size ; i++)
		{
			if(strcmp(nameArray[i], name) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool isFile(const char* path)
{
	for(int i = strlen(path); i >= 0 && path[i] != '\\' ; i--) {
		if(path[i] == '.')
		{
			return true;
		}
	}
	return false;
}

bool isValid(const char* path)
{
	for(int i = 0 ; i < (int)strlen(path) ; i++) {
		if(path[i] == '/') {
			return false;
		}
	}
	return true;
}

// Returns the name of the file without its path.
const char* fileName(const char* path)
{
	char buf[500];
	int i = strlen(path);
	for(; i >= 0 && path[i] != '\\' ; i--);
	if(path[i] == '\\')
	{
		memcpy(buf, path + (++i)*sizeof(char), strlen(path) + 1 - i);
		return strdup(buf);
	}
	return strdup(path);
}

u16*  g_stack[500];
u16   g_level;

static const int START_GENERIC = 256;
static const int END_GENERIC = 257;

// a << b > c
// a < b >> c

bool analyzeText(u16* firstChar, u16* lastChar) {
	bool inComment = false;
	// Only < > , . [ ] a-zA-Z0-9
	while (firstChar <= lastChar) {
		bool isValid 
			    = 	(*firstChar == '<') || (*firstChar == '>') || (*firstChar == ',') || 
					(*firstChar == '[') || (*firstChar == ']') || (*firstChar == '.');
						
		isValid = isValid 	|| ((*firstChar >= 'A') && (*firstChar <= 'Z')) 
							|| ((*firstChar >= 'a') && (*firstChar <= 'z')) 
							|| ((*firstChar >= '0') && (*firstChar <= '9'));
								
		isValid = isValid || (*firstChar <= ' ');	// Less than space.
		isValid = isValid || (*firstChar == '@');

		if (*firstChar == '/') {
			if (inComment == false) {
				if ((firstChar < lastChar) && (firstChar[1]=='*')) {
					inComment = true;
					firstChar += 2;
					continue;
				}
			}
		}
		
		if (*firstChar == '*') {
			if (inComment == true) {
				if ((firstChar < lastChar) && (firstChar[1]=='/')) {
					inComment = false;
					firstChar += 2;
					continue;
				}
			}
		}

		if ((isValid == false) && (inComment == false)) {
				return false;
		}

		firstChar++;
	}
		
	return true;
}

bool patchBlock(int level, u16* pChar) {
	if (analyzeText(g_stack[level],pChar-1) == true) {
		*(g_stack[level]-1)	= START_GENERIC;
		*pChar				= END_GENERIC;
		return true;
	} else {
		// Do nothing.
		return false;
	}
}

void patchFile(u16* file, int length) {
	u16* pChar = file;
	while (pChar != &file[length]) {
		if (*pChar == '<') {
			// Guard against a << b > c pattern.
			// << force next > to be non related.
			if ((&pChar[1] != &file[length]) && (pChar[1] == '<')) {
				// Do nothing.
			} else {
				g_stack[g_level++] = pChar+1;
			}
		}
		else
		if (*pChar == '>') {
			if ((&pChar[1] != &file[length]) && (pChar[1] == '>')) {
				if (g_level >= 2) {
					// Perform patch parent FIRST
					// Then decide from patch or not for child
					bool isGeneric = patchBlock(g_level-2, &pChar[1]);
					if (isGeneric) {
						// Patch
						patchBlock(g_level-1, pChar);
					} else {
						// Do nothing.
					}
					g_level -= 2;
				} else if (g_level == 1) {
					g_level--;
				}
			} else {
				if (g_level > 0) {
					g_level--;
					patchBlock(g_level, pChar);
				}
			}
		}
		else
		if (*pChar == 0xD) {
			while (g_level != 0) {
				g_level--;
				patchBlock(g_level, pChar);
			}
		}
			
		pChar++;
	}
}
	
void generate(u16* file, int length, char* result) {
	u16* pChar = file;
	while (pChar != &file[length]) {
		if (*pChar == START_GENERIC) {
			*result++ = '$';
			*result++ = '<';
		} else if (*pChar == END_GENERIC) {
			*result++ = '$';
			*result++ = '>';
		} else {
			*result++ = (char)*pChar;
		}
		pChar++;
	}
	*result++ = 0;
}

const char* preprocess(const char* input, const char*& allocated8Buff) {
	int length = strlen(input) + 1;
	// 1. Allocate u16 buffer
	u16* pu16 = new u16[length];
	u16* fill = pu16;

	// 2. Copy 8->16 bit
	const char* pOrig = input;
	while (*pOrig) {
		*fill++ = *pOrig++;
	}
	*fill++ = 0;

	// 3. Parse
	patchFile(pu16, length);

	// 4. Generate
	char* p8 = new char[length*2];	// Need to allocate more in case of.
	allocated8Buff = p8;
	generate(pu16, length, p8);
	return p8;
}

void recurse(const char* folder, const char** parsedFiles, int parsedFileCount, u32 compilerOptions) {
	DIR *pDIR;
	struct dirent *entry;
	bool ignoreMode = ((compilerOptions & COMPIL_MODE_IGNORE) != 0);
	if (pDIR=opendir(folder)) {
		// Force all the entries in the directory...
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
				char buff[1000];
				sprintf(buff, "%s\\%s",folder, entry->d_name);
				recurse(buff, parsedFiles, parsedFileCount, compilerOptions);
			}
		}
		closedir(pDIR);
    } else {
		// May be a file ?
		int strLen = strlen(folder);
		if (folder[strLen-3]=='.' 
			&& folder[strLen-2]=='c' 
			&& folder[strLen-1]=='s'
			&& (parsedFileCount == 0
				|| (contains(parsedFiles, parsedFileCount, fileName(folder)) != ignoreMode))) {
			fprintf(stderr,"### Try Process File : %s ###\n", folder);
			// Load file in memory
			FILE* pFile = fopen((const char*)folder, "rb");
			if (pFile) {
				fprintf(stderr,"### Do Process File : %s ###\n", folder);
				fseek (pFile, 0, SEEK_END);   // non-portable
				int size=ftell (pFile);

				char* buff = new char[size+1];
				buff[size] = 0; // close file as C string.

				rewind (pFile);
				fread(buff, size, 1, pFile);

				fclose (pFile);

				// Test Header.
				unsigned char* input = (unsigned char*) buff;
				if ((input[0] == 0xEF) && (input[1] == 0xBB) && (input[2] == 0xBF)) {
					input += 3;
				}

				// Pass the stream.
				resetLocalFileInfo();
				yylineno = 1;
				const char* pDelete;
				int result = runCompiler(preprocess((const char*)input,pDelete));
				delete[] pDelete;
				delete[] buff;
			}
			else {
				fprintf(stderr,"### Failed to Open File : %s ###\n", folder);
			}
		}
	}
}

void displayHelp() {
	printf("\n");
	printf("##############################################################\n");
	printf("#                            Help                            #\n");
	printf("##############################################################\n");
	printf("\n");
	printf("* Command line options\n");
	printf("\n");
	printf("-o or -or\n");
	printf("Description : Tells the output path (relative).\n");
	printf("              If no output option is used, the result will be displayed in the console.\n");
	printf("Argument : Output path, including the file name\n");
	printf("\n");
	printf("-oa\n");
	printf("Description :  Tells the output path (absolute).\n");
	printf("               If no output option is used, the result will be displayed in the console.\n");
	printf("Argument : Full output path, including the file name\n");
	printf("\n");
	printf("-user\n");
	printf("Description : Tells the path to the user project directory.\n");
	printf("              If this option is not used, the first command line argument needs to be this path.\n");
	printf("Argument : Full path to the project directory.\n");
	printf("\n");
	printf("-framework\n");
	printf("Description : When a project which uses the framework is compiled, tells the path to the framework directory.\n");
	printf("Argument : Full path to the framework directory.\n");
	printf("\n");
	printf("-compileframework\n");
	printf("Description : Used to compile the framework only.\n");
	printf("              In this case, -framework is not used and -user is the path to the framework.\n");
	printf("Argument : None.\n");
	printf("\n");
	printf("-ignore\n");
	printf("Description : Rather than parsing the mentioned files only, the compiler will parse all the files \n");
	printf("              except the ones which have been enumerated.\n");
	printf("Argument : None.\n");
	printf("\n");
	printf("-h or -help\n");
	printf("Description : Displays this menu.\n");
	printf("Argument : None.\n");
	printf("\n");
	printf("* Compilation process\n");
	printf("\n");
	printf("- Make sure that your C# project compiles in C#.\n");
	printf("- Check that it does not contain restricted functionalities.\n");
	printf("- Launch the compilation. The basic syntax for the command line is :\n");
	printf("\n");
	printf("  CompilerProject.exe <path to the project> [<C# file to parse 1> <C# file to parse 2> <...>] [-o <output file name>]\n");
	printf("\n");
	printf("  If no parsed file is explicited, every C# file of the folder will be recursively parsed.\n");
	printf("  For further explanation, see the description of the command line options above.\n");
	printf("- Place the inline (.inl) files generated by the compiler into the \"inline\" folder of the \"RuntimeLibrary\" folder.\n");
	printf("- If your project uses the game engine framework, you also need to compile it once, as described below.\n");
	printf("\n");
	printf("* How to compile the framework\n");
	printf("\n");
	printf("- Launch the compiler with the following command line :\n");
	printf("\n");
	printf("  CompilerProject.exe <path to the framework folder> -oa <output path> -compileframework\n");
	printf("\n");
	printf("- Include the generated files (framework.h and framework.cpp) in your C++ project.\n");
	printf("- Do not forget to compile the framework again if changes are made in C#.\n");
	printf("\n");
	system("Pause");
}

bool extractArgs(int argc, const char** argv, SCmdLineInfos* infos)
{
	bool relativePath = false;
	int i = 1;

	if(argc < 2) {
		compilerError(ERR_COMMAND_LINE, "No argument for the command line");
		return false;
	}

	//
	//	List of the avalaible options
	//	N.B. : Must remain up-to-date, so does optionCount
	//
	const char* options[] = {
		"-compileframework",
		"-o",
		"-or",
		"-oa",
		"-user",
		"-framework",
		"-ignore",
		"-h",
		"-help",
		// Important : Do not forget to update optionCount
	};
	int optionCount = 9;

	// First, check every argument to make sure that paths are written using '\'
	for(int n = 0 ; n < argc ; n++) {
		if(!isValid(argv[n])) {
			compilerError(ERR_COMMAND_LINE, "Please use '\\' rather than '/'");
			return false;
		}
	}

	if(!contains(argv, argc, "-user")) {
		if(argv[1][0] == '-') {
			compilerError(ERR_COMMAND_LINE, "Since -user is not used, the first argument should be the path to the solution");
		}
		// The first argument is the user path
		infos->userPath = concat(argv[i++]);
	}
	for(; i < argc ; i++) {
		if(argv[i][0] == '-') {
			//
			//	Options
			//
			if(!contains(options, optionCount, argv[i])) {
				compilerError(ERR_COMMAND_LINE, concat2(argv[i], " : unknown command line option"));
				return false;
			}

			//	Options with no argument
			else if(!strcmp(argv[i], "-compileframework")) {				// Recompile the framework
				infos->compileFramework = true;
				if(contains(argv, argc, "-framework")) {
					compilerError(ERR_COMMAND_LINE, "When using -compileframework, use -user instead of -framework to tell the path to the framework");
					return false;
				}
			}
			else if(!strcmp(argv[i], "-ignore")) {							// The enumerated files will be ignored
				infos->ignoreMode = true;
			}
			else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help")) {	// The enumerated files will be ignored
				displayHelp();
			}

			//	Options with one argument
			else if(i + 1 >= argc) {
				compilerError(ERR_COMMAND_LINE, concat2("Missing argument for ", argv[i]));
				return false;
			}
			else if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "-or")) {	// Output path (relative)
				infos->outputPath = concat(argv[++i]);
				relativePath = true;
			}
			else if(!strcmp(argv[i], "-oa")) {								// Output path (absolute)
				infos->outputPath = concat(argv[++i]);
			}
			else if(!strcmp(argv[i], "-user")) {							// User file path
				infos->userPath = concat(argv[++i]);
			} 
			else if(!strcmp(argv[i], "-framework")) {						// Framework file path
				infos->frameworkPath = concat(argv[++i]);
			}

			//	Options with two arguments
			else if(i + 2 >= argc) {
				compilerError(ERR_COMMAND_LINE, concat2("Missing argument for ", argv[i]));
				return false;
			}/*
			else
				...
			*/

			else {
				compilerError(ERR_COMMAND_LINE, concat3("Option ", argv[i], "exists but has not been implemented yet"));
				return false;
			}
		}
		else {
			// Parsed file name
			if(infos->parsedFileCount + 1 > 50) {
				compilerError(ERR_COMMAND_LINE, "The number of selected parsed files cannot be greater than 50");
				return false;
			}
			infos->parsedFiles[infos->parsedFileCount++] = concat(argv[i]);
		}
	}

	if(infos->compileFramework && infos->outputPath) {
		if(isFile(infos->outputPath)) {
			compilerError(ERR_COMMAND_LINE, "When using -compileframework, -o should designate a folder");
			return false;
		}
		if(infos->outputPath[strlen(infos->outputPath) - 1] != '\\') {
			infos->outputPath = concat2(infos->outputPath, "\\");
		}
	}

	if(relativePath) {
		if(infos->userPath[strlen(infos->userPath) - 1] == '\\') {
			infos->outputPath = concat2(infos->userPath, infos->outputPath);
		}
		else{
			infos->outputPath = concat3(infos->userPath, "\\", infos->outputPath);
		}
	}

	return true;
}

u32 getCompilerOptions(SCmdLineInfos* infos) {
	u32 options = 0;
	if(infos->frameworkPath != NULL) {
		options |= COMPIL_USE_FRAMEWORK;
	}
	if(infos->compileFramework) {
		options |= COMPIL_IS_FRAMEWORK;
	}
	if(infos->ignoreMode) {
		options |= COMPIL_MODE_IGNORE;
	}
	return options;
}

int _tmain(int argc, const char* argv[])
{
	u32 compilerOptions;
	SCmdLineInfos* infos = new SCmdLineInfos();

	if(extractArgs(argc, argv, infos)) {
		compilerOptions = getCompilerOptions(infos);

		// Init code generator.
		initBaseType();
		g_noDump = true;
		g_registerClasses = false;
		//
		// Load always needed library.
		//
		recurse("supported.cs", NULL, 0, compilerOptions | ~COMPIL_MODE_IGNORE);
		g_registerClasses = true;
		if((compilerOptions & COMPIL_USE_FRAMEWORK) != 0) {
			// Load the framework librairies
			recurse(infos->frameworkPath, NULL, 0, compilerOptions);
		}
		g_noDump = false;

		recurse(infos->userPath, infos->parsedFiles, infos->parsedFileCount, compilerOptions | ~COMPIL_MODE_IGNORE);
		yylineno = -1; // Do not parse anymore.

		generateOutput(infos->outputPath, compilerOptions);
		freopen( "CON", "w", stdout );
	}
	else {
		system("Pause");
	}
}
