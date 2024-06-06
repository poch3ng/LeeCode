若要在 SQL 中將31個 `CLS` 欄位（如 `CLS1`, `CLS2`, ... `CLS31`）整合成單一表格，且希望不逐一列出所有欄位，解決方案通常會受到具體數據庫系統的支援限制。大部分標準的 SQL 環境不直接支援生成動態列名的查詢，但你可以使用一些間接的方法來達成類似的目的。

### 1. 動態 SQL

如先前提到，使用動態 SQL 是一個選擇。這涉及到構建一個 SQL 字串，其中包含所有的欄位名稱，並執行該查詢。這可以通過編寫一個腳本或使用存儲過程完成。這裡提供一個基本的範例：

```sql
DECLARE @sql AS VARCHAR(MAX) = 'SELECT ';

-- 動態構建 SELECT 語句
DECLARE @i INT = 1;
WHILE @i <= 31
BEGIN
    SET @sql = @sql + 'MAX(CASE WHEN Day = ' + CAST(@i AS VARCHAR) + ' THEN CLS' + CAST(@i AS VARCHAR) + ' ELSE NULL END) AS CLS' + CAST(@i AS VARCHAR);
    IF @i < 31
        SET @sql = @sql + ', ';
    SET @i = @i + 1;
END;

SET @sql = @sql + ' FROM (SELECT Day, CLS1, CLS2, CLS3, ..., CLS31 FROM ValuesTable) AS Days';

EXEC(@sql);
```

### 2. 使用現代數據庫功能

如果你使用的是支持高度動態查詢的數據庫系統，如 PostgreSQL 的 crosstab 函數或者是 Oracle 的 PIVOT 函數，可以更簡便地實現這一需求。

#### PostgreSQL 示例：

```sql
-- 使用 crosstab 函數需要先安裝 tablefunc 模組
CREATE EXTENSION IF NOT EXISTS tablefunc;

SELECT * FROM crosstab(
  'SELECT Day, ''CLS'' || Day, CLSValue FROM unnest(ARRAY[CLS1, CLS2, ..., CLS31]) WITH ORDINALITY AS t(CLSValue, Day)'
) AS final_result(Day int, CLS1 text, CLS2 text, ..., CLS31 text);
```

### 注意事項

- 以上方法需要根據你的具體數據庫調整。不同的數據庫系統對動態 SQL 的支持程度不同。
- 使用動態 SQL 時要注意防範 SQL 注入的風險，尤其是當 SQL 語句的一部分來自於不可靠的輸入時。
- 這些方法都有一定的複雜度和性能考慮，特別是在大型數據集上運行時。

這些方案雖然可以實現需求，但實施難度和維護成本可能比直接列出所有欄位要高。如果可能，直接列出所有欄位會是最簡單和最直接的方式。