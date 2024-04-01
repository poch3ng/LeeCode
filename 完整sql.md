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