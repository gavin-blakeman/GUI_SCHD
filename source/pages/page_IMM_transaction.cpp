//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                pageSecurityTransaction
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

#include "include/pages/page_IMM_transaction.h"

  // Standard C++ library header files

#include <chrono>
#include <utility>

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDateEdit.h>
#include <Wt/WDoubleSpinBox.h>
#include <Wt/WTable.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

  // Miscellaneous libraries

#include <boost/locale.hpp>
#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/pages/GUI_Templates.h"
#include "include/database/tables/core/tbl_businessTransactions.h"
#include "include/database/tables/tbl_imm_transactionTypes.h"
#include "include/database/views/viewTransaction.h"

namespace transactionPages
{

  /// @brief Constructor for the class.
  /// @param[in] parent: The parent object.
  /// @version 2022-07-29/GGB - Function created.

  CPageIMMTransaction::CPageIMMTransaction(CApplication &parent, std::unique_ptr<parameters_t> p)
    : CPageTransactionView(parent, std::move(p))
  {
    record_ = std::make_unique<views::CViewTransaction>(parent);

    modelTransactionType = std::make_shared<models::CModelComboBox<tindex_t>>(application());
    database::tbl_imm_transactionTypes::createModel(application(), *modelTransactionType);

    modelPortfolio = std::make_shared<models::CModelPortfolio>(application(), models::CModelPortfolio::MU_COMBO_NULL);
    modelPortfolio->reload();

    modelExchanges = std::make_shared<models::CModelExchanges>(application(), models::CModelExchanges::MU_COMBO_NULL);
    modelExchanges->reload();

    modelSecurities= std::make_shared<models::CModelSecurities>(application(), models::CModelSecurities::MU_COMBO_NULL, exchangeID_);
    modelSecurities->reload();

  }

  /// @brief    Clears all the fields.
  /// @throws
  /// @version  2023-07-25/GGB - Function created.

  void CPageIMMTransaction::clearFields()
  {
    comboBoxPortfolio->setCurrentIndex(0);
    comboBoxSecurity->setCurrentIndex(0);
    comboBoxTransactionType->setCurrentIndex(0);
    spinBoxPrice->setValue(0);
    spinBoxQuantity->setValue(0);
  }

  /// @brief      Creates the UI for the business unit view transaction.
  /// @throws
  /// @version    2019-11-09/GGB - Function created.

  void CPageIMMTransaction::createUI()
  {
    tableStore.clear();
    container()->setOverflow(Wt::Overflow::Scroll);

    auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templateTransaction));
    result->addFunction("id", &Wt::WTemplate::Functions::id);

    lineEditTransaction = result->bindWidget("lineEditTransaction", std::make_unique<Wt::WLineEdit>());
    RUNTIME_ASSERT(lineEditTransaction != nullptr, "Control: lineEditTransaction not found");
    lineEditTransaction->setEnabled(false);
    lineEditTransaction->changed().connect([this]
    {
      switch(internalMode)
      {
        case BT_FIND:
        {
          processFind();
          break;
        }
        case BT_CREATE:
        {
          dirty(false);
          enableEdit(true);
          break;
        };
        default:
        {
          CODE_ERROR();
          break;
        }
      };
    });
    auto btn = result->bindWidget("actionButton", std::make_unique<Wt::WPushButton>("Action"));
    {
      auto popup = std::make_unique<Wt::WPopupMenu>();
      popup->addItem("Find");
      popup->addItem("Search");
      auto pp = popup.get();
      btn->setMenu(std::move(popup));
      btn->setStyleClass("btn-outline-primary");
      pp->itemSelected().connect([&](Wt::WMenuItem *item)
      {
        previousMode = internalMode;
        if (item->text() == "Find")
        {
          internalMode = BT_FIND;
        }
        else if (item->text() == "Search")
        {
          internalMode = BT_SEARCH;
        }
        else
        {
          CODE_ERROR();
        };
        checkSave();
      });
    }

    lineEditStatus = result->bindWidget("lineEditStatus", std::make_unique<Wt::WLineEdit>());
    RUNTIME_ASSERT(lineEditStatus != nullptr, "Control: lineEditStatus not found");
    lineEditStatus->setEnabled(false);
    btn = result->bindWidget("buttonStatus", std::make_unique<Wt::WPushButton>("Action"));
    createStatusButton(btn);

    comboBoxTransactionType = result->bindWidget("comboBoxTransactionType", std::make_unique<Wt::WComboBox>());
    RUNTIME_ASSERT(comboBoxTransactionType != nullptr, "Control: comboBoxTransaction Type not found");
    comboBoxTransactionType->setModel(modelTransactionType);
    comboBoxTransactionType->changed().connect([this]
    {
      dynamic_cast<views::CViewTransaction *>(record_.get())->transactionTypeID(modelTransactionType->
                                                                                index2ID(comboBoxTransactionType->currentIndex()));
      dirty();
    });

    comboBoxPortfolio = result->bindWidget("comboBoxPortfolio", std::make_unique<Wt::WComboBox>());
    RUNTIME_ASSERT(comboBoxPortfolio != nullptr, "Control: comboBoxPortfolio Type not found");
    comboBoxPortfolio->setModel(modelPortfolio);
    comboBoxPortfolio->changed().connect([this]
    {
        /* Once the portfolio is entered, the security comboBox and the CostElement combo boxes can be updated.
         */
      dynamic_cast<views::CViewTransaction *>(record_.get())->portfolioID(modelPortfolio->index2ID(comboBoxPortfolio->currentIndex()));
      dirty();
    });

    comboBoxExchange = result->bindWidget("comboBoxExchange", std::make_unique<Wt::WComboBox>());
    RUNTIME_ASSERT(comboBoxExchange != nullptr, "Control: comboBoxExchange Type not found");
    comboBoxExchange->setModel(modelExchanges);
    comboBoxExchange->changed().connect([this]
    {
      exchangeID_ = modelExchanges->index2ID(comboBoxExchange->currentIndex());
      modelSecurities->reload();
      dirty();
    });

    comboBoxSecurity = result->bindWidget("comboBoxSecurity", std::make_unique<Wt::WComboBox>());
    RUNTIME_ASSERT(comboBoxSecurity != nullptr, "Control: comboBoxSecurity Type not found");
    comboBoxSecurity->setModel(modelSecurities);
    comboBoxSecurity->changed().connect([this]
    {
      dynamic_cast<views::CViewTransaction *>(record_.get())->securityID(modelSecurities->index2ID(comboBoxSecurity->currentIndex()));
      dirty();
    });

    spinBoxQuantity = result->bindWidget("spinBoxQuantity", std::make_unique<Wt::WDoubleSpinBox>());
    RUNTIME_ASSERT(spinBoxQuantity != nullptr, "Control: spinBoxQuantity Type not found");
    spinBoxQuantity->changed().connect([this]
    {
      dynamic_cast<views::CViewTransaction *>(record_.get())->quantity(spinBoxQuantity->value());
      updateCosts();
      dirty();
    });

    spinBoxPrice = result->bindWidget("spinBoxPrice", std::make_unique<Wt::WDoubleSpinBox>());
    RUNTIME_ASSERT(spinBoxPrice != nullptr, "Control: spinBoxPrice Type not found");
    spinBoxPrice->changed().connect([this]
    {
      dynamic_cast<views::CViewTransaction *>(record_.get())->price(decimal_t{spinBoxPrice->value()});
      updateCosts();
      dirty();
    });

    lineEditCosts = result->bindWidget("lineEditCosts", std::make_unique<Wt::WLineEdit>());
    RUNTIME_ASSERT(lineEditCosts != nullptr, "Control: lineEditCosts Type not found");
    lineEditCosts->setEnabled(false);

    lineEditTotal = result->bindWidget("lineEditTotal", std::make_unique<Wt::WLineEdit>());
    RUNTIME_ASSERT(lineEditTotal != nullptr, "Control: lineEditTotal Type not found");
    lineEditTotal->setEnabled(false);

    dateEditPosting = result->bindWidget("dateEditPosting", std::make_unique<Wt::WDateEdit>());
    RUNTIME_ASSERT(dateEditPosting != nullptr, "Control: dateEditPosting Type not found");
    dateEditPosting->changed().connect([this]
    {
      Wt::WDate wtDate = dateEditPosting->date();
      std::chrono::year_month_day date(std::chrono::year(wtDate.year()),
                                       std::chrono::month(wtDate.month()),
                                       std::chrono::day(wtDate.day()));
      dynamic_cast<views::CViewTransaction *>(record_.get())->postingDate(GCL::date_t{static_cast<std::chrono::sys_days>(date)});
      dirty();
    });
    dateEditPosting->setDate(Wt::WDate());

    lineEditBasePrice = result->bindWidget("lineEditBasePrice", std::make_unique<Wt::WLineEdit>());
    RUNTIME_ASSERT(lineEditBasePrice != nullptr, "Control: lineEditBasePrice Type not found");
    lineEditBasePrice->setEnabled(false);

      // Table for capturing the information

    tableCostLine = container()->addNew<Wt::WTable>();
    tableCostLine->setWidth(Wt::WLength("100%"));
    tableCostLine->setHeaderCount(1);
    tableCostLine->addStyleClass("table");
    tableCostLine->addStyleClass("table-striped");

    int col = 0;

    pushButtonRowAdd = tableCostLine->elementAt(0, col++)->addNew<Wt::WPushButton>("Add Line");
    pushButtonRowAdd->clicked().connect([this]
    {
      createLine();
    });
    pushButtonRowAdd->setEnabled(false);

    tableCostLine->columnAt(0)->setWidth(100);
    tableCostLine->elementAt(0, col++)->addNew<Wt::WText>("Type");
    tableCostLine->elementAt(0, col++)->addNew<Wt::WText>("Value");

    createLine();

    enableEdit(false);

    DEBUGMESSAGE("Exiting Procedure: CPageIMMTransaction::createUI()");
  }

  /// @brief      Enable/Disable editing
  /// @param[in]  enable: true to enable editing.
  /// @throws
  /// @version    2023-07-25/GGB - Function created.

  void CPageIMMTransaction::enableEdit(bool enable)
  {
    comboBoxTransactionType->setEnabled(enable);
    comboBoxPortfolio->setEnabled(enable);
    comboBoxExchange->setEnabled(enable);
    comboBoxSecurity->setEnabled(enable);
    spinBoxQuantity->setEnabled(enable);
    spinBoxPrice->setEnabled(enable);
    dateEditPosting->setEnabled(enable);
    pushButtonRowAdd->setEnabled(enable);

    for (auto &tableRow: tableStore)
    {
      tableRow.pushButtonDelete->setEnabled(enable);
      tableRow.comboBoxType->setEnabled(enable);
      tableRow.spinBoxCost->setEnabled(enable);
    }
  }

  /// @brief Populates the fields.
  /// @throws
  /// @version 2022-07-28/GGB - Function created.

  void CPageIMMTransaction::populateFields()
  {
    //lineEditAccountName->setText(dirtyRecord.shortText);
    //comboBoxParentAccount->setCurrentIndex(modelAccountGroups->indexFromID(dirtyRecord.parentID));

//    modelAccountsInGroup->loadData();
//    comboBoxPlaceBefore->refresh();
//    comboBoxPlaceBefore->setCurrentIndex(modelAccountsInGroup->itemFromSortOrder(dirtyRecord.sortOrder) + 1);
  }

  /// @brief Function called when the check save/save process is complete.
  /// @throws
  /// @version 2022-08-01/GGB - Function created.

  void CPageIMMTransaction::saveComplete()
  {
      // Update all the models.

    if (internalMode != BT_CLOSEWINDOW)
    {
      //modelAccountGroups->loadData();
    }

    switch(internalMode)
    {
      case BT_UPDATE:
      {
        enableEdit(true);
        break;
      }
      case BT_CREATE:
      {
        clearFields();
        //dirtyRecord.ID = 0;
//        dirtyRecord.parentID = 0;
        //dirtyRecord.shortText = "";
//        dirtyRecord.accountFlags.value = 0;
        enableEdit(true);
        break;
      }
      case BT_RECORDCHANGE:
      {
//        dirtyRecord.ID = pendingAccountID_;
//        database::tbl_fi_accounts::readRecord(application(), dirtyRecord);
//        cleanRecord = dirtyRecord;
        populateFields();
        break;
      };
      default:
      {
        CPageIMMTransaction::saveComplete();
        break;
      }

    }
  }

  /// @brief Saves the changed data.
  /// @version 2022-08-01/GGB - Function created.

  void CPageIMMTransaction::processSaveData()
  {
    using namespace database;

//    if (dirtyRecord.ID == 0)
//    {
//        /* Simple case - only need to update the sortOrder for all the affected items in the group that the new account
//         * is being inserted into.
//         */

////      database::tbl_gl_costElement::updateSortOrder(application(), dirtyRecord.parentID,
////                                                dirtyRecord.sortOrder,        // From this record
////                                                0,                            // To end
////                                                dirtyRecord.sortOrder + 1);

//      tbl_fi_accounts::createRecord(application(), dirtyRecord);
//    }
//    else
//    {
//        /* Two cases and some sub-cases.
//         *  1. If the account is moved to a new account group.
//         *    a) Update all affected accounts in the old account group.
//         *    b) Update all affected accounts in the new account group.
//         *
//         *  2. If the account group if the same
//         *    a) Update all the affected accounts in the account group.
//         */

////      if (dirtyRecord.parentID != cleanRecord.parentID)
////      {
////          // Case 1. account moved to new account group.
////          // Old account group

////        database::tbl_gl_costElement::updateSortOrder(application(), cleanRecord.parentID,
////                                                  cleanRecord.sortOrder,  // From this record
////                                                  0,                      // To end
////                                                  cleanRecord.sortOrder); // New starting value

////          // New account group

////        database::tbl_gl_costElement::updateSortOrder(application(), dirtyRecord.parentID,
////                                                  dirtyRecord.sortOrder,  // From this record
////                                                  0,                      // To end
////                                                  dirtyRecord.sortOrder + 1); // New Start
////      }
////      else if (dirtyRecord.sortOrder != cleanRecord.sortOrder)
////      {
////          // Case 2. account moved within old account group.
////          // This devolves into two cases, one where the record is going to be moved earlier in the list,
////          // and one where the record is going to be moved later in the list.

////        if (dirtyRecord.sortOrder < cleanRecord.sortOrder)
////        {
////            // Record being moved earlier.
////            // Move all the records from >= dirty && < clean

////          database::tbl_gl_costElement::updateSortOrder(application(),
////                                                    dirtyRecord.parentID,
////                                                    dirtyRecord.sortOrder,      // From this record
////                                                    cleanRecord.sortOrder,      // To this record
////                                                    dirtyRecord.sortOrder+1);  // New Start

////        }
////        else
////        {
////            // Record being moved later.
////            // Move all the records from >= clean && < dirty + 1

////          database::tbl_gl_costElement::updateSortOrder(application(),
////                                                    dirtyRecord.parentID,
////                                                    cleanRecord.sortOrder,        // From this record
////                                                    dirtyRecord.sortOrder + 1,    // To this record (because of the gt not gte)
////                                                    cleanRecord.sortOrder);       // New Start
////        }
////      };

//      //tbl_fi_accounts::updateRecord(application(), dirtyRecord);
//    }

//    cleanRecord = dirtyRecord;
//    enableEdit(false);
//    containerChartOfAccounts->updateData();
  }

  /// @brief      Create a new cost line.
  /// @param[in]  dataExists: If true, don't create the view
  /// @throws
  /// @version    2023-07-27/GGB - Function created.

  void CPageIMMTransaction::createLine(bool dataExists)
  {
    tableRow_t tableRow;
    int row = tableStore.size() + 1;
    int column = 0;

      // Create the view

    if (!dataExists)
    {
      tableRow.transactionLine = dynamic_cast<views::CViewTransaction *>(record_.get())->createLine();
    };

    tableRow.pushButtonDelete = tableCostLine->elementAt(row, column)->addNew<extendedPushButton>("Delete", tableStore.size());
    tableRow.pushButtonDelete->buttonClicked().connect(this, &CPageIMMTransaction::deleteCostLine);

      // Cost Type

    tableRow.modelTypes = std::make_shared<models::CModelCostTypes>(application(), models::CModelCostTypes::MU_COMBO_NULL);
    tableRow.modelTypes->reload();
    tableRow.comboBoxType = tableCostLine->elementAt(row, ++column)->addNew<extendedComboBox>(tableStore.size());
    tableRow.comboBoxType->setModel(tableRow.modelTypes);
    tableRow.comboBoxType->changed().connect(this, &CPageIMMTransaction::comboBoxTypeChanged);

      // Cost

    tableRow.spinBoxCost = tableCostLine->elementAt(row, ++column)->addNew<extendedDoubleSpinBox>(tableStore.size());
    tableRow.spinBoxCost->changed().connect(this, &CPageIMMTransaction::spinBoxValueChanged);

    tableStore.push_back(tableRow);
  }

  /// @brief      Delete the specified cost line.
  /// @param[in]  rowID: The row to delete.
  /// @version    2023-07-27/GGB - Function created.

  void CPageIMMTransaction::deleteCostLine(std::size_t rowID)
  {
    std::size_t index;

      // Copy the information down in the vector.

    for (index = rowID + 1; index < tableStore.size(); index++)
    {
      tableStore[index].pushButtonDelete->setUID(index - 1);
      tableStore[index].comboBoxType->setUID(index -1);
      tableStore[index].spinBoxCost->setUID(index -1);
    }

      // Notify the view about the deletion.

    //dynamic_cast<views::CViewTransaction *>(record_.get())->deleteLine(tableStore[rowID].transactionLine->ID());

    tableCostLine->removeRow(rowID + 1);
    tableStore.erase(tableStore.begin() + rowID);
  }

  /// @brief      Function to respond to the change of the value in the comboBox.
  /// @param[in]  row: The table row that has changed.
  /// @throws
  /// @version    2023-08-08/GGB - Function created.

  void CPageIMMTransaction::comboBoxTypeChanged(std::size_t row)
  {
    index_t typeID = tableStore[row].modelTypes->index2ID(tableStore[row].comboBoxType->currentIndex());

    dynamic_cast<views::CViewTransaction *>(record_.get())->transactionLine(row).typeID(typeID);
  }

  /// @brief      Function to respond to changing values in the spin box.
  /// @param[in]  row: The row that has changed.
  /// @throws
  /// @version    2023-08-01/GGB - Function created.

  void CPageIMMTransaction::spinBoxValueChanged(std::size_t row)
  {
    dynamic_cast<views::CViewTransaction *>(record_.get())->transactionLine(row).value({tableStore[row].spinBoxCost->value()});
    updateCosts();
  }

  /// @brief      Updates all the cost edits.
  /// @throws
  /// @version    2023-08-03/GGB - Function created.

  void CPageIMMTransaction::updateCosts()
  {
    money_t total;
    money_t totalFees;
    money_t basePrice;
    double quantity = spinBoxQuantity->value();

    total = dynamic_cast<views::CViewTransaction *>(record_.get())->price() *
            dynamic_cast<views::CViewTransaction *>(record_.get())->quantity();

    totalFees = dynamic_cast<views::CViewTransaction *>(record_.get())->totalCost();

    total += totalFees;

    lineEditCosts->setText(totalFees.to_string());
    lineEditTotal->setText(total.to_string());
    if (quantity != 0)
    {
      basePrice = total / quantity;
      lineEditBasePrice->setText(basePrice.to_string());
    }
    else
    {
      lineEditBasePrice->setText("---");
    }

  }

} // namespace transactions
