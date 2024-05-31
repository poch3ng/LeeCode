在ASP.NET MVC應用中，實現`GetLatestQueryData`方法涉及到如何保存和檢索最後一次用戶執行的查詢數據。考慮到這些數據應該是針對每個用戶獨立保存的，我們可以使用ASP.NET的Session來存儲這些數據。這樣，當用戶決定導出到CSV時，我們可以從Session中取得這些數據。

### 步驟 1: 保存查詢結果到Session

當用戶執行查詢並獲得結果時，您可以將這些結果保存到Session中。這可以在查詢的動作方法中實現：

```csharp
[HttpPost]
public ActionResult SearchData(SearchModel model)
{
    var data = GetDataFromDatabase(model); // 根據查詢模型從數據庫中獲取數據
    Session["LatestQueryResults"] = data;  // 將數據保存到Session中
    return Json(data); // 將數據以JSON格式回傳給前端
}
```

### 步驟 2: 從Session中獲取最後的查詢數據

在`ExportToCsv`方法中，您可以從Session中獲取保存的數據：

```csharp
[HttpGet]
public ActionResult ExportToCsv()
{
    var data = Session["LatestQueryResults"] as List<YourDataType>; // 從Session中獲取數據並轉型
    if (data == null)
    {
        return new HttpStatusCodeResult(HttpStatusCode.BadRequest, "No data available for export.");
    }
    
    var output = ConvertToCsv(data);
    return File(Encoding.UTF8.GetBytes(output), "text/csv", "DataExport.csv");
}
```

### 注意事項

- **數據類型轉換**：在從Session取得數據時，確保正確地轉型到您的數據類型。上面的例子中使用了`List<YourDataType>`作為示例，您需要將其替換成實際的數據類型。
- **Session過期處理**：Session有過期時間，預設通常是20分鐘。如果Session過期，則存儲的數據會丟失，這種情況下如果用戶嘗試導出數據會得到一個錯誤或者無數據的提示。
- **性能和資源考慮**：保存大量數據到Session可以消耗顯著的服務器資源，特別是在用戶量大時。確保您的服務器設定能夠處理這樣的負載，或考慮使用更有效的數據儲存和緩存策略。

使用Session來保存查詢結果是一個簡單直接的方法，但要留意其對性能的影響及適當處理可能的Session過期問題。

要實現一個查詢按鈕和一個匯出Excel的按鈕，我們可以分別建立查詢和匯出的功能。下面的步驟和代碼將幫助您設定這兩個功能：

### 步驟 1: 前端設計

在前端HTML中，我們需要兩個按鈕和一個表格來顯示查詢結果：

```html
<!-- 查詢表單 -->
<input type="text" id="input1" placeholder="輸入條件1">
<input type="text" id="input2" placeholder="輸入條件2">
<button onclick="sendQuery()">查詢</button>
<button onclick="exportToExcel()">匯出Excel</button>

<!-- 用於顯示查詢結果的表格 -->
<table id="resultsTable">
    <thead>
        <tr>
            <th>Column1</th>
            <th>Column2</th>
            <th>Column3</th>
        </tr>
    </thead>
    <tbody>
        <!-- 查詢結果將填充到這裡 -->
    </tbody>
</table>
```

### 步驟 2: JavaScript 查詢和匯出功能

對於查詢和匯出功能，我們可以使用AJAX來實現與服務器的通信：

```javascript
function sendQuery() {
    const data = {
        field1: document.getElementById('input1').value,
        field2: document.getElementById('input2').value
    };

    fetch('/YourController/SearchData', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data)
    })
    .then(response => response.json())
    .then(data => {
        const table = document.getElementById('resultsTable').getElementsByTagName('tbody')[0];
        table.innerHTML = ''; // 清空現有的表格行
        data.forEach(row => {
            const newRow = table.insertRow(table.rows.length);
            newRow.insertCell(0).textContent = row.Column1;
            newRow.insertCell(1).textContent = row.Column2;
            newRow.insertCell(2).textContent = row.Column3;
        });
    })
    .catch(error => console.error('Error:', error));
}

function exportToExcel() {
    fetch('/YourController/ExportToCsv')
    .then(response => response.blob())
    .then(blob => {
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = "DataExport.csv";
        document.body.appendChild(a);
        a.click();
        a.remove();
    })
    .catch(error => console.error('Error:', error));
}
```

### 步驟 3: ASP.NET MVC 控制器動作

您需要在控制器中添加對應的動作方法來處理查詢和匯出：

```csharp
[HttpPost]
public ActionResult SearchData(SearchModel model)
{
    var data = GetDataFromDatabase(model); // 根據查詢模型取得資料
    return Json(data); // 將資料以JSON格式回傳給前端
}

[HttpGet]
public ActionResult ExportToCsv()
{
    var data = GetLatestQueryData(); // 取得最後一次查詢的資料
    var output = ConvertToCsv(data);
    return File(Encoding.UTF8.GetBytes(output), "text/csv", "DataExport.csv");
}
```

### 補充說明

1. **查詢與匯出分離**：您的查詢和匯出操作是分開的。查詢後的數據應該被保存在服務器上（例如，使用Session或Cache），以便匯出時可以重新獲取。

2. **前端和後端的整合**：確保前端發送的數據結構與後端預期的模型結構相匹配。

這種設計允許用戶先進行數據查詢，查看結果，然後選擇將結果導出

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