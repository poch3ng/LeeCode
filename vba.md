如果你想要逐段修改線的樣式，而不是一次性對整條線應用虛線樣式，那麼可以在每個點之間切換不同的樣式。這樣，你可以依據日期來動態地改變每一個點之間的線條樣式，例如：在過去日期使用實線，在未來日期使用虛線。

在 VBA 中，無法直接針對單個點之間的線條應用不同樣式，但可以透過在每個資料點之後插入額外的「空」資料點（NaN），分段處理線條樣式。另一種方法是使用多條 Series，每一段都用不同的線條樣式。

### 解決方法：使用兩條 Series 來分段應用不同樣式
這裡提供一個範例，分成兩個 Series：一個用於顯示實線（過去的資料點），另一個用於顯示虛線（未來的資料點）。

### 修改程式碼範例：

```vba
Sub UpdateDataLabelsAndSegmentedLineStyleBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim yValues As Variant
    Dim i As Integer
    Dim todayDate As Date
    Dim lastPointIndex As Integer
    Dim isFuture As Boolean
    Dim xDate As Date

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)

    ' 第一條線條 (藍色，標籤顯示在上方) - 顯示過去和今天的實線
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues ' 取得 X 軸日期
    yValues = series.Values ' 取得 Y 軸數值
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    For i = LBound(xValues) To UBound(xValues)
        ' 將 X 軸的數值轉換成日期
        xDate = CDate(xValues(i))

        ' 記錄 X 軸的日期值以便排查
        Debug.Print "xDate(" & i & "): " & xDate
        
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xDate = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If

        ' 如果 xDate 是未來的資料，跳出這條線條的迴圈，切換到下一條線
        If xDate > todayDate Then Exit For
    Next i

    ' 第二條線條 (藍色虛線，顯示未來的線條)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues ' 取得 X 軸日期
    yValues = series.Values ' 取得 Y 軸數值
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    For i = LBound(xValues) To UBound(xValues)
        ' 將 X 軸的數值轉換成日期
        xDate = CDate(xValues(i))

        ' 記錄 X 軸的日期值以便排查
        Debug.Print "xDate(" & i & "): " & xDate
        
        ' 顯示最後一個資料點的標籤
        If i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If

        ' 如果資料點是未來，設定虛線
        If xDate > todayDate Then
            series.Format.Line.DashStyle = msoLineDash ' 設定虛線
        End If
    Next i
End Sub
```

### 解釋：
1. **第一條線條（實線）**：這條線顯示今天及之前的資料點，並使用實線樣式。當超過今天的資料點時，迴圈退出，避免繼續繪製未來的資料。
2. **第二條線條（虛線）**：這條線從今天之後的資料點開始顯示，並使用虛線樣式。

### 優化：
如果你想進一步細分樣式，還可以將資料分為更多段，將未來的每個區段分成不同的系列來處理，這樣可以針對每一段應用不同的樣式或顏色。

這樣就可以達到分段改變線條樣式的效果。

要實現今天之前的資料點用實線、未來的資料點用虛線，不能只用一次性設定整條折線的線條格式。相反，必須拆分成兩個部分，一個部分是顯示實線（今天之前的資料點），另一個部分顯示虛線（未來的資料點）。這需要將折線圖拆分成兩個不同的系列來進行格式化。

更新的 VBA 代碼將折線圖根據日期分成兩個部分來顯示，一個是實線（今天及之前），另一個是虛線（未來的日期）。

### 更新的 VBA 代碼

```vb
Sub UpdateDataLabelsAndLineStyleBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim yValues As Variant
    Dim i As Integer
    Dim todayDate As Date
    Dim lastPointIndex As Integer
    Dim isFuture As Boolean

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)

    ' 第一條線條 (藍色，標籤顯示在上方)
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    isFuture = False ' 設定初始狀態為過去資料

    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If

        ' 判斷是否是未來資料，切換線條格式
        If xValues(i) > todayDate And isFuture = False Then
            ' 如果是未來的資料點，開始使用虛線
            series.Format.Line.DashStyle = msoLineDash ' 虛線
            isFuture = True
        End If
    Next i

    ' 第二條線條 (紅色，標籤顯示在下方)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    isFuture = False ' 設定初始狀態為過去資料

    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(255, 0, 0) ' 紅色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionBelow ' 標籤顯示在下方
            End With
        End If
        
        ' 判斷是否是未來資料，切換線條格式
        If xValues(i) > todayDate And isFuture = False Then
            ' 如果是未來的資料點，開始使用虛線
            series.Format.Line.DashStyle = msoLineDash ' 虛線
            isFuture = True
        End If
    Next i
End Sub
```

### 代碼說明：
1. **`isFuture` 判斷變數**：我們引入了 `isFuture` 來追踪目前是否處於未來的資料點。如果處於未來的資料點，就改變線條為虛線。
2. **動態變更線條樣式**：程式會在迭代過程中根據日期動態變更線條格式。

### 執行方法：
1. 在 Excel 中按 `Alt + F11`，打開 VBA 編輯器，將代碼貼入模組中。
2. 回到 Excel，按 `Alt + F8` 選擇 `UpdateDataLabelsAndLineStyleBasedOnDate` 宏並執行。

這樣，你的圖表就能自動根據今天的日期來顯示實線和虛線，並且依然會顯示對應的資料標籤格式。如果依然無法實現，可能需要將未來的數據點移動到不同的資料系列中來分別設置其格式。

要實現將今天（包含）以前的日期顯示為實線，未來的日期顯示為虛線，我們可以使用 VBA 動態設置圖表中的線條格式。具體步驟如下：

### 更新的 VBA 代碼

這段代碼不僅會根據今天的日期來動態顯示資料標籤和設置字型格式，還會對今天及之前的資料點使用實線，對未來的資料點使用虛線。

```vb
Sub UpdateDataLabelsAndLineStyleBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim i As Integer
    Dim todayDate As Date
    Dim lastPointIndex As Integer

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)

    ' 第一條線條 (藍色，標籤顯示在上方)
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引

    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If
        ' 設置實線和虛線
        If xValues(i) <= todayDate Then
            series.Format.Line.DashStyle = msoLineSolid ' 今天或之前的使用實線
        Else
            series.Format.Line.DashStyle = msoLineDash ' 未來的日期使用虛線
        End If
    Next i

    ' 第二條線條 (紅色，標籤顯示在下方)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues
    series.DataLabels.Delete ' 移除所有資料標籤
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引

    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(255, 0, 0) ' 紅色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionBelow ' 標籤顯示在下方
            End With
        End If
        ' 設置實線和虛線
        If xValues(i) <= todayDate Then
            series.Format.Line.DashStyle = msoLineSolid ' 今天或之前的使用實線
        Else
            series.Format.Line.DashStyle = msoLineDash ' 未來的日期使用虛線
        End If
    Next i
End Sub
```

### 代碼說明：
1. **`series.Format.Line.DashStyle = msoLineSolid`**：設置線條為實線，這是針對今天（包含）及之前的日期。
2. **`series.Format.Line.DashStyle = msoLineDash`**：設置線條為虛線，這是針對未來的日期。
3. **條件判斷**：代碼遍歷所有資料點，並根據日期決定是使用實線還是虛線。

### 如何使用：
1. 在 Excel 中按 `Alt + F11`，打開 VBA 編輯器，將代碼貼入模組中。
2. 回到 Excel，按 `Alt + F8` 選擇 `UpdateDataLabelsAndLineStyleBasedOnDate` 宏並執行。

這樣，你的圖表就能自動根據今天的日期來顯示實線和虛線，並且依然會顯示對應的資料標籤格式。

為了確保兩條折線圖的最後一筆資料標籤顯示出來，我們需要在程式中額外添加一個條件，用於檢查和顯示每條折線的最後一個資料點的資料標籤。

以下是更新後的 VBA 代碼，它除了根據今天的日期顯示資料標籤，還會顯示每條折線圖的最後一個資料標籤。

### 更新的 VBA 代碼

```vb
Sub UpdateDataLabelsBasedOnDate()
    Dim chart As ChartObject
    Dim series As Series
    Dim xValues As Variant
    Dim yValues As Variant
    Dim i As Integer
    Dim todayDate As Date
    Dim lastPointIndex As Integer

    ' 設定當前日期
    todayDate = Date
    
    ' 假設折線圖為第一張圖表
    Set chart = ActiveSheet.ChartObjects(1)
    
    ' 第一條線條 (藍色，標籤顯示在上方)
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If
    Next i

    ' 第二條線條 (紅色，標籤顯示在下方)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    
    lastPointIndex = UBound(xValues) ' 找到最後一筆資料的索引
    
    For i = LBound(xValues) To UBound(xValues)
        ' 顯示今天的資料標籤或是最後一個資料點的標籤
        If xValues(i) = todayDate Or i = lastPointIndex Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(255, 0, 0) ' 紅色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionBelow ' 標籤顯示在下方
            End With
        End If
    Next i
End Sub
```

### 代碼說明：
1. **`lastPointIndex = UBound(xValues)`**：這行代碼找到每條折線圖的最後一筆資料索引。
2. **`If xValues(i) = todayDate Or i = lastPointIndex Then`**：此條件確保程式顯示今天日期的資料標籤，或者顯示最後一筆資料的標籤。
3. **標籤位置與字型格式**：根據折線圖的索引，對應設置藍色線條標籤在上方、紅色線條標籤在下方，並且加粗字型與設置字型顏色。

### 執行方法：
1. 按 `Alt + F8`，選擇 `UpdateDataLabelsBasedOnDate`，然後執行。

這樣，除了顯示今天日期的資料標籤外，兩條折線圖的最後一個資料標籤也會顯示出來。你可以根據需要進一步調整代碼來符合具體要求。

如果您想將藍色折線的資料標籤顯示在數據點的上方，紅色折線的資料標籤顯示在下方，可以使用 `.Position` 屬性來調整資料標籤的位置。以下是更新後的 VBA 代碼：

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
    
    ' 第一條線條 (藍色，標籤顯示在上方)
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    For i = LBound(xValues) To UBound(xValues)
        If xValues(i) = todayDate Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionAbove ' 標籤顯示在上方
            End With
        End If
    Next i

    ' 第二條線條 (紅色，標籤顯示在下方)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    For i = LBound(xValues) To UBound(xValues)
        If xValues(i) = todayDate Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(255, 0, 0) ' 紅色
                .Font.Bold = True ' 加粗
                .Position = xlLabelPositionBelow ' 標籤顯示在下方
            End With
        End If
    Next i
End Sub
```

### 代碼說明：
1. **`.Position = xlLabelPositionAbove`**：將藍色折線的資料標籤顯示在數據點的上方。
2. **`.Position = xlLabelPositionBelow`**：將紅色折線的資料標籤顯示在數據點的下方。

### 標籤位置選項：
- **`xlLabelPositionAbove`**：資料標籤顯示在數據點上方。
- **`xlLabelPositionBelow`**：資料標籤顯示在數據點下方。
- **`xlLabelPositionCenter`**：資料標籤顯示在數據點正中央。
- **`xlLabelPositionLeft`**：資料標籤顯示在數據點左側。
- **`xlLabelPositionRight`**：資料標籤顯示在數據點右側。

### 執行方法：
1. 和之前一樣，按 `Alt + F8`，選擇 `UpdateDataLabelsBasedOnDate`，然後執行。

這樣，藍色的資料標籤將會顯示在上方，紅色的資料標籤會顯示在下方。你也可以根據需要進一步調整資料標籤的位置。

根據您的回報，`series.Index = 1` 出現錯誤，原因是 `Series` 物件本身沒有 `Index` 屬性。要正確識別哪一條折線是第一條或第二條，我們可以使用 `SeriesCollection` 的索引來直接引用每一條折線，並分別進行處理。

請使用以下更新的代碼：

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
    
    ' 第一條線條 (藍色)
    Set series = chart.Chart.SeriesCollection(1)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    For i = LBound(xValues) To UBound(xValues)
        If xValues(i) = todayDate Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(0, 0, 255) ' 藍色
                .Font.Bold = True ' 加粗
            End With
        End If
    Next i

    ' 第二條線條 (紅色)
    Set series = chart.Chart.SeriesCollection(2)
    xValues = series.XValues
    yValues = series.Values
    series.DataLabels.Delete ' 移除所有資料標籤
    For i = LBound(xValues) To UBound(xValues)
        If xValues(i) = todayDate Then
            series.Points(i).ApplyDataLabels ' 顯示資料標籤
            With series.Points(i).DataLabel
                .Font.Size = 12 ' 設置字型大小
                .Font.Color = RGB(255, 0, 0) ' 紅色
                .Font.Bold = True ' 加粗
            End With
        End If
    Next i
End Sub
```

### 代碼說明：
1. **`SeriesCollection(1)` 和 `SeriesCollection(2)`**：這個方法使用 `SeriesCollection` 的索引來選擇第一條和第二條折線。`SeriesCollection(1)` 對應第一條折線，`SeriesCollection(2)` 對應第二條折線。
2. 針對每條折線，代碼會分別遍歷其數據點並根據今天的日期顯示資料標籤，同時設置字型的大小和顏色。

### 執行方法：
1. 按 `Alt + F8`，選擇 `UpdateDataLabelsBasedOnDate`，然後執行。

這樣就能夠針對兩條折線分別顯示資料標籤並設置不同的字型顏色與格式。

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