如果你在使用 VB.NET WebForms 進行資料庫操作，特別是執行 `INSERT` 操作並想要確認它是否成功，你可以採取以下幾個步驟來進行確認：

### 1. 使用 Exception Handling 捕捉錯誤

在 VB.NET 中，你應該使用 `Try...Catch...Finally` 語句來捕捉在執行 SQL 語句時可能出現的任何異常。如果 `INSERT` 操作因為某些原因（例如違反資料庫約束）而失敗，將會拋出一個異常。

```vb
Try
    ' 這裡是你的資料庫連接和 INSERT 操作的代碼
    ' 使用你的資料庫連接對象執行命令

    ' 如果沒有錯誤，可以認為插入操作是成功的
    Console.WriteLine("Insert operation was successful.")

Catch ex As Exception
    ' 如果有錯誤，將會捕捉到這裡
    Console.WriteLine("Insert operation failed: " & ex.Message)
Finally
    ' 清理代碼，比如關閉資料庫連接
End Try
```

### 2. 檢查影響的行數

大多數資料庫操作對象（如 `SqlCommand` 或 `OleDbCommand`）在執行 `ExecuteNonQuery` 方法後會返回一個整數值，表示被影響（插入、更新或刪除）的行數。如果返回值大於0，則表示有行被成功插入。

```vb
Dim affectedRows As Integer = command.ExecuteNonQuery()
If affectedRows > 0 Then
    Console.WriteLine("Insert operation was successful.")
Else
    Console.WriteLine("No rows were inserted.")
End If
```

### 3. 使用 Transaction 確保資料一致性

在需要確保多個操作要麼全部成功要麼全部失敗的情況下，使用資料庫事務是一個好方法。如果 `INSERT` 操作或其他操作在事務中失敗，你可以回滾事務以恢復到操作前的狀態。

```vb
Dim transaction As SqlTransaction = connection.BeginTransaction()

Try
    command.Transaction = transaction
    command.ExecuteNonQuery()

    ' 如果到達這裡，表示沒有錯誤發生
    transaction.Commit()
    Console.WriteLine("Transaction committed.")
Catch ex As Exception
    ' 出錯，回滾事務
    transaction.Rollback()
    Console.WriteLine("Transaction rolled back.")
Finally
    connection.Close()
End Try
```

以上就是在 VB.NET WebForms 中進行資料庫 `INSERT` 操作並確認它是否成功的基本方法。請根據你的實際需求和環境調整這些範例代碼。