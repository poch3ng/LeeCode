如果你的 SQL 查詢是要從資料庫中查詢符合特定 `IVNO` 條件的資料，那麼你可以將這個條件應用到 `SqlCommand` 內，並使用 `SqlDataAdapter` 來執行查詢，然後將結果存入 `DataTable` 中。這樣你可以根據查詢的結果進行比對或其他操作。

### 具體的範例程式碼：

```vb
Imports System.Data.SqlClient
Imports System.Data

Public Function 取得WMSBonded資料表(row As DataRow) As DataTable
    ' 建立一個空的 DataTable
    Dim resultTable As New DataTable()

    ' 資料庫連接字串
    Dim connectionString As String = "Server=你的伺服器;Database=你的資料庫;User Id=你的用戶名;Password=你的密碼;"

    ' SQL 查詢，根據 IVNO 條件從 WMS_Bonded_v 表格中查詢
    Dim query As String = "SELECT * FROM WMS_Bonded_v WHERE IVNO = @IVNO"

    ' 使用 SqlConnection 連接資料庫
    Using connection As New SqlConnection(connectionString)
        Try
            connection.Open()

            ' 使用 SqlCommand 來執行查詢
            Using command As New SqlCommand(query, connection)
                ' 將 DataRow 中的 IVNO 值作為 SQL 查詢的參數
                command.Parameters.AddWithValue("@IVNO", row("IVNO"))

                ' 使用 SqlDataAdapter 將結果填充到 DataTable
                Using adapter As New SqlDataAdapter(command)
                    adapter.Fill(resultTable)
                End Using
            End Using
        Catch ex As Exception
            ' 錯誤處理
            Console.WriteLine("發生錯誤: " & ex.Message)
        End Try
    End Using

    ' 返回填充的 DataTable
    Return resultTable
End Function
```

### 這個函式的詳細說明：

1. **SQL 查詢**: 查詢語句 `SELECT * FROM WMS_Bonded_v WHERE IVNO = @IVNO` 將根據傳入的 `DataRow` 中的 `IVNO` 值來過濾結果。你需要確保 `DataRow` 中有一個名為 `IVNO` 的欄位。
2. **參數化查詢**: 使用 `command.Parameters.AddWithValue("@IVNO", row("IVNO"))` 來防止 SQL 注入，同時根據 `DataRow` 內的 `IVNO` 值進行過濾。
3. **回傳 DataTable**: 最終返回一個包含查詢結果的 `DataTable`，你可以用來進行進一步的檢查或操作。

### 呼叫方式：

你可以這樣呼叫這個函式來檢查 `IVNO` 是否存在於資料庫中：

```vb
Dim row As DataRow = ' 你的 DataRow 資料，包含 IVNO 欄位
Dim table As DataTable = 取得WMSBonded資料表(row)

' 檢查 DataTable 是否有資料
If table.Rows.Count > 0 Then
    ' 有匹配資料，進行比對或其他操作
    Console.WriteLine("找到符合的資料")
Else
    ' 沒有匹配資料
    Console.WriteLine("沒有找到符合的資料")
End If
```

### 說明：

- 當你執行查詢後，`table.Rows.Count` 將包含查詢返回的行數。如果這個值大於 0，則表示資料庫中存在符合 `IVNO` 的資料；否則，則沒有匹配的資料。
要在 VB.NET 中連線到資料庫並比對 `DataRow` 內的資料，首先需要使用適當的資料庫連接技術（如 `SqlConnection` 連接到 SQL Server）。這裡提供一個範例，展示如何進行資料庫連線，查詢資料，並與傳入的 `DataRow` 進行比對。

### 假設你要比對某欄位的值，範例如下：

1. 使用 `SqlConnection` 來連接資料庫。
2. 使用 SQL 查詢從資料庫中獲取需要比對的資料。
3. 與 `DataRow` 中的資料進行比對。

範例程式碼：

```vb
Imports System.Data.SqlClient

Public Function 檢查DataRow與資料庫(row As DataRow) As Boolean
    Dim isSame As Boolean = False

    ' 資料庫連接字串，替換成你的資料庫連接資訊
    Dim connectionString As String = "Server=你的伺服器;Database=你的資料庫;User Id=你的用戶名;Password=你的密碼;"
    
    ' SQL 查詢，比對的條件替換成你要的欄位
    Dim query As String = "SELECT * FROM 你的表格 WHERE 你的欄位名稱 = @value"

    ' 使用 SqlConnection 連接資料庫
    Using connection As New SqlConnection(connectionString)
        Try
            connection.Open()

            ' 創建 SqlCommand 並參數化查詢以防止 SQL 注入
            Using command As New SqlCommand(query, connection)
                ' 將 DataRow 中的值作為 SQL 查詢的參數
                command.Parameters.AddWithValue("@value", row("你的欄位名稱"))

                ' 執行查詢
                Using reader As SqlDataReader = command.ExecuteReader()
                    If reader.HasRows Then
                        ' 如果找到匹配的資料，則兩者相同
                        isSame = True
                    End If
                End Using
            End Using
        Catch ex As Exception
            ' 錯誤處理
            Console.WriteLine("發生錯誤: " & ex.Message)
        End Try
    End Using

    Return isSame
End Function
```

### 使用說明：

1. **連接字串**: 替換成你資料庫的實際連接字串。
2. **SQL 查詢**: 將 `query` 替換為你實際想要執行的 SQL 語句。這裡使用參數化查詢，防止 SQL 注入。
3. **比對欄位**: 假設你要比對 `DataRow` 中的某個欄位值是否在資料庫中存在，這個值會通過 `command.Parameters.AddWithValue()` 方法傳入。

### 呼叫範例：

```vb
Dim row As DataRow = ' 你的 DataRow 資料
Dim result As Boolean = 檢查DataRow與資料庫(row)

If result Then
    ' DataRow 與資料庫資料相同
Else
    ' 不相同
End If
```

這個流程會連接到資料庫，查詢資料並與傳入的 `DataRow` 進行比對，最終返回 `True` 或 `False`。