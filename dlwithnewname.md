在 VB WebForm 中，如果要在使用者下載檔案時更改檔案名稱，可以通過設置 `Content-Disposition` 標頭來實現。以下是步驟：

### 1. 在後端控制檔案的下載
在你的程式碼後端 (例如 Button 點擊事件) 中，使用 `Response` 物件來控制檔案的下載過程。

### 2. 設定 `Response` 物件
你需要設定檔案的 MIME 類型和檔案名，並將檔案流寫入 `Response`。

### 範例程式碼：
```vb
Protected Sub btnDownload_Click(sender As Object, e As EventArgs) Handles btnDownload.Click
    ' 設定檔案路徑 (伺服器上的檔案)
    Dim filePath As String = Server.MapPath("~/files/yourfile.txt")
    
    ' 設定要更改的檔案名稱
    Dim newFileName As String = "NewFileName.txt"

    ' 檢查檔案是否存在
    If System.IO.File.Exists(filePath) Then
        ' 清除之前的 response 資料
        Response.Clear()

        ' 設定檔案的 ContentType (MIME 類型)
        Response.ContentType = "application/octet-stream"

        ' 設定檔案的標頭資訊，以強制下載並設定新的檔名
        Response.AddHeader("Content-Disposition", "attachment; filename=" & newFileName)

        ' 讀取檔案並寫入 Response 輸出
        Response.WriteFile(filePath)

        ' 結束 Response 輸出，確保下載完成
        Response.End()
    Else
        ' 如果檔案不存在，顯示錯誤訊息
        Response.Write("檔案不存在")
    End If
End Sub
```

### 3. 關鍵部分：
- **`Server.MapPath()`**：將相對路徑轉換為伺服器上的實際路徑。
- **`Response.ContentType`**：設定檔案類型，`application/octet-stream` 通常用於二進位檔案下載。
- **`Response.AddHeader()`**：`Content-Disposition` 的標頭可以指定下載時的檔名，透過設定 `attachment` 並指定 `filename`。

### 結果：
當使用者點擊下載按鈕時，檔案將以你指定的新檔名下載，而不是伺服器上實際的檔名。

這樣可以確保使用者下載的檔案名稱與伺服器上的原檔案名稱不同。