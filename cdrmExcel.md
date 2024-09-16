在 VB WebForm 中將 SQL 查詢結果匯出成 Excel 的常見方法是使用 `DataTable` 將 SQL 結果存取，然後利用 `HttpResponse` 將這些結果導出為 Excel 格式。以下是步驟說明：

### 步驟 1: 取得 SQL 結果

1. 使用 `SqlConnection` 連接到資料庫。
2. 使用 `SqlCommand` 執行 SQL 查詢。
3. 將查詢結果存入 `DataTable`。

```vb
Dim connStr As String = "YourConnectionString"
Dim query As String = "SELECT * FROM YourTable"
Dim dt As New DataTable()

Using conn As New SqlConnection(connStr)
    Using cmd As New SqlCommand(query, conn)
        conn.Open()
        Using reader As SqlDataReader = cmd.ExecuteReader()
            dt.Load(reader)
        End Using
    End Using
End Using
```

### 步驟 2: 將 DataTable 導出為 Excel

可以使用 `HttpResponse` 來將資料輸出為 Excel 格式的檔案。這裡使用 CSV 格式匯出，因為 CSV 格式能直接被 Excel 開啟。

```vb
Protected Sub ExportToExcel(ByVal sender As Object, ByVal e As EventArgs)
    Dim attachment As String = "attachment; filename=DataExport.csv"
    Response.ClearContent()
    Response.AddHeader("content-disposition", attachment)
    Response.ContentType = "application/csv"

    ' 將 DataTable 內容寫入 Response
    Dim sw As New StringWriter()
    Dim writer As New HtmlTextWriter(sw)

    ' 寫入欄位名稱
    For Each col As DataColumn In dt.Columns
        sw.Write(col.ColumnName & ",")
    Next
    sw.Write(sw.NewLine)

    ' 寫入資料列
    For Each row As DataRow In dt.Rows
        For Each col As DataColumn In dt.Columns
            sw.Write(row(col).ToString() & ",")
        Next
        sw.Write(sw.NewLine)
    Next

    Response.Write(sw.ToString())
    Response.[End]()
End Sub
```

### 步驟 3: 在 WebForm 中添加匯出按鈕

```aspx
<asp:Button ID="btnExport" runat="server" Text="匯出 Excel" OnClick="ExportToExcel" />
```

### 步驟總結
1. 先從 SQL 中抓取資料並儲存在 `DataTable`。
2. 使用 `HttpResponse` 將資料導出成 CSV 格式 (Excel 可直接開啟)。
3. 在 WebForm 中添加一個按鈕，當點擊時觸發匯出功能。

這樣便可以輕鬆地將 SQL 結果匯出到 Excel。