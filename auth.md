要在 ASP.NET WebForms 應用中使得 MasterPage 上的兩個 `LinkButton` 控件僅在用戶登入後顯示，您可以利用程式碼後端來動態控制這些控件的 `Visible` 屬性。這裡提供一個基本的步驟來實現這個需求：

### 步驟 1: 設定控件

在您的 MasterPage 中，確保兩個 `LinkButton` 控件有適當的 ID，以便您可以在程式碼中輕鬆引用它們。例如：

```html
<asp:LinkButton ID="LinkButton1" runat="server" Text="Link 1" />
<asp:LinkButton ID="LinkButton2" runat="server" Text="Link 2" />
```

### 步驟 2: 控制顯示邏輯

在 MasterPage 的程式碼後端（例如在 `Page_Load` 事件處理程序中），添加檢查用戶是否已經登入的邏輯。如果用戶已經登入，則設定 `LinkButton` 控件為可見；如果用戶未登入，則設為不可見。

```csharp
protected void Page_Load(object sender, EventArgs e)
{
    if (!IsPostBack)
    {
        // 檢查用戶是否已經登入
        if (Session["UserLoggedIn"] != null && (bool)Session["UserLoggedIn"] == true)
        {
            LinkButton1.Visible = true;
            LinkButton2.Visible = true;
        }
        else
        {
            LinkButton1.Visible = false;
            LinkButton2.Visible = false;
        }
    }
}
```

這裡，`Session["UserLoggedIn"]` 是一個假設存在的 Session 變量，您應根據您的登入邏輯實際情況來設置和檢查它。這只是一個例子，您可以根據需要調整條件。

### 步驟 3: 確保登入邏輯與 Session 狀態同步

在用戶成功登入後，確保在您的登入邏輯中設置相應的 Session 狀態：

```csharp
// 假設這是登入成功後的處理
Session["UserLoggedIn"] = true;
```

在用戶登出時，清除或設置相應的 Session 狀態：

```csharp
// 登出處理
Session["UserLoggedIn"] = false;
```

### 步驟 4: 測試

- 測試未登入狀態下，這些 `LinkButton` 是否隱藏。
- 測試登入後，這些 `LinkButton` 是否顯示。

通過這些步驟，您可以有效地控制只有在用戶登入後，這些 `LinkButton` 控件才顯示在 MasterPage 上，增強了應用的用戶體驗和安全性。

要設定特定的 ASP.NET WebForms 頁面（如 `abc.aspx` 和 `123.aspx`）只有在用戶驗證過後才能瀏覽，您可以在 `web.config` 文件中使用授權規則來達成這一點。以下是配置步驟：

### 步驟 1: 更新 Web.config 文件

1. **設定 forms 驗證**:
   確保您已經設定了 forms 驗證模式並指定了登入 URL。

   ```xml
   <authentication mode="Forms">
       <forms loginUrl="Login.aspx" timeout="2880" />
   </authentication>
   ```

2. **配置授權規則**:
   在 `<system.web>` 節點下設定授權規則，指定哪些用戶或角色可以訪問 `abc.aspx` 和 `123.aspx`。

   ```xml
   <authorization>
       <deny users="?" />  <!-- Deny anonymous users -->
   </authorization>
   ```

   然後，為整個應用程式或特定文件夾設置具體的訪問規則。例如，如果 `abc.aspx` 和 `123.aspx` 在同一個文件夾中，您可以為該文件夾添加一個 `web.config` 文件並設定如下規則：

   ```xml
   <configuration>
       <system.web>
           <authorization>
               <allow users="*" />  <!-- Allow all authenticated users -->
               <deny users="?" />   <!-- Deny all anonymous users -->
           </authorization>
       </system.web>
   </configuration>
   ```

### 步驟 2: 確保用戶登入

- 確保您的應用程式有一個有效的用戶登入系統。
- 登入頁面（如 `Login.aspx`）應處理用戶的認證並設置適當的身份驗證 Cookie。

### 步驟 3: 測試

- 測試未登入的用戶訪問 `abc.aspx` 和 `123.aspx` 應被重定向到登入頁面。
- 登入後，用戶應能正常訪問這些頁面。

通過這種設定，任何未經驗證的用戶試圖訪問這些頁面時都會被重定向到登入頁面，確保了這些資源的安全性和私密性。這樣您就可以確保只有驗證過的用戶才能訪問 `abc.aspx` 和 `123.aspx`。