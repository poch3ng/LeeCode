在ASP.NET Web Forms应用中，您可以使用多种方法在点击按钮后打开一个新窗口（通常是一个新的浏览器标签页或弹出窗口）。以下是几种实现这一功能的方法：

### 方法 1: 使用HTML按钮和JavaScript

您可以在ASPX页面上使用普通的HTML按钮，并通过JavaScript的`window.open`方法来打开一个新窗口。这种方法简单且直接，不涉及服务器端的回发。

```html
<button type="button" onclick="window.open('目标页面URL', '_blank');">打开新窗口</button>
```

这里，`目标页面URL`是您希望在新窗口中打开的页面的地址，`_blank`指定了链接应在新窗口或标签页中打开。

### 方法 2: 使用ASP.NET按钮和客户端脚本

如果您希望使用ASP.NET的`Button`控件，并在其`Click`事件处理器中处理一些服务器端逻辑，然后再打开新窗口，您可以通过`ScriptManager.RegisterStartupScript`方法来注册并执行JavaScript代码。

在您的ASP.NET页面的代码后台（.aspx.cs或.aspx.vb文件）中：

```vb
Protected Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
    ' 在这里处理服务器端逻辑
    ' ...

    ' 然后注册启动脚本来打开新窗口
    Dim script As String = "window.open('目标页面URL', '_blank');"
    ScriptManager.RegisterStartupScript(Me, Me.GetType(), "openNewWindow", script, True)
End Sub
```

### 方法 3: 使用ASP.NET超链接控件

如果您不需要在打开新窗口之前处理服务器端逻辑，您也可以简单地使用ASP.NET的`HyperLink`控件来实现，这样就无需JavaScript代码。

```html
<asp:HyperLink ID="HyperLink1" runat="server" NavigateUrl="目标页面URL" Target="_blank">打开新窗口</asp:HyperLink>
```

这里，`NavigateUrl`属性指定了要打开的页面URL，而`Target="_blank"`确保链接会在新窗口或标签页中打开。

### 注意

- 使用JavaScript `window.open`方法时，一些浏览器的弹出窗口拦截器可能会阻止新窗口的打开。确保在必要时通知用户允许弹出窗口。
- 在处理服务器端逻辑后打开新窗口的场景中，由于新窗口的打开是通过客户端脚本实现的，因此它仍可能受到浏览器弹出窗口拦截器的影响。

根据您的具体需求选择合适的方法。如果您只是简单地需要打开一个新窗口，而不需要先执行服务器端逻辑，使用HTML按钮或`HyperLink`控件可能是最简单的方法。如果您需要先执行服务器端逻辑，然后再打开新窗口，那么使用ASP.NET按钮和`ScriptManager.RegisterStartupScript`方法将是一个好选择。