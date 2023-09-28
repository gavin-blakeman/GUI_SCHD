//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                financialYear
// SUBSYSTEM:           Financial Year transaction page
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
// OVERVIEW:						Implement the transaction page for financial year management.
//
// HISTORY:             2019-10-20/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/pages/pagePortfolio.h"

  // Standard C++ library header files

#include <utility>

  // Wt framework header files.

#include <Wt/WCheckBox.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

  // msmERP header files

#include "include/application.h"
#include "include/pages/GUI_Templates.h"

namespace transactionPages
{

  /// @brief      Constructor for the class.
  /// @param[in]  parent: The parent object.
  /// @version    2019-10-20/GGB - Function created.

  CPagePortfolio::CPagePortfolio(CApplication &parent, std::unique_ptr<parameters_t> p)
    : CPageTransaction(parent, std::move(p))
  {
  }

  /// @brief      Creates the UI for the business unit view transaction.
  /// @version    2019-10-20/GGB - Function created.

  void CPagePortfolio::createUI()
  {
    auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templatePortfolio));
    result->addFunction("id", &Wt::WTemplate::Functions::id);

    checkBoxEnabled = result->bindWidget("checkBoxEnabled", std::make_unique<Wt::WCheckBox>());

    checkBoxHidden = result->bindWidget("checkBoxHidden", std::make_unique<Wt::WCheckBox>());

    tableViewFinancialYear = result->bindWidget("tableViewFinancialYear", std::make_unique<Wt::WTableView>());
    //tableViewFinancialYear->setModel(modelFinancialYears);

    tableViewPostingPeriods = result->bindWidget("tableViewPostingPeriods", std::make_unique<Wt::WTableView>());
  }


} // namespace transactions
