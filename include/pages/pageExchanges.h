//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageExchanges
// SUBSYSTEM:           Module: Investement Management
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
// HISTORY:             2023-07-25/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef PAGEEXCHANGES_H
#define PAGEEXCHANGES_H

  // Standard C++ library header files

#include <string>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/models/core/modelCountry.h"
#include "include/pages/pageTransactionView.h"

class CApplication;

namespace transactionPages
{

  class CPageExchanges final : public CPageTransactionView
  {
  public:
    CPageExchanges(CApplication &, std::unique_ptr<parameters_t>);

    static std::unique_ptr<CPageTransaction> createClass(CApplication &a, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPageExchanges>(a, std::move(p));
    }

  private:
    CPageExchanges() = delete;
    CPageExchanges(CPageExchanges const &) = delete;
    CPageExchanges operator=(CPageExchanges const &) = delete;

    Wt::WLineEdit *lineEditStatus = nullptr;

    Wt::WComboBox *comboBoxCountry = nullptr;
    Wt::WLineEdit *lineEditShortText = nullptr;
    Wt::WLineEdit *lineEditLongText = nullptr;
    Wt::WLineEdit *lineEditSuffix;

    std::shared_ptr<models::CModelCountry> modelCountry;

    virtual objectType_t objectTypeID() const override { return OT_IMM_EXCHANGES; }
    virtual void createUI() override;
    virtual void enableEdit(bool) override;
    virtual void clearFields() noexcept override;
    virtual void populateFields() override;
    virtual void processFind() override;
    virtual void processModeFind() override {};
//    virtual void processModeEdit() override {};
//    virtual void processModeCreate() override {};
    virtual void processModeSearch() override {};
    virtual void processModeRecordChange() override {};

  };

}

#endif // PAGEEXCHANGES_H
