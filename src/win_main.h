/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/*!
* main.cc
* Copyright (C) Diego Rubin 2011 <rubin.diego@gmail.com>
*
* Gnomato is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Gnomato is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Diego Rubin <rubin.diego@gmail.com>
*
*/

#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <gtkmm.h>
#include <glibmm/i18n.h>
#include <libnotify/notify.h>
#include <iostream>
#include <sstream>

#include "task.h"
#include "dialog_task.h"
#include "dialog_preferences.h"
#include "config.h"

using namespace Gtk;

class WinMain: public Gtk::Window
{
public:
  WinMain(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~WinMain();

  void set_systray(Glib::RefPtr<Gtk::StatusIcon> tray);

protected:

private:

	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
	   ModelColumns()
	   { add(id); add(title); }
	   Gtk::TreeModelColumn< Glib::ustring > id;
	   Gtk::TreeModelColumn< Glib::ustring > title;
	};

  // attributes
  bool showed;
  bool started;
  unsigned int time_elapsed;
  unsigned int minutes,seconds;
  int cycle_number;

  Config configs;

  sigc::slot<bool> timer;
  sigc::connection timeout;
  sigc::connection row_activated;

  Glib::RefPtr<Gtk::Builder> m_refGlade;

  // widgets
  Button *btnStart;
  Button *btnRestart;
  Button *btnAddTask;
  Button *btnDelTask;

  ImageMenuItem *mnuNew;
  ImageMenuItem *mnuQuit;
  ImageMenuItem *mnuPreferences;
  ImageMenuItem *mnuAbout;

  Label *lblDisplay;
  Label *lblCycle;
  Label *lblTaskTitle;

  TreeView *trvTasks;
	ModelColumns mdlColumn;

  Glib::RefPtr<StatusIcon> systray;
  Glib::RefPtr<Gtk::UIManager> mnuSystray;

  Glib::RefPtr<ActionGroup> actMenu;
  Glib::RefPtr<Action> mnuIniciar;
  Glib::RefPtr<ListStore> treTasks;

  //dialogs
  DialogTask *dlgTask;
  AboutDialog *abtDialog;

  // methods
  std::string generate_display();
  std::string generate_cycle();
  void load_tasks();
  void notify(const char *message);

  // callback methods
  virtual void on_systray_activated();
  virtual void on_systray_popup(guint button, guint activate_time);
  virtual void on_button_start_clicked();
  virtual void on_button_restart_clicked();
  virtual void on_treeview_tasks_row_activated(const TreeModel::Path& path,
                                               TreeViewColumn* column);
  virtual void on_button_del_task_clicked();
  virtual bool on_timeout(int timer_number);
  virtual void on_cursor_changed();

  // callback methods - menu
  virtual void on_menu_file_new_task();
  virtual void on_menu_file_quit();
  virtual void on_menu_edit_preferences();
  virtual void on_menu_help_about();
};

#endif //__WIN_MAIN_H_
