如果您需要檢查多個字符串條件，且這些條件很多，手動列出每一個可能會很繁瑣且容易出錯。一種更簡潔的方法是使用 `IN` 關鍵字，這樣可以將所有的值放在一個集合中檢查，從而簡化查詢。這裡是如何使用 `IN` 來簡化您的 `CASE` 語句：

```sql
SELECT 
  CASE 
    WHEN ColumnName IN ('Value1', 'Value2', 'Value3', ..., 'ValueN') THEN 10
    ELSE OtherValue  -- 如果不符合上述任何條件，則可以指定其他值
  END as ResultColumnName
FROM YourTableName;
```

在這個例子中，`ColumnName` 是您的數據表中包含待檢查值的列名，而 `'Value1'`, `'Value2'`, `'Value3'`, ..., `'ValueN'` 是您要檢查的所有可能的字符串值。您只需將這些值按需填入 `IN` 語句中。這樣，如果列中的值匹配列表中的任何一個值，則返回 10；否則，返回 `OtherValue`。

使用 `IN` 語句不僅可以減少您的工作量，還可以讓 SQL 查詢