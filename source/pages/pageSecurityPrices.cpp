//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           GUI: Investment Management
// FILE:                pageSecurityPrices.cpp
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
// HISTORY:             2023-07-27/GGB - File Created
//
//**********************************************************************************************************************************

#include "include/pages/pageSecurityPrices.h"

  // Standard C++ library header files

#include <algorithm>
#include <map>
#include <utility>

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include<Wt/WProgressBar.h>
#include <Wt/WTable.h>
#include <Wt/WTemplate.h>

  // msmERP  header files

#include "include/application.h"
#include "include/pages/GUI_Templates.h"
#include "include/priceUploadManager.h"
#include "include/database/tables/tbl_imm_securityPrices.h"

namespace transactionPages
{

  /// @brief      Constructor for the class.
  /// @param[in]  parent: The parent object.
  /// @version    2023-07-27/GGB - Function created.

  CPageSecurityPrices::CPageSecurityPrices(CApplication &parent, std::unique_ptr<parameters_t> p)
    : CPageTransaction(parent, std::move(p))
  {
  }

  /// @brief      Creates the UI for the operating unit view transaction.
  /// @throws
  /// @version    2022-05-25/GGB - Function created.

  void CPageSecurityPrices::createUI()
  {
    auto result = container()->addWidget(std::make_unique<Wt::WTemplate>(templatePrices));
    result->addFunction("id", &Wt::WTemplate::Functions::id);

    fileDropWidget = bindWidget<Wt::WFileDropWidget>(result, "fileUpload");

    fileDropWidget->drop().connect([this] (const std::vector<Wt::WFileDropWidget::File *>& files)
    {
      const int maxFiles = 32;
      unsigned prevNbFiles = fileDropWidget->uploads().size() - files.size();
      for (unsigned i = 0; i < files.size(); i++)
      {
        if (prevNbFiles + i >= maxFiles)
        {
          fileDropWidget->cancelUpload(files[i]);
          continue;
        }

        Wt::WContainerWidget *block = fileDropWidget->addNew<Wt::WContainerWidget>();
        block->setToolTip(files[i]->clientFileName());
        block->addStyleClass("upload-block spinner");
      }

      if (fileDropWidget->uploads().size() >= maxFiles)
      {
        fileDropWidget->setAcceptDrops(false);
      };
    });

    fileDropWidget->uploaded().connect([this] (Wt::WFileDropWidget::File *file)
    {
      std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
      {
        if (uploads[idx] == file)
        {
          break;
        };
      };
      fileDropWidget->widget(idx)->removeStyleClass("spinner");

      if (IMM::priceUpload::CPriceUploadManager::validateFile(file->uploadedFile().clientFileName(),
                                                              file->uploadedFile().spoolFileName()).size() != 0)
      {
        fileDropWidget->widget(idx)->addStyleClass("ready");
        createLine(file);
      }
      else
      {
        fileDropWidget->widget(idx)->addStyleClass("failed");
      }
    });

    fileDropWidget->tooLarge().connect([this] (Wt::WFileDropWidget::File *file, uint64_t size)
    {
      std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
      {
        if (uploads[idx] == file)
        {
          break;
        };
      };
      fileDropWidget->widget(idx)->removeStyleClass("spinner");
      fileDropWidget->widget(idx)->addStyleClass("failed");
    });

    fileDropWidget->uploadFailed().connect([this] (Wt::WFileDropWidget::File *file)
    {
      std::vector<Wt::WFileDropWidget::File*> uploads = fileDropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
      {
        if (uploads[idx] == file)
        {
          break;
        };
      };
      fileDropWidget->widget(idx)->removeStyleClass("spinner");
      fileDropWidget->widget(idx)->addStyleClass("failed");
    });

      // Table for capturing the information

    tableLines = container()->addNew<Wt::WTable>();
    tableLines->setWidth(Wt::WLength("100%"));
    tableLines->setHeaderCount(1);
    tableLines->addStyleClass("table");
    tableLines->addStyleClass("table-striped");

    int col = 1;    // Needed as the first column heading in blank.

    tableLines->columnAt(0)->setWidth(100);
    tableLines->elementAt(0, col++)->addNew<Wt::WText>("Filename");
    tableLines->elementAt(0, col++)->addNew<Wt::WText>("File Type");
    tableLines->elementAt(0, col++)->addNew<Wt::WText>("Exchange");
    tableLines->elementAt(0, col++)->addNew<Wt::WText>("Security");
    tableLines->elementAt(0, col++)->addNew<Wt::WText>("Upload");
  }

  /// @brief      Creates a new line for the table.
  /// @param[in]  file: The file details to add.
  /// @version    2023-09-22/GGB - Function created.

  void CPageSecurityPrices::createLine(Wt::WFileDropWidget::File *file)
  {
    tableRow_t tableRow;
    int row = tableStore.size() + 1;
    int column = 0;

    tableRow.file = file;
    tableRow.pushButtonDelete = tableLines->elementAt(row, column++)->addNew<extendedPushButton>("Delete", tableStore.size());
    tableRow.pushButtonDelete->buttonClicked().connect(this, &CPageSecurityPrices::deleteLine);

    tableRow.modelExchanges = std::make_shared<models::CModelExchanges>(application(), models::CModelExchanges::MU_COMBO_NULL);
    tableRow.modelExchanges->reload();

    tableRow.modelSecurities= std::make_shared<models::CModelSecurities>(application(), models::CModelSecurities::MU_COMBO_NULL,
                                                                         tableRow.exchangeID_);
    tableRow.modelSecurities->reload();

    tableRow.lineEditFilename = tableLines->elementAt(row, column++)->addNew<Wt::WLineEdit>(file->clientFileName());
    tableRow.lineEditFilename->setEnabled(false);
    tableRow.lineEditFileType = tableLines->elementAt(row, column++)->
                                addNew<Wt::WLineEdit>(IMM::priceUpload::CPriceUploadManager::validateFile(
                                                        file->uploadedFile().clientFileName(),
                                                        file->uploadedFile().spoolFileName()));
    tableRow.lineEditFileType->setEnabled(false);
    tableRow.comboBoxExchange = tableLines->elementAt(row, column++)->addNew<extendedComboBox>(tableStore.size());
    tableRow.comboBoxExchange->setModel(tableRow.modelExchanges);
    tableRow.comboBoxSecurity = tableLines->elementAt(row, column++)->addNew<extendedComboBox>(tableStore.size());
    tableRow.comboBoxSecurity->setModel(tableRow.modelSecurities);
    tableRow.pushButtonUpload = tableLines->elementAt(row, column++)->addNew<extendedPushButton>("Upload", tableStore.size());
    tableRow.pushButtonUpload->buttonClicked().connect(this, &CPageSecurityPrices::pushButtonUploadClicked);

    tableRow.comboBoxExchange->
        setCurrentIndex(tableRow.modelExchanges->
                        suffix22Index(IMM::priceUpload::CPriceUploadManager::exchange(file->uploadedFile().clientFileName(),
                                                                                      file->uploadedFile().spoolFileName())));
    tableRow.exchangeID_ = tableRow.modelExchanges->index2ID(tableRow.comboBoxExchange->currentIndex());
    tableRow.modelSecurities->reload();
    tableRow.comboBoxSecurity->
        setCurrentIndex(tableRow.modelSecurities->
                        symbol2Index(IMM::priceUpload::CPriceUploadManager::security(file->uploadedFile().clientFileName(),
                                                                                     file->uploadedFile().spoolFileName())));


    enableUploadButton(row);
    tableStore.push_back(tableRow);
  }

  /// @brief      Deletes the specified line.
  /// @param[in]  rowIndx: The line to delete.
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  void CPageSecurityPrices::deleteLine(std::size_t rowIndx)
  {
    std::size_t index;

      // Copy the information down in the vector.

    for (index = rowIndx + 1; index < tableStore.size(); index++)
    {
      tableStore[index].pushButtonDelete->setUID(index - 1);
      tableStore[index].comboBoxExchange->setUID(index -1);
      tableStore[index].comboBoxSecurity->setUID(index -1);
      tableStore[index].pushButtonUpload->setUID(index - 1);
    }

    tableLines->removeRow(rowIndx + 1);
    tableStore.erase(tableStore.begin() + rowIndx);
  }

  /// @brief      Enables the relevant upload button if allowed.
  /// @param[in]  rowIndx:
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  void CPageSecurityPrices::enableUploadButton(std::size_t rowIndx)
  {
//    if ((tableStore[rowIndx].comboBoxExchange->currentIndex() != 0) &&
//        (tableStore[rowIndx].comboBoxSecurity->currentIndex() != 0))
//    {
//      tableStore[rowIndx].pushButtonUpload->setEnabled(true);
//    }
//    else
//    {
//      tableStore[rowIndx].pushButtonUpload->setEnabled(false);
//    }
  }

  void CPageSecurityPrices::pushButtonUploadClicked(std::size_t rowIndx)
  {
    using namespace IMM::priceUpload;
    using namespace database::tbl_imm_securityPrices;

    pricesVector_t pricesVector;

    std::cout << "Parse File..." << std::endl;
    CPriceUploadManager::parseFile(tableStore[rowIndx].file->uploadedFile().clientFileName(),
                                   tableStore[rowIndx].file->uploadedFile().spoolFileName(),
                                   pricesVector);

    std::cout << "Upload Records..." << std::endl;
    createRecords(application(),
                  tableStore[rowIndx].modelSecurities->index2ID(tableStore[rowIndx].comboBoxSecurity->currentIndex()),
                  pricesVector);
  }

} // namespace transactions
