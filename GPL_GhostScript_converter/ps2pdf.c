/* GPL Ghostscript is free software; you can redistribute it and/or
   modify it under the terms the GNU General Public License as
   published by the Free Software Foundation, either version 3
   of the License, or (at your option) any later version.
*/

/* Code shamelessly stolen from 
   http://www.ghostscript.com/doc/current/API.htm
   and modified. Compile as follows:
   gcc -o ps2pdf ps2pdf.c gsdll32.lib 
*/   

/* Example of using GS DLL as a ps2pdf converter.  */

#if defined(_WIN32) && !defined(_Windows)
# define _Windows
#endif
#ifdef _Windows
/* add this source to a project with gsdll32.dll, or compile it directly with:
 *   cl -D_Windows -Isrc -Febin\ps2pdf.exe ps2pdf.c bin\gsdll32.lib
 */
# include <windows.h>
# define GSDLLEXPORT __declspec(dllimport)
#endif

#include "ierrors.h"
#include "iapi.h"

void *minst;

int main(int argc, char *argv[])
{
    int code, code1;
    char* gsargv[10];
    int gsargc;
	
	/* Hideous hack without bound checking */
	
	char out_flag[1024] = { "-sOutputFile=" };
	
	if (argc != 2) {
		return 2;
	}
	
	char* dest = out_flag+13;
	const char* src = argv[1];
	
	while (*dest++=*src++)
		;
		
	dest -= 4;
	src = "pdf";
	
	while (*dest++=*src++)
		;	

    gsargv[0] = "ps2pdf";	/* actual value doesn't matter */
    gsargv[1] = "-dNOPAUSE";
    gsargv[2] = "-dBATCH";
    gsargv[3] = "-dSAFER";
    gsargv[4] = "-sDEVICE=pdfwrite";
    gsargv[5] = out_flag;
    gsargv[6] = "-c";
    gsargv[7] = ".setpdfwrite";
    gsargv[8] = "-f";
    gsargv[9] = argv[1];
    gsargc=10;

    code = gsapi_new_instance(&minst, NULL);
    if (code < 0)
	return 1;
    code = gsapi_init_with_args(minst, gsargc, gsargv);
    code1 = gsapi_exit(minst);
    if ((code == 0) || (code == e_Quit))
	code = code1;

    gsapi_delete_instance(minst);

    if ((code == 0) || (code == e_Quit))
	return 0;
    return 1;
}
