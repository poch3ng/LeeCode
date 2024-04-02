如果你是使用`CommandField`来生成编辑按钮，并希望根据用户的角色或权限决定谁可以编辑`GridView`中的数据，你可以在`GridView`的`RowDataBound`事件中根据用户的角色或权限来动态显示或隐藏编辑按钮。`CommandField`生成的编辑按钮不像`TemplateField`中的按钮那样可以直接在标记中控制可见性，但你可以通过代码来控制。

### 步骤1: 设置`GridView`的`OnRowDataBound`事件

首先，确保你的`GridView`标记中已设置了`OnRowDataBound`事件的处理程序：

```asp
<asp:GridView ID="GridView1" runat="server" AutoGenerateEditButton="True" OnRowDataBound="GridView1_RowDataBound">
    ...
</asp:GridView>
```

### 步骤2: 在`RowDataBound`事件处理程序中控制编辑按钮的可见性

接下来，你需要在`RowDataBound`事件处理程序中找到编辑按钮，并根据用户的角色或权限来设置它的`Visible`属性。由于`CommandField`生成的编辑按钮会被渲染为`LinkButton`，你可以通过检查其`CommandName`属性来识别编辑按钮，它的值通常为"Edit"。

```vb
Protected Sub GridView1_RowDataBound(sender As Object, e As GridViewRowEventArgs) Handles GridView1.RowDataBound
    If e.Row.RowType = DataControlRowType.DataRow Then
        ' 尝试找到编辑按钮
        Dim editButton As LinkButton = e.Row.Controls.OfType(Of LinkButton)().FirstOrDefault(Function(button) button.CommandName = "Edit")
        If editButton IsNot Nothing Then
            ' 根据用户权限设置编辑按钮的可见性
            editButton.Visible = HttpContext.Current.User.IsInRole("特定角色或权限")
        End If
    End If
End Sub
```

### 注意

- 上述代码示例假设每行只有一个编辑按钮。如果你的`GridView`中包含多个`CommandField`或其他可能产生具有"Edit"命令名的控件，你可能需要更精确地定位编辑按钮。
- `HttpContext.Current.User.IsInRole("特定角色或权限")`是检查用户是否属于特定角色的示例代码。你需要根据实际使用的身份验证和角色管理系统来调整这部分逻辑。
- 这种方法只控制了编辑按钮的显示，不会阻止未授权的用户通过其他方式（如直接构造请求）尝试编辑操作。因此，你还应该在执行实际的编辑操作前（如在`RowUpdating`事件处理程序中）再次检查用户的权限，以确保应用的安全性。

通过上述方法，你可以根据用户的角色或权限动态地控制`GridView`中编辑按钮的显示，进而控制特定人士的编辑权限。