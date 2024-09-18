黑色點點通常是因為 `TreeView` 使用的是無序列表 (`<ul>`) 和列表項 (`<li>`) 來顯示節點，而這些點點是無序列表的預設樣式。你可以通過修改 CSS 來隱藏這些點點。

### 1. 修改 CSS 移除列表的黑點

要移除黑點，你可以使用 `list-style-type: none;` 這個 CSS 屬性。這樣可以禁用無序列表項的預設樣式。具體步驟如下：

#### 例子：
```css
/* TreeView 整體樣式 */
.TreeViewStyle {
    list-style-type: none; /* 移除黑點 */
    padding: 0;
    margin: 0;
}

/* 移除子項目（節點）的黑點 */
.TreeViewStyle ul {
    list-style-type: none; /* 移除子項目的黑點 */
    padding-left: 20px; /* 可選，設定縮排 */
}

.TreeViewStyle li {
    list-style-type: none; /* 移除黑點 */
}
```

### 2. 在 TreeView 上應用這些樣式

確保你的 `TreeView` 控制項有應用正確的 `CssClass`，範例：

```html
<asp:TreeView ID="TreeView1" runat="server" DataSourceID="SiteMapDataSource1" CssClass="TreeViewStyle">
</asp:TreeView>
```

### 3. 測試樣式

儲存並重新整理你的頁面。黑色點點應該會從目錄項目中消失。

### 其他調整 (可選)

如果你想同時調整節點的間距或縮排，也可以在相應的 CSS 中修改 `padding` 或 `margin` 屬性。例如，調整子節點的縮排：

```css
.TreeViewStyle ul {
    padding-left: 20px; /* 設置縮排 */
}
```

這樣，你就可以去除每個項目前面的黑色點點，並根據需求調整目錄的縮排或樣式。