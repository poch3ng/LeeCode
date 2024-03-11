在VB.NET中，要執行SQL查詢並獲取結果的`COUNT`值，你可以使用ADO.NET。以下是一個基本的例子，展示了如何使用`SqlConnection`和`SqlCommand`對象來執行SQL查詢，並使用`ExecuteScalar`方法來獲取查詢結果的數量。這個例子假設你使用的是Microsoft SQL Server作為數據庫。

```vb.net
Imports System.Data.SqlClient

Module Module1

    Sub Main()
        ' 定義連接字符串，請根據你的數據庫設置進行修改
        Dim connectionString As String = "Data Source=your_server_name;Initial Catalog=your_database_name;Integrated Security=True"

        ' 創建SQL查詢字符串
        Dim queryString As String = "SELECT COUNT(*) FROM your_table_name WHERE your_condition"

        ' 使用Using語句來確保連接被正確關閉和釋放
        Using connection As New SqlConnection(connectionString)
            ' 創建SqlCommand對象
            Dim command As New SqlCommand(queryString, connection)
            Try
                ' 打開數據庫連接
                connection.Open()

                ' 執行查詢並獲取結果
                Dim count As Integer = Convert.ToInt32(command.ExecuteScalar())

                ' 輸出結果
                Console.WriteLine("Count: " & count)
            Catch ex As Exception
                Console.WriteLine(ex.Message)
            End Try
        End Using
    End Sub

End Module
```

確保將`your_server_name`、`your_database_name`、`your_table_name`和`your_condition`替換為你的具體數據庫設置和查詢條件。

這段代碼首先建立與數據庫的連接，然後執行一個`SELECT COUNT(*)`查詢以獲得符合條件的行數。`ExecuteScalar`方法用於執行查詢，並返回查詢結果的第一行第一列的數據，這在只需要一個值的情況下非常有用，比如`COUNT`查詢。最後，它將這個值轉換為`Integer`，並輸出到控制台。