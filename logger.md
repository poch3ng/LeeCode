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

在日志记录中，日志级别（或日志层级）是用来指示日志信息重要性的标准方式。不同的日志级别可以帮助区分日志信息的重要性和紧急性，使得开发者和系统管理员可以更有效地筛选和响应日志。以下是常见的日志级别，从最低到最高的重要性排序，以及各自的使用场景示例：

### 1. DEBUG
- **说明**：用于在开发过程中输出详细的调试信息，如变量值、执行路径等。
- **示例**：记录一个方法的开始和结束，以跟踪执行流程的细节。

```vb
Logger.Log("DEBUG", "开始执行SearchUser方法")
```

### 2. INFO
- **说明**：记录应用程序运行时的一般事件，如系统启动、用户操作。
- **示例**：记录用户登录成功的事件。

```vb
Logger.Log("INFO", "用户张三成功登录系统。")
```

### 3. WARNING
- **说明**：表示存在潜在错误的情形，但应用程序仍能正常运行。
- **示例**：记录配置文件缺失，但应用程序使用了默认配置的警告。

```vb
Logger.Log("WARNING", "未找到配置文件，将使用默认配置。")
```

### 4. ERROR
- **说明**：记录因为某种问题导致操作无法完成的错误事件。
- **示例**：尝试连接数据库失败。

```vb
Logger.Log("ERROR", "连接数据库失败", "无法连接到数据库服务器。请检查网络连接。")
```

### 5. FATAL
- **说明**：记录非常严重的错误事件，这种情况可能导致应用程序中止执行。
- **示例**：系统关键服务启动失败，导致应用无法运行。

```vb
Logger.Log("FATAL", "核心服务启动失败，应用将中止。")
```

使用这些日志级别时，应该在`Logger`类中预设这些级别，并在记录日志时选择适当的级别。通过这种方式，您可以更容易地管理和过滤日志信息，确保关注到重要的事件，同时还能保持日志的清晰和有用。在实践中，可能还会根据实际需求调整或增加日志级别，但上述提供了一个基本的框架。