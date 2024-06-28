如果您想使用 `Robocopy` 命令來移動文件夾中的檔案，僅包括特定日期之前的檔案，並將日誌追加到現有日誌檔案，您可以按照以下的方式來設定命令：

### 命令結構

```bash
robocopy [source] [destination] /MOVE /E /MAXAGE:[date] /LOG+:[log file path]
```

- **[source]**: 源文件夾路徑。
- **[destination]**: 目標文件夾路徑。
- **/MOVE**: 移動文件（複製後刪除源文件）。
- **/E**: 複製所有子目錄（包括空的）。
- **/MAXAGE:[date]**: 複製日期在指定日期之前的檔案。日期格式為 `YYYYMMDD`。
- **/LOG+:[log file path]**: 將操作日誌追加到指定的日誌文件中。

### 範例

假設您想從 `"C:\source-folder"` 移動檔案到 `"D:\destination-folder"`，只包括 2023年5月13日及之前的檔案，並將日誌追加到 `"C:\logs\robocopy_log.txt"` 中，命令將如下：

```bash
robocopy C:\source-folder D:\destination-folder /MOVE /E /MAXAGE:20230513 /LOG+:C:\logs\robocopy_log.txt
```

### 執行命令

1. 打開「命令提示符」（在Windows中搜索 `cmd`）。
2. 輸入上述命令。
3. 按下 `Enter` 鍵執行命令。

這樣設定後，`Robocopy` 將按您的要求移動符合日期限制的文件，並將相關日誌信息追加到指定的日誌文件中。這種方式既保證了操作的精確性，又方便了之後的查閱和管理。