要更新数据库中所有 `Cuno='Cuno995'` 的记录的 `Company_Name` 字段，您需要编写一个 SQL 更新语句。请注意，实际的 SQL 语句可能会根据您使用的数据库（如 SQL Server, MySQL, PostgreSQL 等）略有不同，但基本的语法是类似的。

以下是一个基本的 SQL 更新语句示例，假设您使用的数据库支持标准的 SQL 语法，如 SQL Server：

```sql
UPDATE your_table_name
SET Company_Name = '新的公司名称'
WHERE Cuno = 'Cuno995';
```

在这个 SQL 语句中，`your_table_name` 应该被替换为包含您想要更新记录的实际表名。`'新的公司名称'` 应该被替换为您想要设置的新公司名称。

### 注意事项
- 在执行这类更新操作之前，建议先备份数据库或执行一个 `SELECT` 查询来确认您将要更新的记录，以防止数据丢失或错误更新。
- 确保 `WHERE` 子句正确，以免更新到不期望的记录。
- 如果您使用的是像 SQL Server 这样的数据库管理系统，您可能还需要考虑事务的使用，以便在出现错误时能够回滚更改。

### 在 Visual Basic 中执行 SQL 更新

如果您在 Visual Basic 应用程序中需要执行这个更新，您可以使用 ADO.NET。以下是使用 `SqlCommand` 的一个基本示例：

```vb
Dim connectionString As String = "您的数据库连接字符串"
Dim query As String = "UPDATE your_table_name SET Company_Name = '新的公司名称' WHERE Cuno = 'Cuno995';"

Using connection As New SqlConnection(connectionString)
    Dim command As New SqlCommand(query, connection)
    Try
        connection.Open()
        Dim result As Integer = command.ExecuteNonQuery()
        If result > 0 Then
            Console.WriteLine("更新成功")
        Else
            Console.WriteLine("没有找到匹配的记录进行更新")
        End If
    Catch ex As Exception
        Console.WriteLine("更新过程中发生错误：" & ex.Message)
    End Try
End Using
```

请确保替换 `您的数据库连接字符串` 和 `your_table