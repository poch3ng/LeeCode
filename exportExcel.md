將`DataTable`的資料轉換成Excel檔案在ASP.NET應用中是一個常見的需求。這裡有一個簡單的示例，展示如何使用`Response`對象直接在瀏覽器中生成和下載一個Excel檔案，無需使用第三方庫。請注意，這個方法生成的是一個基於HTML的簡單Excel文件，適合基本用途。對於更複雜的Excel檔案操作，您可能需要使用如EPPlus、ClosedXML等庫。

### 步驟1: 創建DataTable

首先，您需要一個包含資料的`DataTable`。

```vb
Dim table As New DataTable()
' 添加列
table.Columns.Add("ID", GetType(Integer))
table.Columns.Add("Name", GetType(String))
table.Columns.Add("Age", GetType(Integer))
' 添加資料行
table.Rows.Add(1, "John Doe", 30)
table.Rows.Add(2, "Jane Doe", 29)
' 更多資料行...
```

### 步驟2: 轉換DataTable為Excel格式並下載

然後，您可以通過下面的代碼將`DataTable`轉換為一個簡單的Excel文件（實際上是一個`.xls`格式的HTML文件），並提示用戶下載。

```vb
' 設置HTTP響應的內容類型為Excel文件
Response.Clear()
Response.Buffer = True
Response.Charset = ""
Response.ContentType = "application/vnd.ms-excel"
Response.AddHeader("content-disposition", "attachment;filename=DataTableToExcel.xls")

Using sw As New System.IO.StringWriter()
    Using hw As New System.Web.UI.HtmlTextWriter(sw)
        ' 創建一個HtmlTable
        Dim htmlTable As New System.Web.UI.WebControls.Table()
        Dim row As TableRow = Nothing
        Dim cell As TableCell = Nothing
        
        ' 添加表頭
        row = New TableRow()
        For Each column As DataColumn In table.Columns
            cell = New TableCell()
            cell.Text = column.ColumnName
            row.Cells.Add(cell)
        Next
        htmlTable.Rows.Add(row)
        
        ' 添加數據行
        For Each dataRow As DataRow In table.Rows
            row = New TableRow()
            For Each column As DataColumn In table.Columns
                cell = New TableCell()
                cell.Text = dataRow(column).ToString()
                row.Cells.Add(cell)
            Next
            htmlTable.Rows.Add(row)
        Next
        
        ' 渲染表格到HtmlTextWriter
        htmlTable.RenderControl(hw)
        
        ' 輸出HtmlTextWriter內容到HTTP響應
        Response.Output.Write(sw.ToString())
        Response.Flush()
        Response.End()
    End Using
End Using
```

### 注意

- 這個方法生成的是一個基於HTML的Excel文件，而不是一個真正的`.xlsx`或`.xls`文件。大多數現代的Excel版本都可以打開這樣的文件，但如果文件非常大或包含複雜的格式，這種方法可能不適用。
- 對於需要更複雜的Excel文件操作（如格式化、公式、多個工作表等），建議使用專門的庫，例如EPPlus或ClosedXML。這些庫提供了豐富的API來處理Excel文件，但需要額外安裝。

以上代碼示例應該可以滿足基本的需求，將`DataTable`的數據導出為Excel文件並提供下載功能。



要將`DataSet`的資料轉換為Excel文件並提供下載，您可以遵循類似將`DataTable`轉換為Excel的方法。因為`DataSet`可能包含多個`DataTable`，您需要決定如何在Excel文件中表示這些不同的`DataTable`。一種簡單的方法是將每個`DataTable`轉換為Excel文件中的不同工作表，但由於基於HTML的簡單Excel文件不支持多個工作表，這裡我們將所有`DataTable`的數據合併到一個工作表中，或者您也可以為每個`DataTable`創建單獨的Excel文件。

以下是將`DataSet`中所有`DataTable`的數據合併到一個簡單的Excel文件中的示例代碼：

```vb
' 設置HTTP響應的內容類型為Excel文件
Response.Clear()
Response.Buffer = True
Response.Charset = ""
Response.ContentType = "application/vnd.ms-excel"
Response.AddHeader("content-disposition", "attachment;filename=DataSetToExcel.xls")

Using sw As New System.IO.StringWriter()
    Using hw As New System.Web.UI.HtmlTextWriter(sw)
        ' 對DataSet中的每個DataTable進行迭代
        For Each table As DataTable In ds.Tables
            ' 創建一個HtmlTable
            Dim htmlTable As New System.Web.UI.WebControls.Table()
            Dim row As TableRow = Nothing
            Dim cell As TableCell = Nothing
            
            ' 添加表頭
            row = New TableRow()
            For Each column As DataColumn In table.Columns
                cell = New TableCell()
                cell.Text = column.ColumnName
                row.Cells.Add(cell)
            Next
            htmlTable.Rows.Add(row)
            
            ' 添加數據行
            For Each dataRow As DataRow In table.Rows
                row = New TableRow()
                For Each column As DataColumn In table.Columns
                    cell = New TableCell()
                    cell.Text = dataRow(column).ToString()
                    row.Cells.Add(cell)
                Next
                htmlTable.Rows.Add(row)
            Next
            
            ' 渲染表格到HtmlTextWriter
            htmlTable.RenderControl(hw)

            ' 在HtmlTextWriter中添加一些空間作為不同DataTable的分隔
            hw.Write("<br/>")
        Next
        
        ' 輸出HtmlTextWriter內容到HTTP響應
        Response.Output.Write(sw.ToString())
        Response.Flush()
        Response.End()
    End Using
End Using
```

### 注意

- 此方法將`DataSet`中的所有`DataTable`合併到一個基於HTML的Excel文件中。這意味著所有數據將位於同一個工作表中，並且通過空行來分隔不同的`DataTable`。
- 如果您需要更複雜的功能（例如創建包含多個工作表的真正的`.xlsx`文件），則需要使用專門的Excel處理庫，如EPPlus或ClosedXML。這些庫提供了創建和操作實際Excel文件（包括支持多個工作表）的能力，但需要額外安裝並在您的項目中引入。
- 上面的示例代碼適用於基本需求，且操作相對簡單。這種方法不依賴於第三方庫，但功能有限。