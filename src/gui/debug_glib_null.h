/*
 * Xiphos Bible Study Tool
 * utilities.h - support functions
 *
 * Copyright (C) 2009 Xiphos Developer Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifdef DEBUG

/* replicating real g_strdup_printf & friends for the sake of our debugging. */
/* this is a total mind game: we redefine the standard use of glib functions */
/* so as to use our internal versions.  our internal versions scan for mis-  */
/* use of %s, i.e. (char*)NULL that should (by rights) cause crashes anyhow. */

#ifdef __cplusplus
extern "C" {
#endif

#define	g_strdup_printf(f, ...)		XI_g_strdup_printf(__FILE__, __LINE__, f, __VA_ARGS__)
#define	g_string_printf(s, f, ...)	XI_g_string_printf(__FILE__, __LINE__, s, f, __VA_ARGS__)

gchar*	XI_g_strdup_printf (const char *filename,
			    int linenumber,
			    const char *format,
			    ...) G_GNUC_PRINTF (3, 4) G_GNUC_MALLOC;

void	XI_g_string_printf (const char *filename,
			    int linenumber,
			    GString *string,
			    const char *format,
			    ...) G_GNUC_PRINTF (4, 5);

#ifdef __cplusplus
}
#endif

/* the code implementing our versions of these is in src/gnome2/gui.c, */
/* expressly because gui.c does not need these functions; ergo, gui.c  */
/* does not #include this file: it gets access to real glib functions. */
/* all other source files include this file to get the replacements.   */

#endif /* DEBUG */
