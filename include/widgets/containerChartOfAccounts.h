//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2022 Gavin Blakeman.
//                      This file is part of the msmERP Project
//
//                      msmERP is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      msmERP is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with msmERP.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2022-07-31/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef CONTAINERCHARTOFACCOUNTS_H
#define CONTAINERCHARTOFACCOUNTS_H

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

// Miscellaneous library header files.

#include <SCL>

// msmERP  header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelAccountHierarchy.h"

namespace widgets
{
  class CContainerChartOfAccounts : public Wt::WContainerWidget
  {
  private:
    CContainerChartOfAccounts() = delete;
    CContainerChartOfAccounts(CContainerChartOfAccounts const &) = delete;
    CContainerChartOfAccounts &operator=(CContainerChartOfAccounts const &) = delete;

    CApplication &parent_;

    Wt::WTreeView *treeViewCOA = nullptr;

    std::shared_ptr<models::CModelAccountHierarchy> modelEditChartOfAccounts;

    bool hierarchyLoaded = false;
    Wt::Signal<index_t> selectionChanged_;

    void setupUI();

  public:
    CContainerChartOfAccounts(CApplication &);
    void updateData();

    // Slots

    void accountChanged();

    // Signals

    Wt::Signal<index_t> &selectionChanged() { return selectionChanged_; }

  };
}


#endif // CONTAINERCHARTOFACCOUNTS_H
