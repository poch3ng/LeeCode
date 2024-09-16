既然你使用的是 SQL Server Management Studio (SSMS)，你可以使用 SQL Server 的 `PIVOT` 功能或條件聚合來達成這個效果。

以下是針對 SQL Server (SSMS) 的解決方案，使用條件聚合來將屬性展開成不同的欄位：

### SQL 查詢：
```sql
SELECT 
    Part_No, 
    MAX(CASE WHEN Attribute = 'Color' THEN AttributeValue END) AS Color,
    MAX(CASE WHEN Attribute = 'Size' THEN AttributeValue END) AS Size
FROM 
    your_table
GROUP BY 
    Part_No;
```

### 說明：
- `MAX(CASE WHEN Attribute = 'Color' THEN AttributeValue END)`：這段程式碼的意思是，當 `Attribute` 是 `Color` 時，返回對應的 `AttributeValue`，並使用 `MAX()` 函數來聚合每個 `Part_No` 的值。
- `GROUP BY Part_No`：將結果按 `Part_No` 分組。

### 範例資料：
| Part_No | Attribute   | AttributeValue |
|---------|-------------|----------------|
| 123     | Color       | Red            |
| 123     | Size        | Large          |
| 456     | Color       | Blue           |
| 456     | Size        | Medium         |

### 查詢結果：
| Part_No | Color | Size  |
|---------|-------|-------|
| 123     | Red   | Large |
| 456     | Blue  | Medium|

這樣你就能根據 `Part_No`，將不同的 `Attribute` 展開成對應的欄位（例如 `Color` 和 `Size`）。如果有更多的屬性（如 `Weight`、`Height` 等），你可以依照相同邏輯加入更多的 `CASE` 條件。