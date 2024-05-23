若要在SSRS中根據三個不同的分析類型（例如世代、產品名稱、量測機台）進行分析並創建相應的圓餅圖，你可以根據每個類型創建不同的報告部分或使用參數來動態選擇分析類型。這裡有兩種主要方法：

### 方法1：創建三個圓餅圖
每個圓餅圖對應一種分析類型。這種方法簡單直觀，適用於報告固定展示所有三個類型的情況。

#### 步驟：
1. **準備三個資料集**：你需要為每個分析類型創建一個資料集，例如：
   - 對於世代：
     ```sql
     SELECT GenerationType, COUNT(*) AS Count
     FROM YourTable
     GROUP BY GenerationType
     ```
   - 對於產品名稱：
     ```sql
     SELECT ProductName, COUNT(*) AS Count
     FROM YourTable
     GROUP BY ProductName
     ```
   - 對於量測機台：
     ```sql
     SELECT MachineName, COUNT(*) AS Count
     FROM YourTable
     GROUP BY MachineName
     ```

2. **插入三個圓餅圖**：在報告中為每個資料集插入一個圓餅圖，並將相應的數據集連接至對應的圓餅圖。

3. **格式化圓餅圖**：為每個圓餅圖選擇顏色、設置標籤等。

### 方法2：使用參數動態生成圓餅圖
使用一個圓餅圖和一個報告參數來動態選擇想要分析的類型。這種方法靈活，適合用戶需要在同一報告中切換不同分析類型的情況。

#### 步驟：
1. **創建參數**：在報告中添加一個參數，例如 `AnalysisType`，允許用戶選擇「世代」、「產品名稱」或「量測機台」。

2. **準備一個資料集**：資料集的SQL查詢應該基於參數來動態變化，例如：
   ```sql
   SELECT 
     CASE 
       WHEN @AnalysisType = 'Generation' THEN GenerationType
       WHEN @AnalysisType = 'ProductName' THEN ProductName
       WHEN @AnalysisType = 'MachineName' THEN MachineName
     END AS Category,
     COUNT(*) AS Count
   FROM YourTable
   GROUP BY 
     CASE 
       WHEN @AnalysisType = 'Generation' THEN GenerationType
       WHEN @AnalysisType = 'ProductName' THEN ProductName
       WHEN @AnalysisType = 'MachineName' THEN MachineName
     END
   ```

3. **設定圓餅圖數據**：將圓餅圖的數據源設置為上述資料集，並根據`Category`和`Count`欄位配置數據。

4. **部署並測試報告**：確保參數正確影響圓餅圖的數據顯示。

選擇這兩種方法中的任何一種，根據你的具體需求和報告使用者的偏好來決定。如果你希望報告更加動態和交


要將之前提到的查詢轉換成一個存儲過程（Stored Procedure），這樣可以使得從SQL Server Reporting Services (SSRS) 中調用這些查詢更加方便與有效。這裡我將示範如何為之前提到的方法2（使用參數動態生成圓餅圖的SQL查詢）創建存儲過程。

### 創建存儲過程的步驟：

#### 1. 定義存儲過程
打開你的SQL Server Management Studio (SSMS)，連接到數據庫，並開始編寫新的存儲過程：

```sql
CREATE PROCEDURE GetChartData
    @AnalysisType VARCHAR(50)
AS
BEGIN
    SELECT 
        CASE 
            WHEN @AnalysisType = 'Generation' THEN GenerationType
            WHEN @AnalysisType = 'ProductName' THEN ProductName
            WHEN @AnalysisType = 'MachineName' THEN MachineName
        END AS Category,
        COUNT(*) AS Count
    FROM YourTable
    GROUP BY 
        CASE 
            WHEN @AnalysisType = 'Generation' THEN GenerationType
            WHEN @AnalysisType = 'ProductName' THEN ProductName
            WHEN @AnalysisType = 'MachineName' THEN MachineName
        END
END;
GO
```

#### 2. 部署存儲過程
在SSMS中運行上述SQL腳本，這將創建新的存儲過程。確保在適當的數據庫上執行它。

#### 3. 在SSRS中調用存儲過程
- 在你的SSRS報告中，設置一個新的資料來源，連接到包含該存儲過程的數據庫。
- 創建或修改一個數據集，選擇使用存儲過程，並指定剛剛創建的 `GetChartData` 存儲過程。
- 為該數據集配置參數，使之與報告參數 `@AnalysisType` 連接。

#### 4. 測試報告
在報告設計器中設置並預覽報告，檢查不同參數選項下的圓餅圖是否正確反映數據。

這個存儲過程允許你在報告中動態選擇分析類型，並依據選擇生成相應的圓餅圖。這樣做可以提高報告的靈活性和數據處理的效率。