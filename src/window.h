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

#ifndef _WINDOW_H
#define _WINDOW_H

#include <stdbool.h>

typedef struct {
	GtkWidget *window;
	GtkWidget *menubar;
	GtkStatusbar *statusBar;
	guint statusBarContext;
	GtkWidget *view;
	GtkTextBuffer *buffer;
} MainWin;

MainWin *create_main_window(void);
void set_main_window_title(bool modified);

#endif /* _WINDOW_H */
