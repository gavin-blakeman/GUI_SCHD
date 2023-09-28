#ifndef GUI_TEMPLATES_H
#define GUI_TEMPLATES_H

constexpr char templateExchanges[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Exchange</span>
          <div>${lineEditShortText}</div>
          ${buttonAction}
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Status</span>
          <div>${lineEditStatus}</div>
          <div>${buttonStatus}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          <span class="input-group-text">Exchange Details</span>
          <div>${lineEditLongText}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Country</span>
          <div>${comboBoxCountry}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Security Suffix</span>
          <div>${lineEditSuffix}</div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templateSecurities[] =
R"for_c++_include(
  <div class="row">
    <div class="col-sm-4">
      ${widgetSecurities}
    </div>
    <div class="col-sm-8">
      <div class="row">
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Security</span>
            ${lineEditShortText}
          </div>
        </div>
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Status</span>
            <div>${lineEditStatus}</div>
            <div>${buttonStatus}</div>
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Exchange</span>
            ${comboBoxExchange}
          </div>
        </div>
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Symbol</span>
            ${lineEditCode}
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Currency</span>
            ${comboBoxCurrency}
          </div>
        </div>
        <div class="col-sm-6">
          <div class="input-group mb-3">
            <span class="input-group-text">Type</span>
            ${comboBoxSecurityType}
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-sm-12">
          <div class="input-group mb-3">
            <span class="input-group-text">Details</span>
            ${lineEditLongText}
          </div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templateWidgetSecurities[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          <span class="input-group-text">Business Unit</span>
          ${comboBoxExchange}
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          ${tableViewSecurity}
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templatePortfolio[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Exchange</span>
          <div>${lineEditShortText}</div>
          ${buttonAction}
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Status</span>
          <div>${lineEditStatus}</div>
          <div>${buttonStatus}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          <span class="input-group-text">Exchange Details</span>
          <div>${lineEditLongText}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Country</span>
          <div>${comboBoxCountry}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Security Suffix</span>
          <div>${lineEditSuffix}</div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templateTransaction[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Transaction</span>
          <div>${lineEditTransaction}</div>
          <div>${actionButton}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Status</span>
          <div>${lineEditStatus}</div>
          <div>${buttonStatus}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Transaction Type</span>
          <div class="col">${comboBoxTransactionType}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Portfolio</span>
          <div class="col">${comboBoxPortfolio}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Exchange</span>
          <div class="col">${comboBoxExchange}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Security</span>
          <div class="col">${comboBoxSecurity}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-3">
        <div class="input-group mb-3">
          <span class="input-group-text">Quantity</span>
          <div class="col">${spinBoxQuantity}</div>
        </div>
      </div>
      <div class="col-sm-3">
        <div class="input-group mb-3">
          <span class="input-group-text">Price</span>
          <div class="col">${spinBoxPrice}</div>
        </div>
      </div>
      <div class="col-sm-3">
        <div class="input-group mb-3">
          <span class="input-group-text">Costs</span>
          <div class="col">${lineEditCosts}</div>
        </div>
      </div>
      <div class="col-sm-3">
        <div class="input-group mb-3">
          <span class="input-group-text">Total</span>
          <div class="col">${lineEditTotal}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Posting Date</span>
          <div class="col">${dateEditPosting}</div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Base Price</span>
          <div class="col">${lineEditBasePrice}</div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templatePrices[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          <div>${fileUpload}</div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";

constexpr char templateCostTypes[] =
R"for_c++_include(
  <div class="container">
    <div class="row">
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Cost Type</span>
          <div>${lineEditShortText}</div>
          ${buttonAction}
        </div>
      </div>
      <div class="col-sm-6">
        <div class="input-group mb-3">
          <span class="input-group-text">Status</span>
          <div>${lineEditStatus}</div>
          <div>${buttonStatus}</div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-sm-12">
        <div class="input-group mb-3">
          <span class="input-group-text">Cost Element</span>
          <div>${comboBoxCostElement}</div>
        </div>
      </div>
    </div>
  </div>
)for_c++_include";


#endif // GUI_TEMPLATES_H
