為了實現當比對中發現不匹配時，能夠告訴你是哪一個值出錯，你可以修改程式碼來逐一比對陣列中的每個元素，並在發現不匹配時記錄是哪一個位置的值不同。

以下是修改後的程式碼，當比對過程中發現某個位置的值不匹配時，會輸出錯誤的索引和對應的值：

### 修改後的程式碼：

```vb
For Each row1 As DataRow In dataTable1.Rows
    ' 檢查 BondedIT 是否為 1
    If row1.Field(Of Integer)("BondedIT") = 1 Then
        ' 取得 BondedNo 的值並根據分號分割為陣列
        Dim bondedNoArray As String() = row1.Field(Of String)("BondedNo").Split(";"c)

        ' 在第二個表中進行比對
        For Each row2 As DataRow In dataTable2.Rows
            ' 取得 BondedNo1 的值並分割為陣列
            Dim bondedNo1Array As String() = row2.Field(Of String)("BondedNo1").Split(";"c)

            ' 先檢查兩個陣列的長度是否一致
            If bondedNoArray.Length = bondedNo1Array.Length Then
                ' 比對每個元素是否一致
                Dim isMatch As Boolean = True
                For i As Integer = 0 To bondedNoArray.Length - 1
                    If bondedNoArray(i) <> bondedNo1Array(i) Then
                        ' 如果不一致，記錄出錯的索引與值
                        Console.WriteLine($"錯誤: 第 {i + 1} 個值不匹配 - BondedNo: {bondedNoArray(i)} 與 BondedNo1: {bondedNo1Array(i)}")
                        isMatch = False
                    End If
                Next

                ' 如果所有值都匹配，則輸出匹配訊息
                If isMatch Then
                    Console.WriteLine($"完全匹配: {String.Join(";", bondedNoArray)}")
                End If
            Else
                ' 長度不一致時，直接輸出不匹配訊息
                Console.WriteLine("錯誤: BondedNo 和 BondedNo1 的長度不一致")
            End If
        Next
    End If
Next
```

### 具體實現說明：

1. **檢查長度**：首先比較 `bondedNoArray.Length` 和 `bondedNo1Array.Length`，如果長度不一致，則直接輸出長度不一致的錯誤訊息，因為這樣的情況下不需要進行具體的值比對。

2. **逐一比對**：使用 `For` 迴圈逐一比較兩個陣列中的每一個元素 (`bondedNoArray(i)` 和 `bondedNo1Array(i)`)。當發現兩者不相等時，記錄出錯的位置（索引值）和對應的值。

3. **索引值**：因為 `For` 迴圈是從 0 開始，所以在輸出錯誤訊息時，使用 `i + 1` 來表示實際的項目編號，以便符合人們的習慣（從第 1 個項目開始數）。

4. **輸出結果**：如果兩個陣列中的所有值都匹配，則輸出 "完全匹配" 訊息；如果有不匹配，則會逐個列出不匹配的索引與值。

### 測試情境：

假設 `BondedNo` 為 `"A;B;C"`，而 `BondedNo1` 為 `"A;D;C"`。

輸出的結果會是：
```
錯誤: 第 2 個值不匹配 - BondedNo: B 與 BondedNo1: D
```

如果 `BondedNo` 為 `"A;B;C"` 且 `BondedNo1` 也是 `"A;B;C"`，則會輸出：
```
完全匹配: A;B;C
```

這樣的設計可以幫助你精確地定位哪一個位置出現了不匹配，並列出具體的錯誤資訊。

如果 `BondedIT = 1` 對應的是另一個表中的 `BondedNo1`，並且 `BondedNo1` 的值是以分號 (`;`) 來分隔的多個元素，你可以根據 `BondedNo` 值進行比對，檢查 `BondedNo1` 是否包含該值。具體步驟如下：

1. 從 `DataTable` 中找到 `BondedIT = 1` 的行。
2. 取得 `BondedNo` 值，然後與另一個表中的 `BondedNo1` 欄位進行比對。
3. 使用 `Split` 方法將 `BondedNo1` 的值根據分號分隔成陣列，然後逐一比對是否包含目標 `BondedNo`。

### 具體範例：

#### 假設兩個 `DataTable`：
- 第一個表是你要檢查的表，其中有 `BondedIT` 和 `BondedNo` 欄位。
- 第二個表有 `BondedNo1` 欄位，並且 `BondedNo1` 是用分號分隔的多個值。

#### 1. 先在第一個表中找出 `BondedIT = 1` 的行，然後比對 `BondedNo`。
#### 2. 再在第二個表中找 `BondedNo1` 是否包含該 `BondedNo`。

### 程式碼範例：

```vb
' 假設 dataTable1 是包含 BondedIT 和 BondedNo 的表
' 假設 dataTable2 是包含 BondedNo1 的表

For Each row1 As DataRow In dataTable1.Rows
    ' 檢查 BondedIT 是否為 1
    If row1.Field(Of Integer)("BondedIT") = 1 Then
        ' 取得 BondedNo 的值
        Dim bondedNo As String = row1.Field(Of String)("BondedNo")

        ' 在第二個表中進行比對
        For Each row2 As DataRow In dataTable2.Rows
            ' 取得 BondedNo1 的值並分割成陣列
            Dim bondedNo1List As String() = row2.Field(Of String)("BondedNo1").Split(";"c)

            ' 檢查是否包含 BondedNo
            If bondedNo1List.Contains(bondedNo) Then
                ' 如果匹配，則執行相應的邏輯
                Console.WriteLine($"找到匹配的 BondedNo: {bondedNo} 在 BondedNo1: {String.Join(";", bondedNo1List)}")
            End If
        Next
    End If
Next
```

### 具體解釋：
1. **`Split` 方法**：`row2.Field(Of String)("BondedNo1").Split(";"c)` 將 `BondedNo1` 的字串根據分號 `;` 分割為一個陣列。`"c"` 表示用單一字元 `;` 來進行分割。
2. **比對**：`bondedNo1List.Contains(bondedNo)` 會檢查 `BondedNo1` 分割後的陣列是否包含 `BondedNo`，如果有，則表示匹配。
3. **兩個表的遍歷**：先遍歷第一個表，當 `BondedIT = 1` 時，從第二個表中找出 `BondedNo1`，並比對 `BondedNo` 是否存在於 `BondedNo1` 分隔的項目中。

### 修改後的邏輯：
- 如果 `BondedNo` 需要對應 `BondedNo1` 中的一個元素，那麼 `Split` 可以幫助你將 `BondedNo1` 中的多個值分離開來，然後你可以針對這些值進行比對。
- 適用於一對多的比對場景，即一個 `BondedNo` 可能存在於多個 `BondedNo1` 值中。

這樣的程式碼能夠實現你對 `BondedIT` 為 1 的 `BondedNo` 與另一個表中的 `BondedNo1` 進行比對的需求。

如果你想從 `DataTable` 中找到 `BondedIT` 欄位值為 1 的行，並取得該行的 `BondedNo` 欄位的值，你可以在迴圈中進行比對，然後根據條件來取得 `BondedNo` 欄位的值。

以下是具體的實現範例：

### 1. 使用迴圈來比對 `BondedIT` 是否為 1，並取得 `BondedNo`：

```vb
For Each row As DataRow In dataTable.Rows
    ' 檢查 BondedIT 欄位是否為 1
    If row("BondedIT").ToString() = "1" Then
        ' 如果 BondedIT 為 1，取得 BondedNo 欄位的值
        Dim bondedNo As String = row("BondedNo").ToString()
        Console.WriteLine("BondedNo: " & bondedNo)
    End If
Next
```

### 2. 使用 `Field(Of T)` 來取得具體型別的值並進行比對：

這樣可以確保你取得的值是正確的型別，而不必轉換為字串後再比對。

```vb
For Each row As DataRow In dataTable.Rows
    ' 使用 Field(Of T) 方法來取得數值進行比對
    Dim bondedIT As Integer = row.Field(Of Integer)("BondedIT")

    ' 檢查 BondedIT 是否為 1
    If bondedIT = 1 Then
        ' 取得 BondedNo 的值
        Dim bondedNo As String = row.Field(Of String)("BondedNo")
        Console.WriteLine("BondedNo: " & bondedNo)
    End If
Next
```

### 3. 若想將所有符合條件的 `BondedNo` 存入列表：

你可以將所有符合 `BondedIT = 1` 的 `BondedNo` 值收集起來，並進行進一步的操作，例如儲存在一個列表中。

```vb
Dim bondedNoList As New List(Of String)()

For Each row As DataRow In dataTable.Rows
    ' 檢查 BondedIT 是否為 1
    If row.Field(Of Integer)("BondedIT") = 1 Then
        ' 將符合條件的 BondedNo 加入列表
        bondedNoList.Add(row.Field(Of String)("BondedNo"))
    End If
Next

' 顯示所有符合條件的 BondedNo
For Each bondedNo As String In bondedNoList
    Console.WriteLine("BondedNo: " & bondedNo)
Next
```

### 解釋：
1. **比對條件**：使用 `If row("BondedIT").ToString() = "1"` 或 `row.Field(Of Integer)("BondedIT") = 1` 來檢查 `BondedIT` 欄位的值是否為 1。
2. **取得 `BondedNo`**：如果條件符合，則使用 `row("BondedNo").ToString()` 或 `row.Field(Of String)("BondedNo")` 來取得對應的 `BondedNo` 欄位的值。
3. **列表收集**：如果需要將所有符合條件的 `BondedNo` 值收集起來，可以將它們加入一個 `List(Of String)` 中，然後進行進一步的操作。

這樣的邏輯能夠讓你從 `DataTable` 中篩選出 `BondedIT` 為 1 的所有 `BondedNo`，並對它們進行處理。

在 `DataTable` 中，你可以通過 `DataRow` 來訪問特定的欄位。每一個 `DataRow` 代表一行資料，你可以使用欄位名稱或索引來取得特定欄位的值。

以下是幾種常見的方法來取得 `DataTable` 中特定欄位的資料：

### 1. 使用欄位名稱來取得資料：

```vb
For Each row As DataRow In dataTable.Rows
    ' 使用欄位名稱來取得資料
    Dim ivnoValue As String = row("IVNO").ToString()
    Console.WriteLine("IVNO: " & ivnoValue)
Next
```

### 2. 使用欄位索引來取得資料：

如果你知道欄位的索引位置（0 為第一個欄位），你也可以使用欄位索引來取得資料：

```vb
For Each row As DataRow In dataTable.Rows
    ' 使用欄位索引來取得資料（假設 IVNO 是第 0 個欄位）
    Dim ivnoValue As String = row(0).ToString()
    Console.WriteLine("IVNO: " & ivnoValue)
Next
```

### 3. 使用 `Field(Of T)` 方法來取得具體資料類型：

你也可以使用 `Field(Of T)` 方法來取得特定型別的資料，這樣你可以避免將資料轉換為字串再轉換回特定型別：

```vb
For Each row As DataRow In dataTable.Rows
    ' 使用 Field(Of T) 來取得具體型別的資料
    Dim ivnoValue As String = row.Field(Of String)("IVNO")
    Console.WriteLine("IVNO: " & ivnoValue)
Next
```

### 範例整合：

假設你想要取得 `DataTable` 中的 `IVNO` 欄位並進行操作，你可以這樣做：

```vb
Dim dataTable As DataTable = ' 你的 DataTable 資料

If dataTable.Rows.Count > 0 Then
    For Each row As DataRow In dataTable.Rows
        ' 使用欄位名稱取得特定欄位的值
        Dim ivnoValue As String = row("IVNO").ToString()
        Console.WriteLine("IVNO: " & ivnoValue)
        
        ' 你可以在這裡進行進一步的邏輯處理
    Next
Else
    Console.WriteLine("沒有找到符合的資料")
End If
```

### 注意事項：
- 當你取得欄位值時，建議使用欄位名稱，因為這樣程式碼的可讀性更高，也不易因為資料表結構變動而出錯。
- 如果有可能遇到 `DBNull` 的情況，可以使用 `IsDBNull(row("欄位名"))` 來進行檢查，避免轉換錯誤。

如果你在這個 class 中已經有一個持續存在的資料庫連線物件 `conBusmang`，並且想要重用這個連線來執行查詢，那麼你可以修改你的程式碼來避免每次都建立新的 `SqlConnection`，而是直接使用現有的連線。

以下是修改後的範例，假設 `conBusmang` 是一個已經打開的資料庫連線：

### 修改後的程式碼：

```vb
Imports System.Data.SqlClient
Imports System.Data

Public Class YourClass
    ' 假設這裡有一個全局的資料庫連線
    Private conBusmang As SqlConnection

    ' 建構子或其他方法初始化資料庫連線
    Public Sub New(connectionString As String)
        ' 初始化資料庫連線
        conBusmang = New SqlConnection(connectionString)
        conBusmang.Open() ' 確保連線已打開
    End Sub

    ' 取得WMS_Bonded_v資料表的方法
    Public Function 取得WMSBonded資料表(row As DataRow) As DataTable
        ' 建立一個空的 DataTable
        Dim resultTable As New DataTable()

        ' SQL 查詢，根據 IVNO 條件從 WMS_Bonded_v 表格中查詢
        Dim query As String = "SELECT * FROM WMS_Bonded_v WHERE IVNO = @IVNO"

        ' 使用現有的資料庫連線
        Using command As New SqlCommand(query, conBusmang)
            Try
                ' 將 DataRow 中的 IVNO 值作為 SQL 查詢的參數
                command.Parameters.AddWithValue("@IVNO", row("IVNO"))

                ' 使用 SqlDataAdapter 將結果填充到 DataTable
                Using adapter As New SqlDataAdapter(command)
                    adapter.Fill(resultTable)
                End Using
            Catch ex As Exception
                ' 錯誤處理
                Console.WriteLine("發生錯誤: " & ex.Message)
            End Try
        End Using

        ' 返回填充的 DataTable
        Return resultTable
    End Function

    ' 清理連線資源的析構方法
    Protected Overrides Sub Finalize()
        Try
            If conBusmang IsNot Nothing AndAlso conBusmang.State = ConnectionState.Open Then
                conBusmang.Close()
            End If
        Finally
            MyBase.Finalize()
        End Try
    End Sub
End Class
```

### 修改要點：

1. **資料庫連線的重用**：在這裡，我們使用 `conBusmang` 作為一個全局變數，代表資料庫連線，並在 `New` 方法（建構子）中初始化並打開連線。這樣，你的查詢操作可以重用這個連線，而不是每次執行查詢時都建立新連線。
   
2. **使用現有連線**：在 `取得WMSBonded資料表` 函式中，`SqlCommand` 使用現有的 `conBusmang` 連線物件，而不是每次都創建新的 `SqlConnection`。

3. **資源清理**：為了確保連線在不再使用時正確關閉，你可以在 class 的析構方法中關閉連線（`Finalize`），這樣當物件被垃圾回收時，連線會被正確地關閉。你也可以選擇實現 `IDisposable` 介面來更好地控制資源釋放。

### 呼叫方式：

```vb
' 建立 class 的實例並傳入連線字串
Dim myClass As New YourClass("你的連線字串")

Dim row As DataRow = ' 你的 DataRow 資料，包含 IVNO 欄位
Dim table As DataTable = myClass.取得WMSBonded資料表(row)

' 檢查 DataTable 是否有資料
If table.Rows.Count > 0 Then
    ' 有匹配資料，進行比對或其他操作
    Console.WriteLine("找到符合的資料")
Else
    ' 沒有匹配資料
    Console.WriteLine("沒有找到符合的資料")
End If
```

這樣做的好處是減少了每次查詢都創建和關閉連線的開銷，特別是在連線需要重複使用的情況下，能提高性能並減少連線管理的複雜度。

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