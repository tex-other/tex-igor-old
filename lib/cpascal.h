/* cpascal.h: implement various bits of standard Pascal that we use.
   This is the top-level include file for all the web2c-generated C
   programs except TeX and Metafont themselves, which use texmf.h.  */

#ifndef CPASCAL_H
#define CPASCAL_H

/* We must include this first, to resolve many C issues.  */
#include "config.h"


/* Absolute value.  Without the casts to integer here, the Ultrix and
   AIX compilers (at least) produce bad code (or maybe it's that I don't
   understand all the casting rules in C) for tests on memory fields. 
   Specifically, a test in diag_round (in Metafont) on a quarterword
   comes out differently without the cast, thus causing the trap test to
   fail.  (A path at line 86 is constructed slightly differently).  */
#ifdef abs
/* If the system had an abs #define already, get rid of it.  */
#undef abs
#endif
#define	abs(x) ((integer)(x) >= 0 ? (integer)(x) : (integer)-(x))

/* Other standard predefined routines.  */
#define	chr(x)		(x)
#define ord(x)		(x)
#define	odd(x)		((x) % 2)
#define	round(x)	zround ((double) (x))
#define trunc(x)	((integer) (x))

/* File routines.  These are used for both binary and text files, but
   binary is more common.  If you want it 100% right, fix the change
   files to pass the fopen mode to reset in all cases and send me the
   changes; it doesn't matter for Unix, so I'm not going to spend any
   more time on it.  */
#define	reset(f, n)	((f) ? fclose (f) : 0), \
			 (f) = xfopen_pas ((char *) (n), FOPEN_RBIN_MODE)
#define rewrite(f, n)	(f) = xfopen_pas ((char *) (n), FOPEN_WBIN_MODE)
#define flush(f)	(void) fflush (f)

#define read(f, b)	((b) = getc (f))
#define	readln(f)	{ register int c; \
                          while ((c = getc (f)) != '\n' && c != EOF); }

/* We hope this will be efficient than the `x = x - 1' that decr would
   otherwise be translated to.  Likewise for incr.  */
#define	decr(x)		--(x)
#define	incr(x)		++(x)

/* PatGen 2 uses this.  */
#define	input2ints(a, b)  zinput2ints (&a, &b)

/* We need this routine only if TeX is being debugged.  */
#define	input3ints(a, b, c)  zinput3ints (&a, &b, &c)

/* Pascal has no address-of operator, and we need pointers to integers
   to set up the option table.  */
#define addressofint(x)	(&(x))

/* Not all C libraries have fabs, so we'll roll our own.  */
#ifdef fabs
#undef fabs
#endif
#define	fabs(x)		((x) >= 0.0 ? (x) : -(x))

/* The fixwrites program outputs this.  */
#define	Fputs(f, s)	(void) fputs (s, f)

/* Tangle removes underscores from names, but the `struct option'
   structure has a field name with an underscore.  So we have to put it
   back.  Ditto for the other names.  */
#define getoptlongonly	getopt_long_only
#define hasarg		has_arg

/* Same underscore problem.  */
#define PATHMAX		PATH_MAX

/* We need a new type for the argument parsing, too.  */
typedef struct option getoptstruct;

#define printreal(r, n, m)  fprintreal (stdout, r, n, m)
#define	putbyte(x, f)	putc ((char) (x) & 255, f)

#define	toint(x)	((integer) (x))

/* For throwing away input from the file F.  */
#define vgetc(f)	(void) getc (f)

/* If we don't care that strcpy(3) returns A.  Likewise for strcat.  */
#define vstrcpy(a, b)	(void) strcpy (a, b)
#define vstrcat(a, b)	(void) strcat (a, b)

/* Write out elements START through END of BUF to the file F.  */
#define writechunk(f, buf, start, end) \
  (void) fwrite (&buf[start], sizeof (buf[start]), end - start + 1, f)

/* Like fseek(3), but cast the arguments and ignore the return value.  */
#define checkedfseek(f, n, w)  (void) fseek(f, (long) n, (int) w)

/* For faking arrays.  */
typedef unsigned char *pointertobyte;
#define casttobytepointer(e) ((pointertobyte) e)

/* For some initializations of constant strings.  */
typedef char *ccharpointer;

/* For interacting with getopt, etc.  */
#define cinttype int

/* `real' is used for noncritical floating-point stuff.  */
typedef double real;

/* C doesn't distinguish between text files and other files.  */
typedef FILE *text, *file_ptr, *alphafile;

/* `aopenin' is used both for input files and pool files, so it
   needs to know what path to use.  */
#define aopenin(f, p)	open_input (&(f), p, FOPEN_R_MODE)
#define aopenout(f)	open_output (&(f), FOPEN_W_MODE)

/* Closing files is even easier; we don't bother to check the return
   status from fclose(3).  */
#define aclose(f)	if (f) (void) fclose (f)

#ifdef BibTeX
/* See bibtex.ch for why these are necessary.  */
extern FILE *standardinput;
extern FILE *standardoutput;
#endif

#endif /* not CPASCAL_H */
