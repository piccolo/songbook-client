// Copyright (C) 2009-2011 Romain Goffe, Alexandre Dupas
//
// Songbook Creator is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// Songbook Creator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA.
//******************************************************************************

#include "tab-widget.hh"

#include <QAction>
#include <QTabBar>

#include <QDebug>

CTabWidget::CTabWidget()
  : QTabWidget()
  , m_selectionBehaviorOnAdd(SelectCurrent)
{
  setDocumentMode(true);

  updateTabBarVisibility();

  QAction* action;
  action = new QAction(tr("Next tab"), this);
  action->setShortcut(QKeySequence::NextChild);
  connect(action, SIGNAL(triggered()), this, SLOT(next()));
  action = new QAction(tr("Previous tab"), this);
  action->setShortcut(QKeySequence::PreviousChild);
  connect(action, SIGNAL(triggered()), this, SLOT(prev()));
}

CTabWidget::~CTabWidget()
{}

CTabWidget::SelectionBehavior CTabWidget::selectionBehaviorOnAdd() const
{
  return m_selectionBehaviorOnAdd;
}

void CTabWidget::setSelectionBehaviorOnAdd(CTabWidget::SelectionBehavior behavior)
{
  m_selectionBehaviorOnAdd = behavior;
}

void CTabWidget::closeTab(int index)
{
  removeTab(index);
  
  updateTabBarVisibility();
}

int CTabWidget::addTab(QWidget* widget, const QString & label)
{
  int index = QTabWidget::addTab(widget, label);

  updateTabBarVisibility();

  if (selectionBehaviorOnAdd() == SelectNew)
    setCurrentIndex(index);

  return index;
}

void CTabWidget::updateTabBarVisibility()
{
  if (count() > 1)
    tabBar()->show();
  else
    tabBar()->hide();
}

void CTabWidget::next()
{
  setCurrentIndex(currentIndex() + 1);
}

void CTabWidget::prev()
{
  setCurrentIndex(currentIndex() - 1);
}