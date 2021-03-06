/*
 *  TextED - GTK+ based simple text editor
 *  Copyright (C) 2004-2005 Tarot Osuji
 *  Copyright (C) 2014 Baltasar
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

const size_t MinWidth = 250;
const size_t MinHeight = 100;

#include "globals.h"
/*
static void cb_scroll_event(GtkAdjustment *adj, GtkWidget *view)
{
	gtk_text_view_place_cursor_onscreen(GTK_TEXT_VIEW(view));
}
*/
MainWin *create_main_window(void)
{
	GtkWidget *window;
	GtkWidget *vbox;
 	GtkWidget *menubar;
 	GtkWidget *sw;
 	GtkWidget *view;
 	GtkWidget *statusBar;
 	guint statusBarContext;
	
	MainWin *mw = g_malloc(sizeof(MainWin));
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window, PACKAGE_NAME);
	
#if GTK_CHECK_VERSION(2, 6, 0)
	gtk_window_set_default_icon_name(PACKAGE);
#else
 	GdkPixbuf *icon = gdk_pixbuf_new_from_file(
		ICONDIR G_DIR_SEPARATOR_S PACKAGE ".png", NULL);
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	if (icon)
		g_object_unref(icon);
#endif
	
	g_signal_connect(G_OBJECT(window), "delete-event",
		G_CALLBACK(on_file_quit), NULL);
	g_signal_connect_after(G_OBJECT(window), "delete-event",
		G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	menubar = create_menu_bar(window);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	
	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
		GTK_SHADOW_IN);
	gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 0);
	
	view = create_text_view();
	gtk_container_add(GTK_CONTAINER(sw), view);

	statusBar = gtk_statusbar_new();
	statusBarContext = gtk_statusbar_get_context_id( (GtkStatusbar *) statusBar, "status" );
	gtk_statusbar_push( (GtkStatusbar *) statusBar, statusBarContext, " " );
	gtk_box_pack_start(GTK_BOX(vbox), statusBar, FALSE, FALSE, 0);

	mw->window = window;
	mw->menubar = menubar;
	mw->view = view;
	mw->statusBar = (GtkStatusbar *) statusBar;
	mw->statusBarContext = statusBarContext;
	mw->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

	return mw;
}

void set_main_window_title(bool modified)
{
	static const char *TitleSeparator = " - ";
	static const char *ModifiedTag = "*";
	gchar *fileName;
	gchar *title;
	char *modifiedTag = NULL;

	// Check whether * should be added
	if ( modified ) {
		modifiedTag = ModifiedTag;
	}

	// Get the file name
	fileName = get_file_basename(pub->fi->filename, TRUE);

	// Build the name of the app
	title = g_strconcat( fileName, TitleSeparator, PACKAGE_NAME, modifiedTag, NULL );

	// Set title & clean
	gtk_window_set_title(GTK_WINDOW(pub->mw->window), title);
	g_free(fileName);
	g_free(title);
}

