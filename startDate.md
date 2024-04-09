如果您是在使用 SQL Server Management Studio (SSMS) 和 Microsoft SQL Server，您需要采用T-SQL语言的特定函数来完成您的需求。以下是根据您的需求调整的SQL查询，用于选择`startDate`离当前时间最近的且当前日期不超过`endDate`的记录。

### 步骤1: 确定您的数据表结构

假设您的数据表名为`events`，并且至少有以下两个字段：

- `startDate`：事件开始的日期
- `endDate`：事件结束的日期

这些字段应该是`DATE`或`DATETIME`类型。

### 步骤2: 编写SQL查询

在 SQL Server 中，您可以使用`GETDATE()`函数来获取当前日期和时间，然后使用`DATEDIFF`函数来计算两个日期之间的差异。以下是一个可能的SQL查询，它满足您的需求：

```sql
SELECT TOP 1 *
FROM events
WHERE endDate >= CAST(GETDATE() AS DATE)
ORDER BY ABS(DATEDIFF(SECOND, startDate, GETDATE()))
```

这个查询首先筛选出`endDate`大于或等于当前日期的所有事件，然后按`startDate`与当前时间差的绝对值排序，最后选择最顶部的一条记录。

### 步骤3: 执行查询

在 SQL Server Management Studio (SSMS) 中执行上述SQL查询。这将返回一条记录：`startDate`离当前时间最近的且当前日期不超过`endDate`的事件。

### 注意事项

- 确保`startDate`和`endDate`字段的类型是日期类型，如`DATE`或`DATETIME`。
- `CAST(GETDATE() AS DATE)`是将`GETDATE()`返回的当前日期和时间转换为仅包含日期的形式，以确保与`endDate`进行正确比较。
- `DATEDIFF(SECOND, startDate, GETDATE())`计算从`startDate`到当前时间的秒数差异。您可以根据需要调整时间单位，例如使用`DAY`来代替`SECOND`，如果您关心的是天数差异而不是秒数差异。
- 使用`TOP 1`来确保查询结果只返回一条记录。

根据这些指导，您应该能够满足您的需求，从数据库中选择出符合条件的记录。