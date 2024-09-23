若要在 UniPath 中從 Excel 檔案中讀取範圍 C6 到 C 列的最後一個有數據的行（假設是 AF 行），你可以按照以下步驟來實作。

### 具體步驟：

#### 1. **Excel Application Scope**
   首先使用 `Excel Application Scope` 打開你的 Excel 檔案。

#### 2. **Read Range 活動**
   接著使用 `Read Range` 活動來讀取你需要的範圍。在你的情況下，我們會讀取 C6 到 C 列的最後一個非空行（假設你希望讀取範圍為 C6 到 C 列的最後一個有數據的單元格 AF 行）。

#### 3. **讀取指定範圍 (C6 到 C 列的最後一行)**：
   1. **活動：Read Range**
      - **範圍設置**：你可以手動設置範圍 `"C6:CAF"`（假設 AF 是最後一行）。
      - **工作表名稱**：指定你要讀取的工作表。
      - **輸出變數**：將讀取的結果存儲到一個 DataTable 變數中，例如 `DataTable_C6ToCAF`。

### 完整流程範例：

1. **打開最新的 Excel 檔案**
   - 使用 `Excel Application Scope` 打開 `LatestFilePath`，並確保 `Visible` 設置為 `True`（如需顯示 Excel）。

2. **讀取 C6 到 C 列最後一行（AF 行）的範圍**
   - **活動：Read Range**
     - **SheetName**: 你的工作表名稱，例如 `"Sheet1"`。
     - **範圍**: 設置為 `"C6:C500"`（可以設置一個比預期數據行數更大的範圍，例如 C6 到 C500）。
     - **輸出變數**: `DataTable_C6ToCAF`。

3. **後續處理數據**
   - 使用 DataTable 的處理方法來檢查數據。
   - 可以使用 `For Each Row` 活動來逐行讀取數據，或直接存取數據。

### 動態取得 C 列的最後一行 (可選項)：
如果你想動態獲取 C 列的最後一個非空行，你可以使用 `Read Range` 來讀取整個 C 列，然後使用程式來找到最後一個有值的行。例如：

```vbnet
Dim lastRowWithData As Integer = DataTable_C6ToCAF.Rows.Cast(Of DataRow)().Where(Function(row) Not String.IsNullOrEmpty(row(0).ToString())).Count() + 5 '因為從第6行開始
```

這樣可以幫助你動態取得最後一個有值的行號，並確保你讀取的範圍覆蓋所有數據。

### 總結：
1. 使用 `Excel Application Scope` 打開 Excel 檔案。
2. 使用 `Read Range` 讀取 C6 到 C 列的最後一個有數據的行（假設為 AF 行），並將數據存入 DataTable。
3. 後續根據需要處理該 DataTable，或動態獲取 C 列的最後一行來做進一步操作。

這樣，你就能成功從 C6 到 C 列的最後一個有數據的行讀取數據。

如果你重複下載檔案，檔案名稱可能會變成 `SHIP0002(1).xlsx`、`SHIP0002(2).xlsx` 等情況，這樣的話需要動態找到最新的檔案來打開。

以下是如何在 UniPath 實作這個邏輯的具體步驟：

### 具體實作步驟：

#### 1. **設置下載路徑變數**
- **活動：Assign**
  - **變數名**：`DownloadFolderPath`
  - **值**：`"C:\Downloads"`（這是你的下載目錄路徑，根據實際情況修改）

#### 2. **取得最新的 SHIP0002 檔案**
   使用 `Invoke Code` 活動來取得下載資料夾中最後修改的 `SHIP0002` 檔案（無論是 `SHIP0002.xlsx` 還是 `SHIP0002(1).xlsx` 等）。

- **活動：Invoke Code**
  - **Code**：
    ```vbnet
    Dim files As String() = Directory.GetFiles(DownloadFolderPath, "SHIP0002*.xlsx")
    LatestFilePath = files.OrderByDescending(Function(f) New FileInfo(f).LastWriteTime).First()
    ```

  - **變數**：
    - `DownloadFolderPath`（In 參數）：設定為你的下載資料夾路徑變數。
    - `LatestFilePath`（Out 參數）：新增這個變數來儲存最新檔案的路徑。

#### 3. **打開最新的 SHIP0002 檔案**
- **活動：Excel Application Scope**
  - **Path**：設置為 `LatestFilePath`，這樣可以打開最新下載的 SHIP0002 檔案。

### 步驟詳解：

1. **設置下載資料夾路徑**
   - 在流程中加入 `Assign` 活動，設定下載路徑變數 `DownloadFolderPath` 為 `C:\Downloads`。

2. **用 `Invoke Code` 活動取得最新的 SHIP0002 檔案**
   - 加入 `Invoke Code` 活動，並輸入上述程式碼，這個程式會搜尋所有名為 `SHIP0002*.xlsx` 的檔案（包括 `SHIP0002.xlsx` 和 `SHIP0002(1).xlsx` 等），並根據修改時間取最新的。
   - 在該活動中定義變數：
     - `DownloadFolderPath` 作為 In 參數。
     - `LatestFilePath` 作為 Out 參數。

3. **在 `Excel Application Scope` 打開檔案**
   - 加入 `Excel Application Scope` 活動，設定 `Path` 為 `LatestFilePath`。

### 流程總結：

1. 設定下載路徑變數 (`DownloadFolderPath`)。
2. 使用 `Invoke Code` 找出最新下載的 `SHIP0002` 檔案 (`LatestFilePath`)。
3. 用 `Excel Application Scope` 打開該最新的 Excel 檔案。

透過這個流程，你可以確保無論是 `SHIP0002.xlsx` 或 `SHIP0002(1).xlsx`，UniPath 都會自動打開最新下載的檔案。

在 UniPath 中，要實作上述邏輯以確保打開最新下載的 Excel 檔案，可以按照以下步驟來操作。這會涉及到使用 `Assign`、`Invoke Code`、`Excel Application Scope` 等活動。

### 具體步驟：

#### 1. **設置下載路徑變數**
- **活動：Assign**
  - **變數名**：`DownloadFolderPath`
  - **值**：`"C:\Downloads"`（這是你的下載資料夾路徑，可以根據實際情況修改）

#### 2. **取得最新下載的 Excel 檔案路徑**
   這個步驟會使用 `Invoke Code` 來執行 .NET 語法，取得最新修改的 Excel 檔案。

- **活動：Invoke Code**
  - **Code**：
    ```vbnet
    Dim files As String() = Directory.GetFiles(DownloadFolderPath, "*.xlsx")
    LatestFilePath = files.OrderByDescending(Function(f) New FileInfo(f).LastWriteTime).First()
    ```

  - **變數**：
    - `DownloadFolderPath`（In 參數）：設置為前面步驟中的下載資料夾路徑變數。
    - `LatestFilePath`（Out 參數）：新增這個變數來存儲最新的 Excel 檔案路徑。

#### 3. **打開最新的 Excel 檔案**
- **活動：Excel Application Scope**
  - **Path**：設置為 `LatestFilePath`，這樣就能打開最新的 Excel 檔案。

### 步驟詳解：

1. **設置下載資料夾路徑**
   - 在工作流程中加入 `Assign` 活動，設定下載路徑變數 `DownloadFolderPath` 為你的下載目錄，例如 `C:\Downloads`。

2. **用 `Invoke Code` 活動取得最新檔案**
   - 加入 `Invoke Code` 活動，並輸入上述程式碼，用來抓取資料夾內最新的 Excel 檔案。
   - 在該活動中定義變數：
     - `DownloadFolderPath` 作為 In 參數
     - `LatestFilePath` 作為 Out 參數

3. **在 `Excel Application Scope` 打開檔案**
   - 加入 `Excel Application Scope` 活動，設定 `Path` 為 `LatestFilePath`。

### 流程總結：

1. 設定下載路徑變數 (`DownloadFolderPath`)。
2. 使用 `Invoke Code` 找出最新下載的 Excel 檔案 (`LatestFilePath`)。
3. 用 `Excel Application Scope` 打開 `LatestFilePath`。

透過這樣的設計，你的流程就能自動抓取並打開最新下載的 Excel 檔案，即便檔案名稱發生了變化。