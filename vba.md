如果你的 Excel 圖表中有兩條折線圖，你可以修改 VBA 代碼來針對每一條折線進行不同的資料標籤格式設置，並分別將第一條折線設置為藍色，第二條折線設置為紅色。

以下是更新後的 VBA 代碼，會檢查兩條折線，並根據不同的條件顯示資料標籤和設置字型顏色（藍色和紅色）。

### 更新的 VBA 代碼

```vb
Sub UpdateDataLabelsBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim yValues As Variant
    Dim i As Integer
    Dim todayDate As Date

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)
    
    ' 遍歷圖表中的每一條線 (Series)
    For Each series In chart.Chart.SeriesCollection
        ' 獲取 X 軸和 Y 軸的數據
        xValues = series.XValues
        yValues = series.Values
        
        ' 移除所有資料標籤
        series.DataLabels.Delete
        
        ' 遍歷所有數據點
        For i = LBound(xValues) To UBound(xValues)
            ' 檢查 X 軸值是否為今天的日期
            If xValues(i) = todayDate Then
                ' 顯示對應的資料標籤
                series.Points(i).ApplyDataLabels
                
                ' 根據折線 (Series) 設置字型顏色和大小
                With series.Points(i).DataLabel
                    .Font.Size = 12 ' 設置字型大小
                    If series.Index = 1 Then
                        ' 第一條折線，設置藍色
                        .Font.Color = RGB(0, 0, 255) ' 藍色
                    ElseIf series.Index = 2 Then
                        ' 第二條折線，設置紅色
                        .Font.Color = RGB(255, 0, 0) ' 紅色
                    End If
                    .Font.Bold = True ' 設置加粗效果 (可選)
                End With
            End If
        Next i
    Next series
End Sub
```

### 代碼說明：
1. **`For Each series In chart.Chart.SeriesCollection`**：這行代碼遍歷圖表中的所有折線（每條折線是 `Series` 集合中的一個成員）。
2. **`series.Index = 1`**：當 `Index = 1` 時，表示是第一條折線，會將字型設置為藍色。
3. **`series.Index = 2`**：當 `Index = 2` 時，表示是第二條折線，會將字型設置為紅色。

### 如何使用
1. 按照之前步驟插入折線圖，確保圖表中有兩條折線。
2. 在 VBA 編輯器中插入此代碼。
3. 按 `Alt + F8` 選擇 `UpdateDataLabelsBasedOnDate`，然後執行。

這樣你的圖表就會根據今天的日期動態顯示資料標籤，並且第一條折線的標籤會是藍色，第二條折線的標籤會是紅色。如果有更多折線或需要不同的格式，可以進一步修改代碼。

在 Excel 中，可以使用 VBA 來自動根據今天的日期動態顯示折線圖的資料標籤。以下是實現這一需求的步驟：

### 1. 插入折線圖
- 先準備好你的數據源，並插入一個折線圖。

### 2. 添加 VBA 代碼
- 按下 `Alt + F11` 開啟 VBA 編輯器。
- 在左邊的「**VBAProject**」中找到你的工作表，右鍵點擊它並選擇「**插入 > 模組**」。
- 然後在新模組中輸入以下 VBA 代碼：

```vb
Sub UpdateDataLabelsBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim yValues As Variant
    Dim i As Integer
    Dim todayDate As Date

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)
    Set series = chart.Chart.SeriesCollection(1)
    
    ' 獲取 X 軸和 Y 軸的數據
    xValues = series.XValues
    yValues = series.Values
    
    ' 移除所有資料標籤
    series.DataLabels.Delete
    
    ' 遍歷所有數據點
    For i = LBound(xValues) To UBound(xValues)
        ' 檢查 X 軸值是否為今天的日期
        If xValues(i) = todayDate Then
            ' 顯示對應的資料標籤
            series.Points(i).ApplyDataLabels
        End If
    Next i
End Sub
```

### 3. 代碼說明
- 這段代碼會遍歷圖表中的所有數據點，並檢查 X 軸的日期是否為今天的日期。
- 如果 X 軸的日期是今天，則會顯示對應的資料標籤。

### 4. 觸發宏
- 在 Excel 中，按 `Alt + F8` 開啟「**宏**」對話框。
- 選擇 `UpdateDataLabelsBasedOnDate`，然後按下「**執行**」即可。

這樣你的折線圖會動態根據今天的日期來顯示資料標籤。你也可以將此 VBA 宏綁定到按鈕或工作表事件（例如每次工作表改變時自動執行），以進一步自動化操作。

如果有其他特定需求或問題，可以進一步調整代碼來適應。