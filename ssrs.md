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