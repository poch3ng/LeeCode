若要根據一個表中的 `Day` 欄位值去查找另一個表中相對應的 `CLS1`, `CLS2`, `CLS3` 的值，你需要一個 SQL 查詢來根據 `Day` 的值動態選擇欄位。以下提供一種方法來實現這個需求，這裡使用的是一種通用的 SQL 語法。這個例子假設你的兩個表分別名為 `DaysTable` 和 `ValuesTable`。

### 1. 使用 CASE 語句

你可以使用 SQL 中的 `CASE` 語句來根據 `Day` 的值從 `ValuesTable` 中選擇相應的 `CLS` 欄位：

```sql
SELECT 
    d.Day,
    CASE 
        WHEN d.Day = 1 THEN v.CLS1
        WHEN d.Day = 2 THEN v.CLS2
        WHEN d.Day = 3 THEN v.CLS3
        ELSE NULL
    END AS CLSValue
FROM 
    DaysTable d
CROSS JOIN
    (SELECT TOP 1 CLS1, CLS2, CLS3 FROM ValuesTable) v
```

### 說明：

- **`DaysTable` 和 `ValuesTable`:** 假設 `DaysTable` 是包含 `Day` 欄位的表，`ValuesTable` 是包含 `CLS1`, `CLS2`, `CLS3` 的表。
- **`CASE`:** 根據 `DaysTable` 中的 `Day` 值選擇 `ValuesTable` 中相應的 `CLS` 欄位。例如，如果 `Day` 是 1，則選擇 `CLS1`。
- **`CROSS JOIN`:** 因為 `ValuesTable` 只有一行，使用 `CROSS JOIN` 來與每一個 `Day` 值關聯。這假設 `ValuesTable` 中只有一個記錄。如果 `ValuesTable` 有多條記錄，則需要進一步確定如何選擇相應的行。

### 注意：

- 確保 `DaysTable` 中的 `Day` 值範圍與 `ValuesTable` 中的 `CLS` 欄位匹配。
- 如果你的具體數據庫系統（如 MySQL, PostgreSQL, Oracle）有特定的語法或函數，你可能需要稍作調整。

這個查詢為一個基本的例子，根據你的實際數據庫環境和需求，可能需要進行適當的修改。如果你需要針對特定數據庫的進一步幫助，請提供更多相關信息。