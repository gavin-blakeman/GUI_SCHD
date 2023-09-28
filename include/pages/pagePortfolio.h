//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pagePortfolio
// SUBSYSTEM:           Portfolio information
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
// HISTORY:             2023-07-20/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef PAGEPORTFOLIO_H
#define PAGEPORTFOLIO_H

  // Standard C++ library header files

#include <memory>

  // Wt framework header files.

#include <Wt/WTableView.h>

  // msmERP header files.

#include "include/database/models/modelPortfolio.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/pages/page_IMM_transaction.h"

namespace transactionPages
{
  class CPagePortfolio: public CPageTransaction
  {
  public:
    CPagePortfolio(CApplication &, std::unique_ptr<parameters_t> p);

    static std::unique_ptr<CPageTransaction> createClass(CApplication &a, std::unique_ptr<parameters_t> p)
    {
      return std::make_unique<CPagePortfolio>(a, std::move(p));
    }

  protected:
    virtual objectType_t objectTypeID() const override { return OT_IMM_PORTFOLIO; }
    virtual void createUI() override;
    virtual bool allowEdit() const override{};
    virtual void enableEdit(bool) override{};
    virtual void processSaveData() override{};
    virtual void saveComplete() override{};
    virtual void clearFields() override{};
    virtual void populateFields() override{};
    virtual void processFind() override{};
    virtual void processModeFind() override {};
    virtual void processModeEdit() override {};
    virtual void processModeCreate() override {};
    virtual void processModeSearch() override {};
    virtual void processModeRecordChange() override {};
  private:
    CPagePortfolio() = delete;
    CPagePortfolio(CPagePortfolio const &) = delete;
    CPagePortfolio operator=(CPagePortfolio const &) = delete;

    Wt::WCheckBox *checkBoxEnabled = nullptr;
    Wt::WCheckBox *checkBoxHidden = nullptr;
    Wt::WTableView *tableViewFinancialYear = nullptr;
    Wt::WTableView *tableViewPostingPeriods = nullptr;

    //std::shared_ptr<models::CModelFinancialYears> modelFinancialYears;

    bool enabled_ = false;
    bool hidden_ = false;
  };
} // namespace transactions

#endif // PAGEPORTFOLIO_H
