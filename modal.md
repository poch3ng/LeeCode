如果您沒有使用Bootstrap且正在ASP.NET Web Forms环境中工作，可以使用ASP.NET的内建控件和JavaScript来创建一个类似的功能，以弹出一个窗口让用户输入信息。这里有一个使用`Panel`控件作为模态窗口的示例，并通过`ModalPopupExtender`控件从ASP.NET AJAX Control Toolkit来触发这个窗口。

首先，确保您已经将ASP.NET AJAX Control Toolkit添加到您的项目中。如果尚未添加，您可以通过NuGet包管理器搜索并安装。

### 步骤1: 添加ModalPopupExtender和Panel控件

在ASPX页面中，添加一个`Panel`作为模态窗口，使用`ModalPopupExtender`来控制其显示。

```aspx
<%@ Register Assembly="AjaxControlToolkit" Namespace="AjaxControlToolkit" TagPrefix="ajaxToolkit" %>

<asp:Button ID="btnShowModal" runat="server" Text="新增" />
<ajaxToolkit:ModalPopupExtender ID="ModalPopupExtender1" runat="server"
    TargetControlID="btnShowModal"
    PopupControlID="Panel1"
    BackgroundCssClass="modalBackground">
</ajaxToolkit:ModalPopupExtender>

<asp:Panel ID="Panel1" runat="server" CssClass="modalPopup" style="display:none">
    <p>公司：<asp:DropDownList ID="ddlCompany" runat="server"></asp:DropDownList></p>
    <p>客戶代號：<asp:TextBox ID="txtCustomerCode" runat="server"></asp:TextBox></p>
    <asp:Button ID="btnAdd" runat="server" Text="新增" OnClick="btnAdd_Click" />
    <asp:Button ID="btnCancel" runat="server" Text="取消" />
</asp:Panel>
```

### 步骤2: 添加CSS样式

在您的ASPX页面或外部CSS文件中，添加CSS样式以美化模态窗口。

```css
<style>
    .modalBackground {
        background-color: Gray;
        filter: alpha(opacity=70);
        opacity: 0.7;
    }
    .modalPopup {
        background-color: White;
        border-width: 3px;
        border-style: solid;
        border-color: Gray;
        padding: 10px;
        width: 300px;
    }
</style>
```

### 步骤3: 后端处理新增操作

在您的后端代码中（.aspx.cs或.aspx.vb文件），添加点击新增按钮`btnAdd`的事件处理逻辑。

```vb
Protected Sub btnAdd_Click(sender As Object, e As EventArgs)
    ' 检查数据库中是否已经存在输入的客户代号
    ' 假设已经有方法CheckCustomerExists和InsertCustomer
    Dim company As String = ddlCompany.SelectedItem.Text
    Dim customerCode As String = txtCustomerCode.Text

    If Not CheckCustomerExists(customerCode) Then
        InsertCustomer(company, customerCode)
        ' 可能需要刷新页面或执行其他逻辑
    Else
        ' 显示错误信息
    End If
End Sub
```

### 步骤4: 设置取消按钮逻辑

取消按钮可以通过JavaScript来关闭模态窗口。将以下JavaScript代码添加到页面中。

```javascript
<script type="text/javascript">
    function hideModal() {
        var modal = document.getElementById('<%= Panel1.ClientID %>');
        modal.style.display = 'none';
    }
</script>
```

然后，修改`btnCancel`按钮的属性，让其点击时执行JavaScript函数。

```aspx
<asp:Button ID="btnCancel" runat="server" Text="取消" OnClientClick="hideModal(); return false;" />
```

这个示例展示了如何在ASP.NET Web Forms应用中使用`Panel`和`ModalPopupExtender`来创建一个简单的模态输入窗口。您需要根据实际项目需求调整数据库检查和数据插入的逻辑。