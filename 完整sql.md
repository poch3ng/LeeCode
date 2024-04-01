要在VB.NET WebForms中執行一個完整的資料插入（`INSERT`）操作並確認其成功，以下是一個詳細的範例，包括資料庫連接、執行 `INSERT` 語句、錯誤處理以及確認插入成功的步驟。

### 假設

- 使用的資料庫是 SQL Server。
- 有一個名為 `Users` 的表格，包含兩個欄位：`UserId` (int, 主鍵, 自動增長) 和 `UserName` (nvarchar(50))。

### 步驀 1: 添加必要的參考

在你的 VB.NET WebForms 專案中，確保已經添加了到 SQL Server 的參考，例如 `System.Data.SqlClient`。

### 步驀 2: 寫代碼進行插入操作

打開你的 WebForm 的後端代碼檔（例如 `Default.aspx.vb`），然後添加以下代碼：

```vb
Imports System.Data.SqlClient

Partial Class _Default
    Inherits System.Web.UI.Page

    Protected Sub Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        ' 資料庫連接字串（請根據實際情況進行修改）
        Dim connectionString As String = "Data Source=你的資料庫伺服器;Initial Catalog=你的資料庫名稱;Integrated Security=True"

        ' SQL INSERT 語句
        Dim insertQuery As String = "INSERT INTO Users (UserName) VALUES (@UserName)"

        Using connection As New SqlConnection(connectionString)
            ' 創建 SqlCommand 物件
            Using command As New SqlCommand(insertQuery, connection)
                ' 添加參數到你的 SQL 語句
                command.Parameters.AddWithValue("@UserName", "New User")

                Try
                    ' 打開資料庫連接
                    connection.Open()

                    ' 執行 INSERT 語句
                    Dim affectedRows As Integer = command.ExecuteNonQuery()

                    ' 檢查影響的行數
                    If affectedRows > 0 Then
                        Response.Write("Insert operation was successful.")
                    Else
                        Response.Write("No rows were inserted.")
                    End If

                Catch ex As Exception
                    ' 捕捉並處理異常
                    Response.Write("Insert operation failed: " & ex.Message)
                Finally
                    ' 確保連接被關閉
                    If connection.State = ConnectionState.Open Then
                        connection.Close()
                    End If
                End Try
            End Using
        End Using
    End Sub
End Class
```

### 說明

- 此代碼示例展示了如何在VB.NET WebForms應用程序中執行資料插入操作。
- 修改 `connectionString` 變量，以包含正確的資料庫連接資訊。
- `INSERT` 語句中使用了參數化查詢（`@UserName`），以增強安全性並防止SQL注入攻擊。
- 使用 `Try...Catch...Finally` 語句來處理可能發生的任何異常，並確保資料庫連接正確關閉。
- `ExecuteNonQuery` 方法用於執行 `INSERT` 語句，它返回一個整數，表示被影響（即插入）的行數。這個返回值用於確認插入操作是否成功。

使用這個範例作為基礎，你可以根據自己的需求進行調整和擴展，例如添加更多的欄位或處理更複雜的業務邏輯。





在VB.NET中使用事务（Transaction）可以帮助你确保数据的一致性和完整性，特别是在执行需要多个步骤的数据库操作时。如果操作过程中的任何一个步骤失败，事务可以被回滚（Rollback），数据库状态会恢复到事务开始之前的状态。

以下是一个使用事务来确保数据插入成功的VB.NET示例。这个例子假设你正在使用SQL Server数据库，但相同的概念也适用于其他数据库系统（可能需要小的语法调整）。

### 步骤 1: 设置数据库连接

首先，确定你的数据库连接字符串，并设置一个SQL连接对象。

### 步骤 2: 执行带事务的数据库操作

接下来，我们将创建一个事务，然后在这个事务内执行SQL命令。如果一切顺利，我们将提交事务；如果出现异常，我们将回滚事务以避免数据不一致。

```vb
Imports System.Data.SqlClient

Partial Class _Default
    Inherits System.Web.UI.Page

    Protected Sub Page_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Dim connectionString As String = "Data Source=你的服务器;Initial Catalog=你的数据库;Integrated Security=True"
        Using connection As New SqlConnection(connectionString)
            connection.Open()

            ' 开始一个事务
            Dim transaction As SqlTransaction = connection.BeginTransaction()

            Try
                ' 创建一个SqlCommand并且设置它的事务
                Dim command As SqlCommand = connection.CreateCommand()
                command.Transaction = transaction

                ' 添加你的SQL命令
                command.CommandText = "INSERT INTO Users (UserName) VALUES ('TestUser')"
                command.ExecuteNonQuery()

                ' 这里可以继续执行更多的命令...
                
                ' 如果一切正常，则提交事务
                transaction.Commit()
                Response.Write("Transaction committed.")
            Catch ex As Exception
                ' 如果有任何错误发生，则回滚事务
                transaction.Rollback()
                Response.Write("Transaction rolled back. Error: " & ex.Message)
            End Try
        End Using
    End Sub
End Class
```

### 注意：

- 在实际应用中，确保替换连接字符串中的占位符（如`你的服务器`和`你的数据库`）为实际的值。
- 使用事务时，务必注意异常处理是非常重要的。`Try...Catch`块确保了在执行命令过程中遇到任何错误时，事务能够被回滚，从而保护了数据库的完整性。
- `Using`语句确保即使发生错误，数据库连接也能够被正确关闭和清理。
- 在上述代码中，如果`command.ExecuteNonQuery()`执行成功，事务将被提交，这意味着更改将永久保存到数据库中。如果执行过程中抛出异常，则执行`transaction.Rollback()`回滚事务，撤销所有更改。

通过以上步骤，你可以在VB.NET WebForms应用程序中安全地使用事务来执行数据库操作，确保数据的一致性和完整性。