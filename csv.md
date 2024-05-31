如果你希望在不使用外部函式庫如 EPPlus 的情況下，從 VB MVC 專案中將數據匯出到 Excel，你可以使用 CSV 格式，因為所有的 Excel 版本都支援 CSV，並且可以直接使用文本處理來生成。這種方法不需要安裝任何額外的 NuGet 套件。下面是如何在 ASP.NET MVC 中生成並下載 CSV 文件的步驟：

### 步驟 1: 創建一個動作方法來生成 CSV 檔案

你可以在控制器中創建一個方法，用於生成 CSV 格式的數據。

```vb
Public Function ExportToCsv() As ActionResult
    ' 假設有一個獲取數據的方法，返回一個列表
    Dim data = GetData()

    Dim csvContent As New StringBuilder()
    ' 添加 CSV 頭部
    csvContent.AppendLine("Column1,Column2,Column3")

    ' 遍歷數據並添加到 CSV 內容中
    For Each item In data
        csvContent.AppendLine($"{item.Property1},{item.Property2},{item.Property3}")
    Next

    ' 設置回應類型
    Response.ContentType = "text/csv"
    Response.AddHeader("Content-Disposition", "attachment; filename=Data.csv")
    Response.ContentEncoding = Encoding.UTF8
    Response.Write(csvContent.ToString())
    Response.Flush()
    Response.End()

    Return Nothing
End Function
```

### 步驟 2: 創建一個按鈕或鏈接來調用這個動作

在你的視圖中，提供一個按鈕或鏈接供使用者點擊導出 CSV。

```html
<a href="@Url.Action("ExportToCsv", "YourControllerName")">Export to CSV</a>
```

### 補充說明

- CSV 文件是以純文本格式保存，所以使用逗號分隔值是非常基本的方法來進行數據交換。
- 確保數據中沒有包含逗號或換行符，或者如果有，你需要對這些字符進行適當的處理（例如，將數據值包含在引號中）。
- 這種方法不需要額外的庫，並且可以直接從 MVC 應用中下載 CSV 文件。

使用這個方法，你可以簡單地從你的 MVC 應用中導出數據至一個 Excel 可讀的格式，而不需依賴任何外部庫。