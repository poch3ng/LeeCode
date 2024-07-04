當你在 SQL 中遇到違反主鍵條件約束的錯誤，表示你嘗試插入的資料中有重複的主鍵值，這是不被允許的。在 `dbo.TrainingFormMain` 表格中，每個主鍵的值必須是唯一的。以下是解決此問題的步驟：

1. **檢查資料**：先確認你嘗試插入的資料，看看是否主鍵欄位中的值已經存在於資料表中。
   ```sql
   SELECT * FROM dbo.TrainingFormMain WHERE PrimaryKeyColumn = '你想插入的值';
   ```
   將 `PrimaryKeyColumn` 替換成你的主鍵欄位名稱，並將 `'你想插入的值'` 替換成你嘗試插入的主鍵值。

2. **修改資料**：如果上述查詢返回了結果，這表示該主鍵值已經存在。你需要修改你嘗試插入的資料中的主鍵值，使其唯一。
   
3. **再次插入資料**：修改後，再次執行插入操作。確保新的主鍵值不會與表中現有的主鍵值重複。
   ```sql
   INSERT INTO dbo.TrainingFormMain (PrimaryKeyColumn, OtherColumn1, OtherColumn2) VALUES ('新的主鍵值', '值1', '值2');
   ```
   將 `PrimaryKeyColumn`, `OtherColumn1`, `OtherColumn2` 替換成你的實際欄位名稱，並用相應的值替換 `'新的主鍵值'`, `'值1'`, `'值2'`。

4. **錯誤處理**：為了避免未來再次發生此類錯誤，考慮在你的應用程式或資料處理邏輯中加入錯誤處理機制，以檢查資料是否已存在於資料庫中。

透過這些步驟，你應該能夠解決違反主鍵條件約束的問題。