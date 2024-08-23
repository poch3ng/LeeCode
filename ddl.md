如果你使用 `DataBind` 来绑定 `DropDownList (DDL)`，并且想要在数据绑定后手动添加一个默认选项，你可以按照以下步骤操作：

1. 数据绑定后，插入默认选项。
2. 设置默认选项的值为 `%`。

以下是一个示例代码：

```asp
<asp:DropDownList ID="yourDDLName" runat="server" AutoPostBack="True">
</asp:DropDownList>

<script runat="server">
    Protected Sub Page_Load(ByVal sender As Object, ByVal e As EventArgs) Handles Me.Load
        If Not IsPostBack Then
            BindData()
            ' 数据绑定后添加默认选项
            yourDDLName.Items.Insert(0, New ListItem("---select---", "%"))
        End If
    End Sub

    Private Sub BindData()
        ' 示例数据绑定
        yourDDLName.DataSource = GetDataSource()
        yourDDLName.DataTextField = "TextField"
        yourDDLName.DataValueField = "ValueField"
        yourDDLName.DataBind()
    End Sub

    Private Function GetDataSource() As DataTable
        ' 返回一个示例数据源
        Dim dt As New DataTable()
        dt.Columns.Add("TextField")
        dt.Columns.Add("ValueField")
        
        dt.Rows.Add("選項1", "1")
        dt.Rows.Add("選項2", "2")
        
        Return dt
    End Function
</script>
```

### 关键点说明：
- `DataBind()` 用于将数据绑定到下拉列表中。
- `Items.Insert(0, New ListItem("---select---", "%"))` 用于在数据绑定后将 `---select---` 作为第一个选项插入到下拉列表中，并将其值设为 `%`。

这样，`DropDownList` 的第一个选项将始终是 `---select---`，且值为 `%`。