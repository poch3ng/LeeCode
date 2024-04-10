以下是一个简单的VB.NET WebForms示例，展示如何实现一个基本的日志记录功能，将日志信息存储到数据库中。我们将创建一个名为`Logger`的类来处理日志的记录工作，并在数据库中创建一个相应的表来存储这些日志。

### 第1步：创建数据库表

首先，在您的数据库中创建一个表来存储日志数据。以下是一个简单的SQL脚本示例：

```sql
CREATE TABLE ApplicationLogs (
    LogID INT IDENTITY(1,1) PRIMARY KEY,
    LogDate DATETIME NOT NULL DEFAULT GETDATE(),
    LogLevel VARCHAR(50),
    LogMessage VARCHAR(MAX),
    ExceptionMessage VARCHAR(MAX)
);
```

### 第2步：创建`Logger`类

在您的ASP.NET WebForms项目中创建一个新的类文件（例如，名为`Logger.vb`），并添加以下代码来实现日志记录功能：

```vb
Imports System.Data.SqlClient

Public Class Logger
    Private Shared ReadOnly connectionString As String = System.Configuration.ConfigurationManager.ConnectionStrings("YourConnectionString").ToString()

    Public Shared Sub Log(LogLevel As String, LogMessage As String, Optional ExceptionMessage As String = "")
        Dim query As String = "INSERT INTO ApplicationLogs (LogLevel, LogMessage, ExceptionMessage) VALUES (@LogLevel, @LogMessage, @ExceptionMessage)"
        
        Using conn As New SqlConnection(connectionString)
            Using cmd As New SqlCommand(query, conn)
                cmd.Parameters.AddWithValue("@LogLevel", LogLevel)
                cmd.Parameters.AddWithValue("@LogMessage", LogMessage)
                If String.IsNullOrEmpty(ExceptionMessage) Then
                    cmd.Parameters.AddWithValue("@ExceptionMessage", DBNull.Value)
                Else
                    cmd.Parameters.AddWithValue("@ExceptionMessage", ExceptionMessage)
                End If
                
                conn.Open()
                cmd.ExecuteNonQuery()
            End Using
        End Using
    End Sub
End Class
```

确保替换`YourConnectionString`为您的数据库连接字符串的名称，该字符串应该在`Web.config`文件中定义。

### 第3步：使用`Logger`类记录日志

现在，您可以在WebForms应用程序的任何位置调用`Logger`类中的`Log`方法来记录日志了。例如，您可以在捕获异常的`Catch`块中使用它：

```vb
Try
    ' 尝试执行一些代码
Catch ex As Exception
    Logger.Log("Error", "发生错误", ex.Message)
End Try
```

或者，记录一条简单的信息日志：

```vb
Logger.Log("Info", "用户登录成功")
```

这样，每当调用`Log`方法时，相关的日志信息就会被存储到数据库的`ApplicationLogs`表中。

### 注意

- 确保Web应用程序有足够的权限连接到数据库，并对`ApplicationLogs`表有插入数据的权限。
- 考虑到性能和安全性，对记录日志的方法进行适当的异常处理和优化。