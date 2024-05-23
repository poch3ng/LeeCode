要使 SSRS 報告中的顏色動態生成，並依據 `GenerationType` 的數量或類型自動選擇顏色，可以使用一些技巧來實現這種動態顏色配置。這樣做可以確保隨著 `GenerationType` 的變化，顏色能夠自動配對，而無需手動更新顏色設置。這裡是一種實現方法：

### 創建動態顏色的步驟：

#### 1. 準備自定義代碼
在報告的「報告屬性」中，添加自定義代碼來生成顏色。這段代碼會在內存中維護一個字典，對每個獨特的 `GenerationType` 分配一個顏色。

##### 添加自定義代碼：
- 打開報告的設計視圖。
- 在「報告」菜單中選擇「報告屬性」。
- 點擊「代碼」選項卡並輸入以下代碼：

```vb
Dim colorDict As System.Collections.Generic.Dictionary(Of String, String) = Nothing

Public Function GetColor(ByVal generationType As String) As String
    If colorDict Is Nothing Then
        colorDict = New System.Collections.Generic.Dictionary(Of String, String)
    End If

    If colorDict.ContainsKey(generationType) Then
        Return colorDict(generationType)
    Else
        Dim color As String = String.Format("#{0:X6}", (New Random()).Next(16777216)) ' Generate random color
        colorDict.Add(generationType, color)
        Return color
    End If
End Function
```

#### 2. 設置長條圖的顏色
在長條圖的「系列屬性」中，設定「填充顏色」的表達式使用剛剛建立的函數：

```vb
=Code.GetColor(Fields!GenerationType.Value)
```

這個表達式會為每個獨特的 `GenerationType` 調用 `GetColor` 函數，該函數將返回一個顏色，如果該類型已存在於字典中，則返回相應的顏色；如果不存在，則生成一個新顏色並將其添加到字典中。

#### 3. 預覽並調整報告
- 應用並預覽報告以確保顏色的動態生成運作正常。
- 確認每個 `GenerationType` 的顏色保持一致性，即使報告數據或 `GenerationType` 類型有所改變。

#### 4. 部署報告
完成所有設定後，將報告部署到報告服務伺服器以供使用。

使用這種方法，你可以確保 SSRS 報告中的顏色分配完全動態化，適應數據變化，同時無需手動干預顏色設置。這對於數據類型頻繁變動或未知的情況特別有用。