要將 SQL 腳本中的表名稱作為變數使用，可以通過動態 SQL 命令來實現。下面是一個示例，展示如何將表名稱設為變數並執行相應的 SQL 命令：

### 步驟 1: 定義變數
首先，您需要定義包含表名的 SQL 變數。然後使用這些變數來構建動態 SQL 查詢。

```sql
DECLARE @SourceTable NVARCHAR(128) = 'OriginalTable';  -- 源表名
DECLARE @BackupTable NVARCHAR(128) = 'BackupTable';  -- 備份表名
```

### 步驟 2: 使用動態 SQL 創建和更新表
您將需要使用 `EXEC sp_executesql` 命令來執行包含變數的 SQL 腳本。

```sql
-- 創建新表的動態 SQL 腳本
DECLARE @SQL NVARCHAR(MAX);

-- 檢查新表是否存在，如果不存在則創建新表
SET @SQL = N'IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = ''' + @BackupTable + ''')
BEGIN
    SELECT * INTO ' + @BackupTable + ' FROM ' + @SourceTable + ' WHERE 1 = 0; -- 創建結構
END';
EXEC sp_executesql @SQL;

-- 將數據從源表複製到備份表
SET @SQL = N'INSERT INTO ' + @BackupTable + ' SELECT * FROM ' + @SourceTable + ';';
EXEC sp_executesql @SQL;
```

### 步驟 3: 驗證數據
最後，您可以執行一個查詢來檢查新表中的數據：

```sql
SET @SQL = N'SELECT * FROM ' + @BackupTable + ';';
EXEC sp_executesql @SQL;
```

### 注意事項：
- 使用動態 SQL 時需小心，因為它容易出錯且可能導致 SQL 注入攻擊。確保控制變數的來源和內容。
- 確保在生產環境中使用時具有適當的許可權和錯誤處理機制。
- 確保傳入的表名稱是預期的並且安全的。

通過這種方法，您可以將表名作為變數傳入 SQL 腳本，方便地對不同的表進行操作。

如果您想要將 SQL Server Management Studio (SSMS) 中的一個表中的所有資料備份到一個新的表中，您可以使用 SQL 查詢來達到這個目的。這裡提供一個簡單的步驟來實現這個過程：

### 步驟 1: 開啟 SSMS 並連接到數據庫
1. 打開 SQL Server Management Studio。
2. 連接到您的 SQL Server 實例。

### 步驟 2: 創建新表並複製資料
假設您已經有一個叫做 `OriginalTable` 的表，您想要將其所有資料複製到一個新的表 `BackupTable` 中。您可以使用以下 SQL 命令來執行這個操作：

```sql
-- 檢查新表是否已存在，如果不存在則創建新表
IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'BackupTable')
BEGIN
    -- 使用原表的結構來創建新表
    SELECT *
    INTO BackupTable
    FROM OriginalTable
    WHERE 1 = 0  -- 這樣做是為了只創建表結構，不複製數據
END

-- 現在將原表的所有數據插入到新表中
INSERT INTO BackupTable
SELECT * FROM OriginalTable
```

### 說明：
- 第一個 `SELECT INTO` 語句檢查 `BackupTable` 是否存在，如果不存在，它將創建一個新表並具有與 `OriginalTable` 相同的結構但不包含任何數據。
- `INSERT INTO` 語句將 `OriginalTable` 中的所有數據複製到 `BackupTable` 中。

### 步驟 3: 驗證數據
完成後，您可以執行一個簡單的查詢來檢查新表中的數據是否正確：

```sql
SELECT * FROM BackupTable
```

這樣您就可以確保所有的數據都被正確地複製到新表中了。

### 注意事項：
- 確保在執行這些操作之前擁有足夠的許可權。
- 如果數據量很大，這個過程可能需要一些時間。
- 定期檢查和維護備份數據的完整性和更新性。

通過這些步驟，您可以有效地將 SSMS 中一個表的數據備份到另一個新的表中。