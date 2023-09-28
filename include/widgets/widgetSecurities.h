//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                widgetSecurities
// SUBSYSTEM:           Investment Management GUI Plugin
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2023 Gavin Blakeman.
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
// HISTORY:             2023-07-23/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef WIDGETSECURITIES_H
#define WIDGETSECURITIES_H

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files

#include <Wt/WContainerWidget.h>
#include <Wt/WTreeView.h>
#include <Wt/WSignal.h>

  // Miscellaneous library header files.

#include <SCL>

  // msmERP header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelExchanges.h"
#include "include/database/models/modelSecurities.h"

namespace widgets
{
  class CWidgetSecurities final : public Wt::WContainerWidget
  {
  public:
    CWidgetSecurities(CApplication &, index_t &);

    void refresh()
    {
      modelSecurities->reload();
    }

    Wt::Signal<index_t> &selectionChanged() { return selectionChanged_; }

  private:
    CWidgetSecurities() = delete;
    CWidgetSecurities(CWidgetSecurities const &) = delete;
    CWidgetSecurities operator=(CWidgetSecurities const &) = delete;

    CApplication &application_;
    index_t &exchangeID_;

    Wt::WComboBox *comboBoxExchange;
    Wt::WTableView *tableViewSecurities;

    std::shared_ptr<models::CModelExchanges> modelExchanges;
    std::shared_ptr<models::CModelSecurities> modelSecurities;

    Wt::Signal<index_t> selectionChanged_;

    void setupUI();



  };
}

#endif // WIDGETSECURITIES_H
