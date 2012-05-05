/*  $Id$

    Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 1985-2002, University of Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _ERROR_H_INCLUDED
#define _ERROR_H_INCLUDED

#define ERR_INSTANTIATION 1		/* general badly typed argument */
#define ERR_IO	          2		/* general IO error */

#define error(a,b,c,d) error_func(a,b,c,(intptr_t)(d))

extern int	error_func(int type, const char *pred, int argi, intptr_t argl);

#endif /*_ERROR_H_INCLUDED*/

