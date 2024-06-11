在 SSRS 中，你可以使用自定義代碼來創建一個函數，這樣可以讓你的報表更加模塊化和重用代碼。下面是如何創建一個函數來根據 `CLSValue` 返回工時上限的步驟：

### 步驟 1: 打開報表並添加自定義代碼

1. **打開你的報表**: 在報表設計器中打開你要修改的報表。
2. **導航到報表屬性**: 通常在報表設計視圖的菜單中可以找到“報表屬性”選項。
3. **添加自定義代碼**:
   - 在報表屬性窗口中找到“代碼”選項卡。
   - 在代碼區域，輸入以下 VB 函數代碼：

   ```vb
   Public Function GetWorkHoursLimit(ByVal clsValue As String) As String
       Select Case clsValue
           Case "GX", "GJ"
               Return "8 小時"
           Case "EG", "EH", "EI", "EJ"
               Return "10 小時"
           Case "FB"
               Return "休假"
           Case Else
               Return "未定義"
       End Select
   End Function
   ```

### 步驟 2: 使用自定義函數在報表中設定工時上限

1. **找到需要設定工時上限的欄位**: 在報表設計視圖中，選擇需要根據 `CLSValue` 設定工時的欄位。
2. **設定表達式來調用函數**:
   - 點擊欄位，然後選擇“表達式”來編輯。
   - 輸入以下表達式來調用你創建的函數：
     ```plaintext
     =Code.GetWorkHoursLimit(Fields!CLSValue.Value)
     ```
   - 這個表達式會將 `CLSValue` 的值作為參數傳遞給 `GetWorkHoursLimit` 函數，並將返回的字符串顯示在報表的相應欄位中。

### 步驟 3: 保存並預覽報表

- **保存變更**：確保你的所有更改都已保存。
- **預覽報表**：預覽報表以確保函數正確執行，工時上限按預期顯示。

通過這些步驟，你可以在 SSRS 報表中靈活地使用自定義函數來根據不同條件設定工時上限，使報表更加動態和可重用。