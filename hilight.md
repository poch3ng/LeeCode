若要使用VBA將一個名為 `highlight` 的文字方塊移到最上層，可以使用以下VBA程式碼來實現：

### VBA 程式碼範例

```vba
Sub BringHighlightToFront()
    Dim shp As Shape
    Dim slide As slide

    ' 確認當前投影片
    Set slide = ActiveWindow.View.Slide
    If slide Is Nothing Then
        MsgBox "請確保你選擇了一個投影片"
        Exit Sub
    End If

    ' 嘗試找到名為 'highlight' 的文字方塊
    On Error Resume Next
    Set shp = slide.Shapes("highlight")
    On Error GoTo 0

    ' 檢查是否找到該物件
    If shp Is Nothing Then
        MsgBox "未找到名為 'highlight' 的物件"
    Else
        ' 將該物件移到最上層
        shp.ZOrder msoBringToFront
        MsgBox "'highlight' 物件已移至最上層"
    End If
End Sub
```

### 程式碼說明：
1. **`slide.Shapes("highlight")`**：尋找當前投影片中名為 `highlight` 的物件（文字方塊）。
2. **`shp.ZOrder msoBringToFront`**：將該物件移到最上層。
3. **錯誤處理**：使用 `On Error Resume Next` 避免在找不到物件時出現錯誤，並在找不到物件時顯示錯誤訊息。

### 操作步驟：
1. **開啟PowerPoint** 並確認存在名為 `highlight` 的文字方塊。
2. **開啟VBA編輯器**：
   - 按 `Alt + F11` 開啟VBA編輯器。
   - 在「專案」窗口中，找到對應的PowerPoint檔案，右鍵 `ThisPresentation` → `插入` → `模組`。
3. **貼上上述程式碼** 到新插入的模組中。
4. **執行宏**：
   - 按 `Alt + F8`，選擇 `BringHighlightToFront` 並執行。
5. **觀察結果**：名為 `highlight` 的文字方塊將被移到最上層。

### 使用UiPath執行VBA：
你可以將上述VBA程式碼儲存在PowerPoint中，然後使用UiPath的 `Invoke VBA` 活動來執行這段程式碼。這樣可以在自動化流程中完成將 `highlight` 文字方塊移至最上層的操作。