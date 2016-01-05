/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  1999-2012, University of Amsterdam
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in
       the documentation and/or other materials provided with the
       distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <SWI-Stream.h>
#include <SWI-Prolog.h>
#include <stdio.h>
#include "error.h"
#include "table.h"
#include <string.h>
#ifdef __unix__
#include <errno.h>
#endif

#ifdef __WINDOWS__
#include <malloc.h>

		 /*******************************
		 *	       WINDOWS		*
		 *******************************/

static char *
winerror(int id)
{ char *msg;
  static WORD lang;
  static int lang_initialised = 0;

  if ( !lang_initialised )
    lang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK);

again:
  if ( !FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
		      FORMAT_MESSAGE_IGNORE_INSERTS|
		      FORMAT_MESSAGE_FROM_SYSTEM,
		      NULL,			/* source */
		      id,			/* identifier */
		      lang,
		      (LPTSTR) &msg,
		      0,			/* size */
		      NULL) )			/* arguments */
  { if ( lang_initialised == 0 )
    { lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
      lang_initialised = 1;
      goto again;
    }

    msg = "Unknown Windows error";
  }

  return strcpy((char *)malloc(strlen(msg)+1), msg);
}
#endif

		 /*******************************
		 *            ERRORS		*
		 *******************************/

#if !defined(HAVE_STRERROR) && !defined(__WINDOWS__)
static char *
strerror(int err)
{ extern char *sys_errlist[];

  return sys_errlist[err];
}
#endif


int
error_func(int type, const char *pred, int argi, intptr_t argl)
{ switch(type)
  { case ERR_INSTANTIATION:
    { char buf[1024];

      sprintf(buf, "%s: instantiation error on argument %d", pred, argi);
      return PL_warning(buf);
    }
    case ERR_IO:
    { char buf[1024];

#ifdef __WINDOWS__
      char *msg = winerror(argi);
      sprintf(buf, "%s: IO error %s", pred, msg);
      free(msg);
#else
      sprintf(buf, "%s: IO error %s", pred, strerror(argi));
#endif

      return PL_warning(buf);
    }
  }

  return PL_warning("Table package: unknown error");
}
