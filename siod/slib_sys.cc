/*  
 *                   COPYRIGHT (c) 1988-1994 BY                             *
 *        PARADIGM ASSOCIATES INCORPORATED, CAMBRIDGE, MASSACHUSETTS.       *
 *        See the source file SLIB.C for more information.                  *

 * Reorganization of files (Mar 1999) by Alan W Black <awb@cstr.ed.ac.uk>

 * System functions

*/
#include <stdio.h>
#include "siod.h"
#include "siodp.h"

static LISP lgetenv(LISP name)
{
    return rintern(getenv(get_c_string(name)));
}

static LISP lsetenv(LISP name,LISP value)
{
    char *entry=walloc(char,strlen(get_c_string(name))+
		       strlen(get_c_string(value))+16);
    sprintf(entry,"%s=%s",get_c_string(name),get_c_string(value));
    putenv(entry);
    return name;
}

static LISP lsystem(LISP name)
{
    system(get_c_string(name));
    return NIL;
}

static LISP lpwd(void)
{
    char *cwd;

    cwd = getcwd(NULL,1024);

    return cintern(cwd);
}

static LISP lchdir(LISP args, LISP env)
{
    (void)env;
    char *home;
    
    if (siod_llength(args) == 0)
    {
	home = getenv("HOME");
	chdir(home);
	return rintern(home);
    }
    else
    {
	chdir(get_c_string(car(args)));
	return (car(args));
    }
}

static LISP lgetpid(void)
{
    return flocons((float)getpid());
}

void init_subrs_sys(void)
{
 init_subr_0("getpid",lgetpid,
 "(getpid)\n\
  Return process id.");
 init_fsubr("cd",lchdir,
 "(cd DIRNAME)\n\
  Change directory to DIRNAME, if DIRNAME is nil or not specified \n\
  change directory to user's HOME directory.");
 init_subr_0("pwd",lpwd,
 "(pwd)\n\
  Returns current directory as a string.");
 init_subr_1("getenv",lgetenv,
 "(getenv VARNAME)\n\
  Returns value of UNIX environment variable VARNAME, or nil if VARNAME\n\
  is unset.");
 init_subr_2("setenv",lsetenv,
 "(setenv VARNAME VALUE)\n\
  Set the UNIX environment variable VARNAME to VALUE.");
 init_subr_1("system",lsystem,
 "(system COMMAND)\n\
  Execute COMMAND (a string) with the UNIX shell.");
}