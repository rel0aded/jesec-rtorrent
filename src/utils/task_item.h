// rTorrent - BitTorrent library
// Copyright (C) 2005, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef RTORRENT_UTILS_TASK_ITEM_H
#define RTORRENT_UTILS_TASK_ITEM_H

#include <list>
#include <sigc++/slot.h>

#include "utils/timer.h"

namespace utils {

// The user is responsible for removing TaskItem from the TaskScheduler.

class TaskItem {
public:
  typedef sigc::slot<void>                                  Slot;
  typedef std::list<std::pair<Timer, TaskItem*> >::iterator iterator;

  TaskItem(Slot s = Slot()) : m_slot(s) {}

  Slot&               get_slot()                    { return m_slot; }
  void                set_slot(Slot s)              { m_slot = s; }

  iterator            get_iterator()                { return m_iterator; }
  const iterator      get_iterator() const          { return m_iterator; }
  void                set_iterator(iterator itr)    { m_iterator = itr; }

  const Timer&        get_time() const              { return m_iterator->first; }

private:
  TaskItem(const TaskItem& t);
  TaskItem&           operator = (const TaskItem& t);

  iterator            m_iterator;
  Slot                m_slot;
};

}

#endif