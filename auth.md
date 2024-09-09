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