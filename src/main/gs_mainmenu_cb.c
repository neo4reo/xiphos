/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

  /*
    * GnomeSword Bible Study Tool
    * gs_mainmenu_cb.c
    * -------------------
    * Tue Aug 21 2001
    * copyright (C) 2000 by Terry Biggs
    * tbiggs@users.sourceforge.net
    *
 */
 
 /*
    *  This program is free software; you can redistribute it and/or modify
    *  it under the terms of the GNU General Public License as published by
    *  the Free Software Foundation; either version 2 of the License, or
    *  (at your option) any later version.
    *
    *  This program is distributed in the hope that it will be useful,
    *  but WITHOUT ANY WARRANTY; without even the implied warranty of
    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    *  GNU Library General Public License for more details.
    *
    *  You should have received a copy of the GNU General Public License
    *  along with this program; if not, write to the Free Software
    *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>
#include <gtkhtml/gtkhtml.h>

#include  <gal/shortcut-bar/e-shortcut-bar.h>
#include <gal/e-paned/e-hpaned.h>

#include "gs_mainmenu_cb.h"
#include "gs_gnomesword.h"
#include "gs_menu.h"
#include "sword.h"
#include "gs_viewdict_dlg.h"
#include "gs_history.h"
#include "gs_shortcutbar.h"
#include "support.h"
#include "gs_file.h"
#include "about_gnomesword.h"

/******************************************************************************
 * externals
******************************************************************************/
extern SETTINGS 
	*settings;	/* pointer to settings structure - (declared in gs_gnomesword.c) */
extern gboolean 
	firstsearch,	/* search dialog is not running when TRUE */
	firstLE;	  /* ListEditor in not running when TRUE */
extern GtkWidget 
	*listeditor;		/* pointer to ListEditor */
extern gint 
	iquickmarks;	/* number of items in bookmark menu  -- declared in filestuff.cpp */
	
/******************************************************************************

******************************************************************************/

/**********************************************************************************
 * main menu call backs
 * popup menu call backs are located in gs_popup_cb.c
 **********************************************************************************/
/******************************************************************************
 *on_help_contents_activate - user chose help item
******************************************************************************/
void
on_help_contents_activate(GtkMenuItem * menuitem, gpointer user_data)
{       
	pid_t pid;	
	
	if ((pid = fork ()) == 0)
	{
		execlp ("gnome-help-browser", "gnome-help-browser",
			"ghelp:gnomesword");
		g_error (_("Cannot launch gnome-help-browser"));
	}	
}

/******************************************************************************
 *on_mnuHistoryitem1_activate - user chose an history item
******************************************************************************/
void
on_mnuHistoryitem1_activate(GtkMenuItem * menuitem, gpointer user_data)
{       	
	changeverseHistory(atoi((gchar *)user_data));
}


/*** display - The SWORD Project - about information ***/
void
on_about_the_sword_project1_activate(GtkMenuItem * menuitem,
				     gpointer user_data)
{
	GtkWidget *dlg, *text1, *version_label;
	const char *ver;
	gchar version[40];
	
	dlg = gui_create_about_sword();
	text1 = lookup_widget(dlg, "txtAboutSword");
	version_label = lookup_widget(dlg, "version_label");
	gtk_text_set_word_wrap(GTK_TEXT(text1), TRUE);	
	/* get sword version */
	ver = getSwordVerionSWORD();	
	sprintf(version,"Sword-%s",ver);
	gtk_label_set_text(GTK_LABEL(version_label),version);
	gtk_widget_show(dlg);
}


/*** display daily devotion in shortcut bar viewer ***/
void
on_daily_devotion1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{	
	displayDevotional();
}


/*** toogle global options in main text window ***/
void on_global_options_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	globaloptionsSWORD((gchar *)user_data, MAIN_TEXT_WINDOW, GTK_CHECK_MENU_ITEM(menuitem)->active,TRUE);	
}


/*** open preferences dialog ***/
void on_preferences1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	loadpreferencemodsSWORD();
}


/*** display search group in shortcut bar ***/
void on_search1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	SETTINGS *s;
	EShortcutBar *bar1;
		
	s = settings;
	bar1 = E_SHORTCUT_BAR(s->shortcut_bar);
	if(!s->showshortcutbar){
		on_btnSB_clicked(NULL,s);
	}
	e_group_bar_set_current_group_num(E_GROUP_BAR(bar1),
						 s->searchbargroup,
						 TRUE);
}


/*** toogle autosave of personal notes ***/
void
on_auto_save_notes1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	setautosave(GTK_CHECK_MENU_ITEM(menuitem)->active);
}



/*** toogle between verse and paragraph style ***/
void on_verse_style1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	setversestyleSWORD(GTK_CHECK_MENU_ITEM(menuitem)->active); 
}


/*** toogle display of interlinear page ***/
void
on_show_interlinear_page1_activate(GtkMenuItem * menuitem,
				   gpointer user_data)
{
	showIntPage(settings->app, GTK_CHECK_MENU_ITEM(menuitem)->active);
}


/*** do a nice orderly shut down and exit gnomesword ***/
void on_exit1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	shutdownSWORD();
}


/*** remove all items from history list ***/
void on_clear1_activate(GtkMenuItem * menuitem,	//-- clear history menu
			gpointer user_data)
{
	clearhistory(settings->app,GTK_WIDGET(settings->shortcut_bar));
}


/*** display gnomesword about dialog ***/
void
on_about_gnomesword1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *AboutBox;

	AboutBox = gui_create_about_gnomesword();
	gtk_widget_show(AboutBox);
}






/******   end of file   ******/
