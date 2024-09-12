要讓使用者在點擊 `LinkButton` 後知道他們所在的頁面，通常可以透過以下幾個步驟來實現：

### 1. **改變 LinkButton 的外觀（CSS 樣式）**
   你可以使用 `CSS` 動態地改變目前所在頁面的按鈕樣式，讓使用者知道他們正在瀏覽的頁面。

### 2. **判斷當前頁面並設置樣式**
   在 `MasterPage` 的後台程式碼中，可以根據目前的頁面 URL 判斷使用者正在瀏覽的頁面，然後動態改變 `LinkButton` 的樣式或狀態。

以下是具體步驟：

### 步驟 1：在 `MasterPage` 中設置 LinkButton
假設你的 `MasterPage` 上有兩個 `LinkButton`，分別對應兩個不同的頁面。

```html
<asp:LinkButton ID="LinkButton1" runat="server" PostBackUrl="~/Page1.aspx" CssClass="nav-link">Page 1</asp:LinkButton>
<asp:LinkButton ID="LinkButton2" runat="server" PostBackUrl="~/Page2.aspx" CssClass="nav-link">Page 2</asp:LinkButton>
```

### 步驟 2：在 MasterPage 的後台程式碼進行判斷
在 `MasterPage` 的 `Page_Load` 事件中，可以根據目前的 URL 來判斷並動態改變按鈕的外觀。

```vb
Protected Sub Page_Load(ByVal sender As Object, ByVal e As EventArgs) Handles Me.Load
    ' 取得當前頁面的路徑
    Dim currentPage As String = System.IO.Path.GetFileName(Request.Path)
    
    ' 根據當前頁面設置相應的樣式
    Select Case currentPage
        Case "Page1.aspx"
            LinkButton1.CssClass = "nav-link active" ' 設置當前頁面 LinkButton 的樣式
        Case "Page2.aspx"
            LinkButton2.CssClass = "nav-link active"
    End Select
End Sub
```

在這段程式碼中，`System.IO.Path.GetFileName(Request.Path)` 會取得當前頁面的名稱，並根據頁面名稱來設置相應的 `LinkButton` 的 `CssClass`，如 `active` 樣式。

### 步驟 3：在 CSS 中定義樣式
你需要在你的 CSS 中定義不同的樣式，讓使用者知道他們在哪個頁面。比如你可以設置一個 `active` 類別來改變目前頁面的 `LinkButton` 樣式。

```css
.nav-link {
    color: black;
    text-decoration: none;
}

.nav-link.active {
    font-weight: bold;
    color: red;
}
```

這樣，當使用者在 `Page1.aspx` 時，`LinkButton1` 會加上 `active` 類別，並顯示成紅色和粗體。當使用者在 `Page2.aspx` 時，`LinkButton2` 則會顯示成紅色和粗體。

### 總結
1. 在 `MasterPage` 中設置 `LinkButton`，並指向不同頁面。
2. 在後台程式碼中，根據當前頁面的 URL 判斷使用者正在瀏覽哪個頁面，並改變對應的 `LinkButton` 的樣式。
3. 在 CSS 中設置樣式，讓使用者清楚地知道自己所在的頁面。

這樣，使用者在點擊按鈕後可以直觀地知道自己正在瀏覽的頁面。