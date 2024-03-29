如果在显示模态窗口（Modal）时，按下 Enter 键后焦点（focus）不在模态窗口上，可能是因为页面的其他元素（如按钮或输入框）捕获了焦点。为了确保在打开模态窗口时焦点始终位于模态窗口的一个元素上，你可以使用 JavaScript 或 jQuery 设置焦点到模态窗口的特定控件上，比如模态窗口的一个输入框。

下面是如何在使用 ASP.NET AJAX Control Toolkit 的 `ModalPopupExtender` 打开模态窗口时，使用 JavaScript 设置焦点的示例：

### 步骤 1: 定义模态窗口显示后要聚焦的控件

假设你想在模态窗口中的 `txtCustomerCode` 输入框获得焦点，首先确保该输入框（或你想要聚焦的任何控件）有一个 `ClientIDMode="Static"` 的属性（如果你希望使用控件的 ID 在客户端代码中引用它）。如果不设置 `ClientIDMode`，ASP.NET 会为控件ID生成基于容器命名的较长ID，这可能使得通过ID引用它变得复杂。

```aspx
<asp:TextBox ID="txtCustomerCode" runat="server" ClientIDMode="Static"></asp:TextBox>
```

### 步骤 2: 添加 JavaScript 代码设置焦点

在 `ModalPopupExtender` 的 `OnShown` 属性中添加 JavaScript 函数名称，该函数在模态窗口完全显示后执行。

```aspx
<ajaxToolkit:ModalPopupExtender ID="ModalPopupExtender1" runat="server"
    TargetControlID="btnShowModal"
    PopupControlID="Panel1"
    BackgroundCssClass="modalBackground"
    OnShown="onModalShown">
</ajaxToolkit:ModalPopupExtender>
```

然后，在页面中添加这个 `onModalShown` 函数，并使用 JavaScript 或 jQuery 设置焦点。这里是使用纯 JavaScript 设置焦点的例子：

```html
<script type="text/javascript">
    function onModalShown() {
        document.getElementById('txtCustomerCode').focus();
    }
</script>
```

如果你倾向于使用 jQuery（确保你的项目已经包含了 jQuery），则可以这样写：

```html
<script type="text/javascript">
    function onModalShown() {
        $('#txtCustomerCode').focus();
    }
</script>
```

### 注意

- 确保你的 `ModalPopupExtender` 控件的 `OnShown` 属性正确引用了 JavaScript 函数。
- 使用 `ClientIDMode="Static"` 使客户端代码更容易引用服务器端控件的 ID。如果不使用 `ClientIDMode="Static"`，则需要通过 `ClientID` 属性动态获取控件的客户端 ID。
- 上述方法确保了当模态窗口显示时，特定的输入框或控件获得焦点，从而改善了用户体验并减少了不必要的键盘或鼠标操作。